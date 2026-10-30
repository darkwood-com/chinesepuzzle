## A board cell node: either a playing card or an empty board slot (CardPlay / CardBoard).
class_name CpzCard
extends Node2D

enum SlotState { EMPTY, YES, NO }

var is_slot := false
var code := -1
var face_up := false
var locked := false
var state := SlotState.EMPTY
var skin: CpzSkin
var sprite := Sprite2D.new()

func _init(p_is_slot: bool, p_code: int = -1) -> void:
	is_slot = p_is_slot
	code = p_code
	add_child(sprite)

func set_skin(s: CpzSkin) -> void:
	skin = s
	refresh()

func set_face_up(v: bool) -> void:
	face_up = v
	refresh()

func set_state(s: int) -> void:
	if state != s:
		state = s
		refresh()

func refresh() -> void:
	if skin == null:
		return
	if is_slot:
		match state:
			SlotState.YES: sprite.texture = skin.tex["cardboardyes"]
			SlotState.NO: sprite.texture = skin.tex["cardboardno"]
			_: sprite.texture = skin.tex["cardboardempty"]
	else:
		sprite.texture = skin.faces[code] if face_up else skin.tex["cardplaybg"]

func get_rect() -> Rect2:
	return Rect2(position - Vector2(CpzSkin.CARD_SIZE) / 2, Vector2(CpzSkin.CARD_SIZE))
