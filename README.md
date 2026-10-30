# Chinese Puzzle

Solitaire-style card puzzle by Darkwood, built with **Godot 4.7.2** (GDScript, GL Compatibility renderer, landscape 960x640).
The original Cocos2d-JS / CoffeeScript version has been removed; it lives in the git history.

## Layout

- `Godot/` — the Godot project (`scenes/`, `scripts/`, `assets/`, `tests/`, GamePix SDK addon in `addons/gpx-godot-plugin`)
- `Godot/assets/platform/` — app icons (iOS sizes, Android adaptive foreground/background/monochrome) generated from `assets/icon.png`
- `Design/` — original PSD/AI art sources (`Godot/tools/extract_assets.py` flattens the 960x640 atlases)
- `build/build.sh` — native exports (Android, macOS, iOS)
- `gamepix/`, `itch/` — web builds and store assets; `tools/` — headless Chrome smoke/screenshot scripts
- `Exports/` — build outputs (gitignored)

## Run

```sh
cd Godot
godot              # open the editor, F5 to play
godot --path . scenes/main.tscn   # run the game directly
```

## Test

```sh
cd Godot && godot --headless -s res://tests/test_game.gd
```

## Build

| Platform | Command | Output |
|---|---|---|
| itch.io (HTML5) | `itch/build.sh` | `Exports/chinesepuzzle-itch-html5.zip` |
| GamePix (HTML5 + SDK) | `gamepix/build.sh` | `Exports/chinesepuzzle-gamepix.zip` |
| Android APK + AAB (debug-signed) | `build/build.sh android` | `Exports/Android/chinesepuzzle-debug.{apk,aab}` |
| macOS (universal, ad-hoc signed) | `build/build.sh macos` | `Exports/macOS/ChinesePuzzle.zip` |
| iOS / iPadOS (universal) Xcode project | `build/build.sh ios` | `Exports/chinesepuzzle-ios-xcode.zip` |

`build/build.sh all` runs the three native targets. Settings come from env vars or a gitignored `build/local.env`
(see `build/local.env.example`): `GODOT`, `JAVA_HOME` (JDK 17), `ANDROID_HOME`, `GODOT_ANDROID_KEYSTORE_DEBUG_*`, `IOS_TEAM_ID`.

Requirements: Godot 4.7.2 + matching export templates, and for Android a JDK 17 and the Android SDK
(platform-tools, build-tools, platform 35). The Android export uses a Gradle build; the build template is installed
into `Godot/android/` on first run (gitignored). A debug keystore is created at `~/.android/debug.keystore` if missing.

The GamePix SDK is only active on web builds with the GamePix shell; every call is a no-op on native platforms.

## Store publishing — remaining steps

- **Google Play**: create a release (upload) keystore — never commit it — and export with
  `GODOT_ANDROID_KEYSTORE_RELEASE_PATH/USER/PASSWORD` set, using `--export-release` with `gradle_build/export_format=1` (AAB).
  Bump `version/code` in the Android preset for each upload.
- **iOS / iPadOS**: on a Mac with Xcode and an Apple Developer account, unzip the Xcode project, set the Team
  (or export with `IOS_TEAM_ID`), then Archive and upload to App Store Connect. Linux cannot build the `.ipa`.
- **macOS**: the app is ad-hoc signed only. For distribution, sign with a Developer ID (or Mac App Store) certificate
  and notarize with an Apple account (Godot can do this from a Mac, or use `codesign` + `notarytool`).
