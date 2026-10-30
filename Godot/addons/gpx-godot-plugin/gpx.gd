extends Node

var gpx = null
var _gpx_interstitial_cb = null
var _gpx_interstitial_cb_fn = null
var _gpx_reward_cb = null
var _gpx_reward_cb_success_fn = null
var _gpx_reward_cb_fail_fn = null

func _ready():
	if OS.has_feature("web"):
		# Builds without the SDK shell (e.g. itch.io) must not log errors: probe first.
		if str(JavaScriptBridge.eval("typeof window.GamePix", true)) != "object":
			print("GamePix SDK not present, running standalone")
			return
		gpx = JavaScriptBridge.get_interface("GamePix")
		_gpx_interstitial_cb = JavaScriptBridge.create_callback(_interstitial_callback)
		_gpx_reward_cb = JavaScriptBridge.create_callback(_reward_callback)
		_register_pause_resume()

func lang():
	if gpx != null:
		return gpx.lang()
	return "en"

func setItem(key, value):
	if gpx != null:
		gpx.localStorage.setItem(key, value)

func getItem(key):
	if gpx != null:
		return gpx.localStorage.getItem(key)
	
	return null

func updateScore(score):
	if gpx != null:
		gpx.updateScore(score)

func updateLevel(level):
	if gpx != null:
		gpx.updateLevel(level)

func happyMoment(type := ""):
	# v3 SDK: GamePix.happyMoment(type?) (requires lifecycle.loaded() to have completed)
	_js("GamePix.lifecycle.loaded().then(function(){GamePix.happyMoment(%s);})" % (JSON.stringify(type) if type != "" else ""))

# --- GamePix SDK v3 lifecycle (manual mode, enabled in index.html via window.GamePixConfig) ---
# The HTML shell reports loading progress (lifecycle.loading) and readiness (lifecycle.loaded);
# the game reports the start of real gameplay here.
var _pause_cb = null
var _resume_cb = null
var _game_started := false

func game_start():
	if _game_started:
		return
	_game_started = true
	_js("GamePix.lifecycle.loading(100);GamePix.lifecycle.loaded().then(function(){GamePix.lifecycle.gameStart();})")

func _js(code: String) -> void:
	if gpx != null:
		JavaScriptBridge.eval("try{if(window.GamePix&&GamePix.lifecycle){%s}}catch(e){console.warn('GamePix:',e);}" % code)

func _register_pause_resume():
	if gpx == null:
		return
	_pause_cb = JavaScriptBridge.create_callback(_on_gpx_pause)
	_resume_cb = JavaScriptBridge.create_callback(_on_gpx_resume)
	var events = gpx.events
	if events != null:
		events.on("pause", _pause_cb)
		events.on("resume", _resume_cb)

# Pause gameplay and mute all audio (idempotent).
func _on_gpx_pause(_args):
	get_tree().paused = true
	AudioServer.set_bus_mute(0, true)

func _on_gpx_resume(_args):
	get_tree().paused = false
	AudioServer.set_bus_mute(0, false)

func interstitialAd(fn = null):
	if gpx != null:
		_gpx_interstitial_cb_fn = fn
		get_tree().paused = true
		gpx.interstitialAd().then(_gpx_interstitial_cb)
	elif fn != null:
		fn.call()

func _interstitial_callback(args):
	if _gpx_interstitial_cb_fn != null:
		_gpx_interstitial_cb_fn.call()
	_gpx_interstitial_cb_fn = null
	get_tree().paused = false

func rewardAd(success = null, fail = null):
	if gpx != null:
		_gpx_reward_cb_success_fn = success
		_gpx_reward_cb_fail_fn = fail
		get_tree().paused = true
		gpx.rewardAd().then(_gpx_reward_cb)
	elif success != null:
		success.call()
	elif fail != null:
		fail.call()

func _reward_callback(args):
	if args[0].success:
		_gpx_reward_cb_success_fn.call()
	else:
		_gpx_reward_cb_fail_fn.call()

	_gpx_reward_cb_success_fn = null
	_gpx_reward_cb_fail_fn = null
	get_tree().paused = false
