## Chinese Puzzle game scene (port of GameScene / Game / GameLayout / Menu from the Cocos2d-JS version).
extends Node2D

const DESIGN := Vector2(960, 640)
const CARD := Vector2(52, 72)
const SPACE := Vector2(8, 8)
const GRID_POS := Vector2(8, 0)
const BUTTONS := ["newBtn", "retryBtn", "undoBtn", "hintBtn", "soundBtn", "themeBtn"]
const BUTTON_Y := [580, 476, 372, 268, 164, 60]   # cocos (bottom-left origin) coordinates, x = 902
const THEMES := ["classic", "chinese", "polkadots", "seamless", "shullshearts", "splash", "spring", "stripes", "vivid"]
const SAVE_PATH := "user://chinesepuzzle.json"
const SAVE_KEY := "chinesepuzzle.data"

enum Z { BG, UI, BOARD, CARD, MOVE_CARD, HINT_CARD }

var conf := {"theme": "chinese", "card_layout": false, "sound_on": true, "init_board": [], "moves": []}
var lang := {}
var skin: CpzSkin
var board := []            # [i][j] -> CpzCard (card or slot), mirrors CpzRules board
var grid := []             # [i][j] -> int code (CpzRules)
var root := Node2D.new()   # 960x640 design space, centered in the viewport
var bg_pattern := TextureRect.new()
var bg := Sprite2D.new()
var buttons := {}
var touch_last := Sprite2D.new()
var switch_slot: CpzCard
var drag_card: CpzCard = null
var drag_from := Vector2i(-1, -1)
var hint_slot: CpzCard = null
var last_touch := Vector2.ZERO
var busy := 0
var menu: Control = null
var ui_layer := CanvasLayer.new()   # dialogs (GUI controls) above the board
var music := AudioStreamPlayer.new()
var sfx := {}
var bgm_theme := 0
var rng := RandomNumberGenerator.new()
var won_shown := false
var game_started := false

func _ready() -> void:
	rng.randomize()
	_load_lang()
	_load_conf()
	bg_pattern.texture = load("res://assets/bgPattern.png")
	bg_pattern.stretch_mode = TextureRect.STRETCH_TILE
	bg_pattern.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(bg_pattern)
	add_child(root)
	add_child(ui_layer)
	bg.centered = false
	bg.z_index = Z.BG
	root.add_child(bg)
	for b in BUTTONS:
		var s := Sprite2D.new()
		s.position = Vector2(902, DESIGN.y - BUTTON_Y[BUTTONS.find(b)])
		s.scale = Vector2(0.75, 0.75)
		s.z_index = Z.UI
		root.add_child(s)
		buttons[b] = s
	touch_last.visible = false
	touch_last.z_index = Z.HINT_CARD
	root.add_child(touch_last)
	switch_slot = CpzCard.new(true)
	switch_slot.visible = false
	switch_slot.z_index = Z.BOARD
	root.add_child(switch_slot)
	for i in CpzRules.ROWS:
		board.append([])
		for j in CpzRules.COLS:
			board[i].append(null)
	add_child(music)
	for n in ["card_move", "card_undo", "menu_pop", "menu_push", "menu_select", "shuffle"]:
		var p := AudioStreamPlayer.new()
		p.stream = load("res://assets/sound/%s.mp3" % n)
		add_child(p)
		sfx[n] = p
	get_viewport().size_changed.connect(_reshape)
	_reshape()
	_apply_skin()
	if conf["init_board"].is_empty():
		_rand_init_board()
	_load_board()
	layout(true)
	play_background_music(conf["sound_on"])
	GPX.game_start()
	game_started = true

# ---------------------------------------------------------------- config / save

func _load_lang() -> void:
	var code := OS.get_locale_language()
	if OS.has_feature("web") and GPX.gpx != null:
		code = str(GPX.lang()).substr(0, 2)
	if code not in ["en", "fr", "de"]:
		code = "en"
	var f := FileAccess.open("res://assets/lang/%s.json" % code, FileAccess.READ)
	lang = JSON.parse_string(f.get_as_text())

func tr_key(key: String) -> String:
	return lang.get(key, key)

## Web builds save in window.localStorage (synchronised by GamePix); other platforms in user://.
func _storage_get() -> String:
	if OS.has_feature("web"):
		var ls = JavaScriptBridge.get_interface("localStorage")
		var v = ls.getItem(SAVE_KEY) if ls else null
		return str(v) if v != null else ""
	if not FileAccess.file_exists(SAVE_PATH):
		return ""
	return FileAccess.get_file_as_string(SAVE_PATH)

