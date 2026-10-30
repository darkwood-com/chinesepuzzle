## Pure game rules of Chinese Puzzle (ported from Common/Bin/Data/coffee/Game/Game.coffee).
##
## Board: 8 rows (i) x 14 columns (j). Two 52-card decks (104 cards) are dealt in
## columns 1..13; column 0 starts with 8 empty slots (gaps).
## A card is encoded as suit * 13 + (rank - 1) (suit 0..3, rank 1..13); a gap is -1.
## A move takes a card onto a gap and the gap takes the card's former place:
## - gap in column 0: only an Ace may go there;
## - otherwise the card left of the gap must be a card of the same suit and rank - 1.
class_name CpzRules
extends RefCounted

const ROWS := 8
const COLS := 14
const GAP := -1

enum Check { FROM, TO_BEFORE, KO, OK }

static func suit_of(card: int) -> int:
	return card / 13

static func rank_of(card: int) -> int:
	return card % 13 + 1

static func make_card(suit: int, rank: int) -> int:
	return suit * 13 + rank - 1

static func is_next_to(card: int, before: int) -> bool:
	return card >= 0 and before >= 0 and suit_of(card) == suit_of(before) and rank_of(card) == rank_of(before) + 1

static func empty_board() -> Array:
	var b := []
	for i in ROWS:
		var row := []
		row.resize(COLS)
		row.fill(GAP)
		b.append(row)
	return b

## Shuffled deal like _randInitBoard: two decks into columns 1..13.
static func deal(rng: RandomNumberGenerator) -> Array:
	var deck := []
	for k in 2:
		for c in 52:
			deck.append(c)
	# Fisher-Yates with the given rng (deterministic for a seed)
	for n in range(deck.size() - 1, 0, -1):
		var m := rng.randi_range(0, n)
		var t = deck[n]
		deck[n] = deck[m]
		deck[m] = t
	var b := empty_board()
	var k := 0
	for i in ROWS:
		for j in range(1, COLS):
			b[i][j] = deck[k]
			k += 1
	return b

static func copy_board(b: Array) -> Array:
	return b.duplicate(true)

static func in_board(i: int, j: int) -> bool:
	return i >= 0 and i < ROWS and j >= 0 and j < COLS

## from/to are Vector2i(i, j)
static func check_move(b: Array, from: Vector2i, to: Vector2i) -> int:
	if not in_board(from.x, from.y) or b[from.x][from.y] == GAP:
		return Check.FROM
	if not in_board(to.x, to.y) or b[to.x][to.y] != GAP:
		return Check.FROM
	var card: int = b[from.x][from.y]
	if to.y == 0:
		if rank_of(card) == 1:
			return Check.OK
	else:
		var before: int = b[to.x][to.y - 1]
		if before == GAP:
			return Check.TO_BEFORE
		if is_next_to(card, before):
			return Check.OK
	return Check.KO

static func swap(b: Array, from: Vector2i, to: Vector2i) -> void:
	var t = b[to.x][to.y]
	b[to.x][to.y] = b[from.x][from.y]
	b[from.x][from.y] = t

## Replays saved moves on an initial board.
static func replay(init_board: Array, moves: Array) -> Array:
	var b := copy_board(init_board)
	for m in moves:
		swap(b, m[0], m[1])
	return b

## Locked = in place: row starts with an Ace in column 0 and continues in sequence.
static func locked_mask(b: Array, i: int) -> Array:
	var mask := []
	mask.resize(COLS)
	mask.fill(false)
	for j in COLS:
		var card: int = b[i][j]
		if card == GAP:
			continue
		if j == 0 and rank_of(card) == 1:
			mask[j] = true
		elif j > 0 and mask[j - 1] and is_next_to(card, b[i][j - 1]):
			mask[j] = true
	return mask

static func is_won(b: Array) -> bool:
	for i in ROWS:
		var mask := locked_mask(b, i)
		for j in 13:
			if not mask[j]:
				return false
	return true

static func legal_moves(b: Array) -> Array:
	var res := []
	for i in ROWS:
		for j in COLS:
			if b[i][j] != GAP:
				continue
			var to := Vector2i(i, j)
			for fi in ROWS:
				for fj in COLS:
					var from := Vector2i(fi, fj)
					if b[fi][fj] != GAP and check_move(b, from, to) == Check.OK:
						res.append([from, to])
	return res
