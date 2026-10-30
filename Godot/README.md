# Chinese Puzzle — Godot 4.7.2 port

Port of the original Cocos2d-JS / CoffeeScript game (original Cocos2d sources removed from the repo, see git history before this commit).

- Main scene: `scenes/main.tscn` (`scripts/main.gd`: board, input, menus, sound, save)
- Rules: `scripts/rules.gd` (deal, move validation, locked cards, win check)
- Theme/card rendering: `scripts/skin.gd` (regions of the original 960x640 atlases; card faces composed like `GameConfig.coffee`)
- Assets: `assets/` — atlases flattened from `../Design/960x640/*.psd` with `tools/extract_assets.py`; fonts, sounds, switch and lang files copied from the original game data
- Test: `godot --headless -s res://tests/test_game.gd`
- Exports: `Web` preset (itch.io, `../itch/build.sh`) and `GamePix` preset (`../gamepix/build.sh`)