func _storage_set(text: String) -> void:
	if OS.has_feature("web"):
		var ls = JavaScriptBridge.get_interface("localStorage")
		if ls:
			ls.setItem(SAVE_KEY, text)
		return
	var f := FileAccess.open(SAVE_PATH, FileAccess.WRITE)
	if f:
		f.store_string(text)

func _load_conf() -> void:
	var text := _storage_get()
	if text == "":
		return
	var data = JSON.parse_string(text)
	if typeof(data) != TYPE_DICTIONARY:
		return
	if data.get("theme", "") in THEMES:
		conf["theme"] = data["theme"]
	conf["card_layout"] = bool(data.get("card_layout", false))
	conf["sound_on"] = bool(data.get("sound_on", true))
	var ib = data.get("init_board", [])
	if typeof(ib) == TYPE_ARRAY and ib.size() == CpzRules.ROWS:
		var b := []
		for row in ib:
			var r := []
			for c in row:
				r.append(int(c))
			b.append(r)
		conf["init_board"] = b
		var moves := []
		for m in data.get("moves", []):
			moves.append([Vector2i(int(m[0]), int(m[1])), Vector2i(int(m[2]), int(m[3]))])
		conf["moves"] = moves

func save_conf() -> void:
	var moves := []
	for m in conf["moves"]:
		moves.append([m[0].x, m[0].y, m[1].x, m[1].y])
	var data := {"theme": conf["theme"], "card_layout": conf["card_layout"], "sound_on": conf["sound_on"],
		"init_board": conf["init_board"], "moves": moves}
	_storage_set(JSON.stringify(data))

# ---------------------------------------------------------------- layout

func _reshape() -> void:
	var vp := get_viewport_rect().size
	root.position = ((vp - DESIGN) / 2).floor()
	ui_layer.offset = root.position
	bg_pattern.position = Vector2.ZERO
	bg_pattern.size = vp

func board_point(c: Vector2i) -> Vector2:
	return Vector2(GRID_POS.x + (0.5 + c.y) * (CARD.x + SPACE.x),
		DESIGN.y - (GRID_POS.y + (0.5 + c.x) * (CARD.y + SPACE.y)))

func grid_coord(p: Vector2) -> Vector2i:
	var cy := DESIGN.y - p.y
	return Vector2i(floori((cy - GRID_POS.y - 0.5) / (CARD.y + SPACE.y)), floori((p.x - GRID_POS.x - 0.5) / (CARD.x + SPACE.x)))

func _apply_skin() -> void:
	skin = CpzSkin.new(conf["theme"], conf["card_layout"])
	bg.texture = skin.tex["bg"]
	for b in BUTTONS:
		var key: String = b
		if b == "soundBtn":
			key = "soundOnBtn" if conf["sound_on"] else "soundOffBtn"
		buttons[b].texture = skin.tex[key]
	touch_last.texture = skin.tex["cardtouched"]
	switch_slot.set_skin(skin)
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			if board[i][j]:
				board[i][j].set_skin(skin)

func _rand_init_board() -> void:
	conf["init_board"] = CpzRules.deal(rng)
	conf["moves"] = []

func _load_board() -> void:
	var cards := []
	var slots := []
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			var n: CpzCard = board[i][j]
			if n:
				(slots if n.is_slot else cards).append(n)
	grid = CpzRules.replay(conf["init_board"], conf["moves"])
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			var code: int = grid[i][j]
			var node: CpzCard = null
			if code == CpzRules.GAP:
				node = slots.pop_back() if not slots.is_empty() else null
				if node == null:
					node = CpzCard.new(true)
			else:
				for c in cards:
					if c.code == code:
						node = c
						break
				if node:
					cards.erase(node)
				else:
					node = CpzCard.new(false, code)
			node.locked = false
			if node.is_slot:
				node.state = CpzCard.SlotState.EMPTY
			board[i][j] = node
			if node.get_parent() == null:
				node.z_index = Z.BOARD if node.is_slot else Z.CARD
				node.position = board_point(Vector2i(i, j))
				node.set_skin(skin)
				root.add_child(node)
	won_shown = false

func layout(anim: bool) -> void:
	touch_last.visible = false
	switch_slot.visible = false
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			var c := Vector2i(i, j)
			var node: CpzCard = board[i][j]
			var target := board_point(c)
			if node.is_slot:
				node.position = target
				continue
			if anim:
				var tw := _tween()
				tw.tween_interval(0.05 * (7 - i + j - 1))
				if node.position != target:
					tw.tween_property(node, "position", target, 1.0)
				if not node.face_up:
					tw.tween_property(node, "scale:x", 0.0, 0.1)
					tw.tween_callback(node.set_face_up.bind(true))
					tw.tween_property(node, "scale:x", 1.0, 0.1)
			else:
				node.position = target
				node.set_face_up(true)
		lock_line(i)

