# Chinese Puzzle — Godot 4.7.2 port

Port of the original Cocos2d-JS / CoffeeScript game (`Common/Bin/Data/coffee`, kept untouched for reference).

- Main scene: `scenes/main.tscn` (`scripts/main.gd`: board, input, menus, sound, save)
- Rules: `scripts/rules.gd` (deal, move validation, locked cards, win check)
- Theme/card rendering: `scripts/skin.gd` (regions of the original 960x640 atlases; card faces composed like `GameConfig.coffee`)
- Assets: `assets/` — atlases flattened from `Common/Bin/Design/960x640/*.psd` with `tools/extract_assets.py`; fonts, sounds, switch and lang files copied from `Common/Bin/Data`
- Test: `godot --headless -s res://tests/test_game.gd`
- Exports: `Web` preset (itch.io, `../itch/build.sh`) and `GamePix` preset (`../gamepix/build.sh`)
