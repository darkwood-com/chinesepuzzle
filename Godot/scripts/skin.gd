## Builds textures for one theme from the original 960x640 atlases
## (regions taken from Common/Bin/Design/export.jsx, card compositions from GameConfig.coffee).
class_name CpzSkin
extends RefCounted

const CARD_SIZE := Vector2i(52, 72)
const THEME_REGIONS := {
	"bg": Rect2i(0, 0, 960, 640),
	"cardplaybg": Rect2i(1056, 0, 52, 72),
	"cardboardempty": Rect2i(1152, 0, 52, 72),
	"cardboardyes": Rect2i(1248, 0, 52, 72),
	"cardboardno": Rect2i(1344, 0, 52, 72),
	"cardtouched": Rect2i(1440, 0, 52, 72),
	"newBtn": Rect2i(960, 316, 72, 72),
	"retryBtn": Rect2i(1056, 316, 72, 72),
	"hintBtn": Rect2i(1152, 316, 72, 72),
	"soundOnBtn": Rect2i(1248, 316, 72, 72),
	"soundOffBtn": Rect2i(1248, 416, 72, 72),
	"themeBtn": Rect2i(1344, 316, 72, 72),
	"undoBtn": Rect2i(1440, 316, 72, 72),
}
const UI_REGIONS := {
	"menuMask": Rect2i(0, 0, 960, 640),
	"menuContainer": Rect2i(960, 0, 192, 192),
	"menuItemYes": Rect2i(960, 192, 100, 36),
	"menuItemNo": Rect2i(960, 278, 100, 36),
	"menuItemOk": Rect2i(960, 366, 72, 72),
	"menuItemThemeSelect": Rect2i(960, 460, 180, 144),
	"classic": Rect2i(1140, 316, 180, 144),
	"chinese": Rect2i(1500, 28, 180, 144),
	"polkadots": Rect2i(1140, 460, 180, 144),
	"seamless": Rect2i(1320, 28, 180, 144),
	"shullshearts": Rect2i(1320, 172, 180, 144),
	"splash": Rect2i(1320, 316, 180, 144),
	"spring": Rect2i(1320, 460, 180, 144),
	"stripes": Rect2i(1500, 316, 180, 144),
	"vivid": Rect2i(1500, 460, 180, 144),
}
const CARD_BG := Rect2i(960, 0, 52, 72)
const SUIT_ROWS := [106, 146, 186, 224]
const RANK_X := [1032, 16, 1052, 14, 1070, 14, 1088, 14, 1106, 14, 1124, 14, 1142, 14, 1160, 14, 1178, 14, 1194, 18, 1216, 14, 1232, 20, 1254, 14]
const BIG := [Rect2i(960, 104, 30, 32), Rect2i(962, 140, 24, 34), Rect2i(960, 180, 28, 34), Rect2i(960, 220, 32, 32)]
const SMALL := [Rect2i(1002, 108, 18, 20), Rect2i(1004, 148, 16, 20), Rect2i(1004, 186, 18, 20), Rect2i(1002, 226, 20, 20)]

static var _ui_tex: Dictionary = {}

var theme_name := ""
var card_layout := false
var tex := {}          # name -> Texture2D
var faces := []        # card code (0..51) -> Texture2D

static func atlas(source: Texture2D, r: Rect2i) -> AtlasTexture:
	var a := AtlasTexture.new()
	a.atlas = source
	a.region = Rect2(r)
	return a

static func ui(name: String) -> Texture2D:
	if _ui_tex.is_empty():
		var src: Texture2D = load("res://assets/ui.png")
		for k in UI_REGIONS:
			_ui_tex[k] = atlas(src, UI_REGIONS[k])
	return _ui_tex[name]

func _init(p_theme: String, p_card_layout: bool) -> void:
	theme_name = p_theme
	card_layout = p_card_layout
	var src: Texture2D = load("res://assets/themes/%s.png" % p_theme)
	for k in THEME_REGIONS:
		tex[k] = atlas(src, THEME_REGIONS[k])
	var img: Image = src.get_image()
	if img.is_compressed():
		img.decompress()
	img.convert(Image.FORMAT_RGBA8)
	for suit in 4:
		for rank in range(1, 14):
			faces.append(ImageTexture.create_from_image(_compose(img, suit, rank)))

func _piece(img: Image, r: Rect2i) -> Image:
	return img.get_region(r)

## Pastes piece centered at (x, y) given in cocos coordinates (origin bottom-left).
func _put(dst: Image, piece: Image, x: float, y: float) -> void:
	var gy := CARD_SIZE.y - y
	var pos := Vector2i(roundi(x - piece.get_width() / 2.0), roundi(gy - piece.get_height() / 2.0))
	dst.blend_rect(piece, Rect2i(Vector2i.ZERO, piece.get_size()), pos)

func _compose(img: Image, suit: int, rank: int) -> Image:
	var card := _piece(img, CARD_BG)
	var rank_img := _piece(img, Rect2i(RANK_X[(rank - 1) * 2], SUIT_ROWS[suit], RANK_X[(rank - 1) * 2 + 1], 26))
	var small := _piece(img, SMALL[suit])
	var big := _piece(img, BIG[suit])
	var w := float(CARD_SIZE.x)
	var h := float(CARD_SIZE.y)
	if not card_layout:
		_put(card, rank_img, w / 4, 3 * h / 4)
		_put(card, big, 2 * w / 4, h / 4)
		_put(card, small, 3 * w / 4, 3 * h / 4)
		return card
	var pips := []
	match rank:
		1:
			_put(card, rank_img, w / 4, 3 * h / 4)
			_put(card, rank_img, 3 * w / 4, h / 4)
			pips = [[2, 2, 4]]
		2:
			pips = [[2, 1, 4], [2, 3, 4]]
		3:
			pips = [[2, 1, 4], [2, 2, 4], [2, 3, 4]]
		4:
			pips = [[1, 1, 4], [1, 3, 4], [3, 1, 4], [3, 3, 4]]
		5:
			pips = [[1, 1, 4], [1, 3, 4], [3, 1, 4], [3, 3, 4], [2, 2, 4]]
		6:
			pips = [[1, 1, 4], [1, 2, 4], [1, 3, 4], [3, 1, 4], [3, 2, 4], [3, 3, 4]]
		7:
			pips = [[1, 1, 4], [1, 2, 4], [1, 3, 4], [3, 1, 4], [3, 2, 4], [3, 3, 4], [2, 2, 4]]
		8:
			pips = [[1, 1, 4], [1, 2, 4], [1, 3, 4], [3, 1, 4], [3, 2, 4], [3, 3, 4], [2, 1.5, 4], [2, 2.5, 4]]
		9:
			pips = [[1, 1, 5], [1, 2, 5], [1, 3, 5], [1, 4, 5], [3, 1, 5], [3, 2, 5], [3, 3, 5], [3, 4, 5], [2, 1.5, 5]]
		10:
			pips = [[1, 1, 5], [1, 2, 5], [1, 3, 5], [1, 4, 5], [3, 1, 5], [3, 2, 5], [3, 3, 5], [3, 4, 5], [2, 1.5, 5], [2, 3.5, 5]]
		_:
			pips = [[1, 1, 2], [3, 1, 2]]
			_put(card, rank_img, w / 4, 4 * h / 5)
			_put(card, rank_img, 3 * w / 4, h / 5)
	for p in pips:
		_put(card, small, p[0] * w / 4, p[1] * h / p[2])
	return card