func _tween() -> Tween:
	var tw := create_tween()
	busy += 1
	tw.finished.connect(func(): busy -= 1)
	return tw

func is_busy() -> bool:
	return busy > 0

func lock_line(i: int) -> void:
	if i < 0 or i >= CpzRules.ROWS:
		return
	var mask := CpzRules.locked_mask(grid, i)
	for j in CpzRules.COLS:
		if not board[i][j].is_slot:
			board[i][j].locked = mask[j]

func get_card(c: Vector2i) -> CpzCard:
	return board[c.x][c.y] if CpzRules.in_board(c.x, c.y) else null

# ---------------------------------------------------------------- game actions

func new_game() -> void:
	_rand_init_board()
	retry_game()

func retry_game() -> void:
	conf["moves"] = []
	_load_board()
	layout(true)
	save_conf()
	play_sound("shuffle")

func make_move(from: Vector2i, to: Vector2i) -> int:
	var check := CpzRules.check_move(grid, from, to)
	var c_from := get_card(from)
	if check == CpzRules.Check.OK:
		var c_switch := get_card(to)
		board[to.x][to.y] = c_from
		board[from.x][from.y] = c_switch
		CpzRules.swap(grid, from, to)
		var tw := _tween()
		tw.tween_property(c_from, "position", board_point(to), 0.5)
		tw.tween_callback(_make_move_end)
		tw.tween_callback(play_sound.bind("card_move"))
		c_switch.position = board_point(from)
		c_switch.set_state(CpzCard.SlotState.EMPTY)
		switch_slot.position = board_point(to)
		lock_line(to.x)
		conf["moves"].append([from, to])
		save_conf()
		tw.tween_callback(_check_win)
	elif c_from and not c_from.is_slot:
		var tw := _tween()
		tw.tween_property(c_from, "position", board_point(from), 0.5)
		tw.tween_callback(_make_move_end)
	else:
		_make_move_end()
	return check

func undo_move() -> void:
	if conf["moves"].is_empty() or is_busy():
		return
	var m = conf["moves"].pop_back()
	var from: Vector2i = m[0]
	var to: Vector2i = m[1]
	var c_to := get_card(to)
	var c_switch := get_card(from)
	board[from.x][from.y] = c_to
	board[to.x][to.y] = c_switch
	CpzRules.swap(grid, from, to)
	var tw := _tween()
	tw.tween_property(c_to, "position", board_point(from), 0.5)
	tw.tween_callback(_make_move_end)
	tw.tween_callback(play_sound.bind("card_undo"))
	c_switch.position = board_point(to)
	c_switch.set_state(CpzCard.SlotState.EMPTY)
	switch_slot.position = board_point(from)
	switch_slot.visible = true
	lock_line(from.x)
	lock_line(to.x)
	save_conf()

func _make_move_end() -> void:
	switch_slot.visible = false
	if drag_card:
		drag_card.z_index = Z.CARD
		drag_card = null
	_hint_move()

func _check_win() -> void:
	if not won_shown and CpzRules.is_won(grid):
		won_shown = true
		GPX.happyMoment("puzzle_solved")
		open_menu("win")

# ---------------------------------------------------------------- input

func _unhandled_input(event: InputEvent) -> void:
	if menu != null:
		return
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		var p: Vector2 = root.make_input_local(event).position
		if event.pressed:
			tap_down(p)
		else:
			tap_up(p)
	elif event is InputEventMouseMotion and (event.button_mask & MOUSE_BUTTON_MASK_LEFT):
		tap_move(root.make_input_local(event).position)

func _card_at(p: Vector2) -> CpzCard:
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			var n: CpzCard = board[i][j]
			if n.get_rect().has_point(p):
				return n
	return null

func _button_at(p: Vector2) -> String:
	for b in BUTTONS:
		var s: Sprite2D = buttons[b]
		var size := s.texture.get_size() * 0.75 * 2.0
		if Rect2(s.position - size / 2, size).has_point(p):
			return b
	return ""

