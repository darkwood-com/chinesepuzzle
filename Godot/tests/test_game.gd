## Headless test: godot --headless -s res://tests/test_game.gd
## Checks deal, move validation, undo, a reachable win (scramble/replay on a seed) and the game scene.
extends SceneTree

var failures := 0

func ok(cond: bool, msg: String) -> void:
	if cond:
		print("PASS ", msg)
	else:
		failures += 1
		printerr("FAIL ", msg)

func _initialize() -> void:
	_test_deal()
	_test_rules()
	_test_win_reachable()
	await _test_scene()
	print("RESULT: %s (%d failures)" % ["OK" if failures == 0 else "FAILED", failures])
	quit(1 if failures else 0)

func _test_deal() -> void:
	var rng := RandomNumberGenerator.new()
	rng.seed = 42
	var b := CpzRules.deal(rng)
	var counts := {}
	var gaps := 0
	for i in CpzRules.ROWS:
		ok(b[i][0] == CpzRules.GAP, "column 0 row %d is empty" % i)
		for j in CpzRules.COLS:
			if b[i][j] == CpzRules.GAP:
				gaps += 1
			else:
				counts[b[i][j]] = counts.get(b[i][j], 0) + 1
	ok(gaps == 8, "8 gaps after deal")
	ok(counts.size() == 52 and counts.values().all(func(v): return v == 2), "two full decks dealt")
	var rng2 := RandomNumberGenerator.new()
	rng2.seed = 42
	ok(CpzRules.deal(rng2) == b, "deal is deterministic for a seed")

func _test_rules() -> void:
	var b := CpzRules.empty_board()
	var heart_ace := CpzRules.make_card(0, 1)
	var heart_two := CpzRules.make_card(0, 2)
	var club_two := CpzRules.make_card(1, 2)
	b[0][5] = heart_ace
	b[1][3] = heart_two
	b[2][4] = club_two
	ok(CpzRules.check_move(b, Vector2i(1, 3), Vector2i(3, 0)) == CpzRules.Check.KO, "only an Ace goes to column 0")
	ok(CpzRules.check_move(b, Vector2i(0, 5), Vector2i(3, 0)) == CpzRules.Check.OK, "Ace to column 0 is valid")
	ok(CpzRules.check_move(b, Vector2i(5, 5), Vector2i(3, 0)) == CpzRules.Check.FROM, "moving from an empty cell is rejected")
	ok(CpzRules.check_move(b, Vector2i(0, 5), Vector2i(1, 3)) == CpzRules.Check.FROM, "target must be empty")
	ok(CpzRules.check_move(b, Vector2i(1, 3), Vector2i(4, 4)) == CpzRules.Check.TO_BEFORE, "left of target must be a card")
	ok(CpzRules.check_move(b, Vector2i(1, 3), Vector2i(0, 6)) == CpzRules.Check.OK, "2 of same suit next to its Ace is valid")
	ok(CpzRules.check_move(b, Vector2i(2, 4), Vector2i(0, 6)) == CpzRules.Check.KO, "2 of another suit next to the Ace is invalid")
	# apply then undo (swap is its own inverse)
	var before := CpzRules.copy_board(b)
	CpzRules.swap(b, Vector2i(1, 3), Vector2i(0, 6))
	ok(b[0][6] == heart_two and b[1][3] == CpzRules.GAP, "move applied")
	CpzRules.swap(b, Vector2i(1, 3), Vector2i(0, 6))
	ok(b == before, "undo restores the board")

func _solved() -> Array:
	var b := CpzRules.empty_board()
	for i in CpzRules.ROWS:
		for j in 13:
			b[i][j] = CpzRules.make_card(i % 4, j + 1)
	return b

func _test_win_reachable() -> void:
	var b := _solved()
	ok(CpzRules.is_won(b), "solved board is a win")
	var rng := RandomNumberGenerator.new()
	rng.seed = 2026
	var forward := []
	# Scramble with 400 reverse moves: take a card that could legally have arrived at its cell, move it to a gap.
	for step in 400:
		var candidates := []
		var gaps := []
		for i in CpzRules.ROWS:
			for j in CpzRules.COLS:
				var c: int = b[i][j]
				if c == CpzRules.GAP:
					gaps.append(Vector2i(i, j))
				elif (j == 0 and CpzRules.rank_of(c) == 1) or (j > 0 and CpzRules.is_next_to(c, b[i][j - 1])):
					candidates.append(Vector2i(i, j))
		if candidates.is_empty():
			break
		var g: Vector2i = candidates[rng.randi_range(0, candidates.size() - 1)]
		var p: Vector2i = gaps[rng.randi_range(0, gaps.size() - 1)]
		CpzRules.swap(b, g, p)
		forward.push_front([p, g])
	ok(forward.size() >= 50, "scrambled with %d reverse moves" % forward.size())
	ok(not CpzRules.is_won(b), "scrambled board is not won")
	var all_valid := true
	for m in forward:
		if CpzRules.check_move(b, m[0], m[1]) != CpzRules.Check.OK:
			all_valid = false
			break
		CpzRules.swap(b, m[0], m[1])
	ok(all_valid, "every replayed move is valid (%d moves)" % forward.size())
	ok(CpzRules.is_won(b), "win reached by replaying valid moves")

func _test_scene() -> void:
	var main = load("res://scenes/main.tscn").instantiate()
	root.add_child(main)
	await process_frame
	ok(main.board.size() == 8 and main.board[0].size() == 14, "scene built an 8x14 board")
	await create_timer(2.5).timeout
	ok(not main.is_busy(), "deal animation finished")
	var moves: Array = CpzRules.legal_moves(main.grid)
	print("legal moves at start: ", moves.size())
	if moves.size() > 0:
		var m = moves[0]
		var card = main.get_card(m[0])
		ok(main.make_move(m[0], m[1]) == CpzRules.Check.OK, "scene accepts a legal move")
		ok(main.get_card(m[1]) == card and main.conf["moves"].size() == 1, "card moved and move recorded")
		await create_timer(0.8).timeout
		main.undo_move()
		ok(main.get_card(m[0]) == card and main.conf["moves"].is_empty(), "undo puts the card back")
		await create_timer(0.8).timeout
	# an invalid move is refused
	var bad_from := Vector2i(-1, -1)
	for i in CpzRules.ROWS:
		for j in range(1, CpzRules.COLS):
			if main.grid[i][j] != CpzRules.GAP and CpzRules.rank_of(main.grid[i][j]) != 1:
				bad_from = Vector2i(i, j)
				break
		if bad_from.x >= 0:
			break
	var gap0 := Vector2i(-1, -1)
	for i in CpzRules.ROWS:
		if main.grid[i][0] == CpzRules.GAP:
			gap0 = Vector2i(i, 0)
			break
	if gap0.x >= 0:
		ok(main.make_move(bad_from, gap0) == CpzRules.Check.KO, "scene refuses a non-Ace in column 0")
	main.open_menu("theme")
	ok(main.menu != null, "theme menu opens")
	main._select_theme("classic")
	ok(main.skin.theme_name == "classic", "theme switch applied")
	main.close_menu()
	main.queue_free()
	await process_frame
	CpzSkin._ui_tex.clear()