func tap_down(p: Vector2) -> void:
	var b := _button_at(p)
	if b != "":
		var s: Sprite2D = buttons[b]
		var tw := create_tween()
		tw.tween_property(s, "scale", Vector2.ONE, 0.1).set_ease(Tween.EASE_IN)
		tw.tween_callback(_action_button.bind(b))
		tw.tween_property(s, "scale", Vector2(0.75, 0.75), 0.1).set_ease(Tween.EASE_OUT)
		return
	if drag_card == null and not is_busy():
		var tap := _card_at(p)
		if tap and tap.is_slot and touch_last.visible:
			var from := grid_coord(touch_last.position)
			var to := grid_coord(tap.position)
			if CpzRules.check_move(grid, from, to) == CpzRules.Check.OK:
				switch_slot.position = touch_last.position
				switch_slot.visible = true
				make_move(from, to)
		if tap and not tap.is_slot and not tap.locked:
			drag_from = grid_coord(tap.position)
			drag_card = tap
			var pos := board_point(drag_from)
			switch_slot.position = pos
			switch_slot.visible = true
			touch_last.position = pos
			drag_card.z_index = Z.MOVE_CARD
		touch_last.visible = false
	_hint_move()
	last_touch = p

func tap_move(p: Vector2) -> void:
	touch_last.visible = false
	if drag_card:
		drag_card.position += p - last_touch
	_hint_move()
	last_touch = p

func tap_up(p: Vector2) -> void:
	if drag_card:
		var target := _drop_slot(drag_card)
		var to := grid_coord(target.position if target else drag_card.position)
		if target == null:
			to = drag_from
		var check := make_move(drag_from, to)
		if check != CpzRules.Check.OK and drag_card and drag_card.position == touch_last.position:
			touch_last.visible = true
		drag_card = null
	last_touch = p

## Nearest board slot intersecting the dragged card (GameControlNode.checkRectNode).
func _drop_slot(card: CpzCard) -> CpzCard:
	var rect := card.get_rect()
	var best: CpzCard = null
	var best_d := -1.0
	for i in CpzRules.ROWS:
		for j in CpzRules.COLS:
			var n: CpzCard = board[i][j]
			if not n.is_slot:
				continue
			var r := n.get_rect()
			if r.intersects(rect):
				var d := rect.position.distance_squared_to(r.position)
				if best_d < 0 or d < best_d:
					best_d = d
					best = n
	return best

func _hint_move() -> void:
	if drag_card:
		var to := _drop_slot(drag_card)
		if to:
			if hint_slot and hint_slot != to:
				hint_slot.set_state(CpzCard.SlotState.EMPTY)
			hint_slot = to
			var ok := CpzRules.check_move(grid, drag_from, grid_coord(to.position)) == CpzRules.Check.OK
			hint_slot.set_state(CpzCard.SlotState.YES if ok else CpzCard.SlotState.NO)
			return
	if hint_slot:
		hint_slot.set_state(CpzCard.SlotState.EMPTY)
		hint_slot = null

func _action_button(b: String) -> void:
	match b:
		"newBtn": open_menu("new")
		"retryBtn": open_menu("retry")
		"undoBtn":
			undo_move()
		"hintBtn": open_menu("hint")
		"soundBtn":
			conf["sound_on"] = not conf["sound_on"]
			save_conf()
			play_background_music(conf["sound_on"])
			buttons["soundBtn"].texture = skin.tex["soundOnBtn" if conf["sound_on"] else "soundOffBtn"]
		"themeBtn": open_menu("theme")

# ---------------------------------------------------------------- sound

func play_sound(n: String) -> void:
	if conf["sound_on"] and sfx.has(n):
		sfx[n].play()

func play_background_music(play: bool) -> void:
	if play and conf["sound_on"]:
		var next := bgm_theme % 3 + 1
		var stream: AudioStreamMP3 = load("res://assets/sound/bgm%d.mp3" % next)
		stream.loop = true
		music.stream = stream
		music.volume_db = linear_to_db(0.5)
		music.play()
		bgm_theme = next
	elif bgm_theme != 0:
		music.stop()

# ---------------------------------------------------------------- menus

func _font(size: int) -> LabelSettings:
	var ls := LabelSettings.new()
	ls.font = load("res://assets/fonts/arial32.fnt")
	ls.font_size = size
	return ls

func _make_box(size: Vector2, title: String) -> Control:
	menu = Control.new()
	menu.size = DESIGN
	menu.mouse_filter = Control.MOUSE_FILTER_STOP
	ui_layer.add_child(menu)
	var mask := TextureRect.new()
	mask.texture = CpzSkin.ui("menuMask")
	mask.mouse_filter = Control.MOUSE_FILTER_IGNORE
	menu.add_child(mask)
	var box := NinePatchRect.new()
	box.texture = CpzSkin.ui("menuContainer")
	box.patch_margin_left = 64
	box.patch_margin_top = 64
	box.patch_margin_right = 64
	box.patch_margin_bottom = 64
	box.size = size
	box.position = (DESIGN - size) / 2
	menu.add_child(box)
	var lt := Label.new()
	lt.text = title
	lt.label_settings = _font(32)
	lt.position = Vector2(40, 40 - 32)
	box.add_child(lt)
	var ok := TextureButton.new()
	ok.texture_normal = CpzSkin.ui("menuItemOk")
	ok.ignore_texture_size = true
	ok.stretch_mode = TextureButton.STRETCH_SCALE
	ok.size = Vector2(54, 54)
	ok.position = Vector2(size.x - 10 - 27, 10 - 27)
	ok.pressed.connect(close_menu)
	ok.name = "Ok"
	box.add_child(ok)
	play_sound("menu_push")
	return box

func _add_button(box: Control, tex: Texture2D, center: Vector2, cb: Callable, label := "") -> TextureButton:
	var b := TextureButton.new()
	b.texture_normal = tex
	b.position = center - tex.get_size() / 2
	b.pressed.connect(cb)
	box.add_child(b)
	return b

func close_menu() -> void:
	if menu:
		menu.queue_free()
		menu = null
		play_sound("menu_pop")

func open_menu(kind: String) -> void:
	if menu:
		close_menu()
	match kind:
		"new", "retry", "win":
			var keys := {"new": "menu.newgame", "retry": "menu.retrygame", "win": "menu.wingame"}
			var k: String = keys[kind]
			var box := _make_box(Vector2(600, 400), tr_key(k + ".title"))
			var content := Label.new()
			content.text = tr_key(k + ".content")
			content.label_settings = _font(26)
			content.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
			content.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
			content.size = Vector2(520, 120)
			content.position = Vector2(40, 140)
			box.add_child(content)
			var yes_cb := func():
				close_menu()
				if kind == "retry":
					retry_game()
				else:
					new_game()
			_add_button(box, CpzSkin.ui("menuItemYes"), Vector2(400, 300), yes_cb).name = "Yes"
			_add_button(box, CpzSkin.ui("menuItemNo"), Vector2(200, 300), close_menu).name = "No"
		"hint":
			var box := _make_box(Vector2(800, 500), tr_key("menu.hintgame.title"))
			var sc := ScrollContainer.new()
			sc.position = Vector2(50, 80)
			sc.size = Vector2(700, 380)
			sc.horizontal_scroll_mode = ScrollContainer.SCROLL_MODE_DISABLED
			box.add_child(sc)
			var content := Label.new()
			content.text = tr_key("menu.hintgame.content")
			content.label_settings = _font(22)
			content.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
			content.custom_minimum_size = Vector2(680, 0)
			sc.add_child(content)
		"theme":
			var box := _make_box(Vector2(600, 600), tr_key("menu.themegame.title"))
			var scale := 0.8
			var cell := Vector2(180, 144) * scale
			var origin := Vector2((600 - cell.x * 3 - 20) / 2, 80)
			for t in THEMES.size():
				var name: String = THEMES[t]
				var b := TextureButton.new()
				b.texture_normal = CpzSkin.ui(name)
				b.ignore_texture_size = true
				b.stretch_mode = TextureButton.STRETCH_SCALE
				b.size = cell
				b.position = origin + Vector2((t % 3) * (cell.x + 10), (t / 3) * (cell.y + 10))
				b.pressed.connect(_select_theme.bind(name))
				b.name = "Theme_" + name
				box.add_child(b)
				if name == conf["theme"]:
					var sel := TextureRect.new()
					sel.texture = CpzSkin.ui("menuItemThemeSelect")
					sel.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
					sel.size = cell
					sel.mouse_filter = Control.MOUSE_FILTER_IGNORE
					b.add_child(sel)
			var sw := TextureButton.new()
			sw.texture_normal = load("res://assets/switch/switch-on.png" if conf["card_layout"] else "res://assets/switch/switch-off.png")
			sw.position = Vector2(80, 540 - 16)
			sw.pressed.connect(_toggle_card_layout)
			sw.name = "Switch"
			box.add_child(sw)
			var sl := Label.new()
			sl.text = tr_key("menu.themegame.cardlayout.on" if conf["card_layout"] else "menu.themegame.cardlayout.off")
			sl.label_settings = _font(24)
			sl.position = Vector2(150, 540 - 16)
			box.add_child(sl)

func _select_theme(name: String) -> void:
	play_sound("menu_select")
	conf["theme"] = name
	save_conf()
	_apply_skin()
	open_menu("theme")

func _toggle_card_layout() -> void:
	conf["card_layout"] = not conf["card_layout"]
	save_conf()
	_apply_skin()
	open_menu("theme")
