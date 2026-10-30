#!/usr/bin/env bash
# Native exports of the Godot project into Exports/.
#   build/build.sh android|macos|ios|all
# Config via env vars or a gitignored build/local.env (see build/local.env.example).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
[ -f "$ROOT/build/local.env" ] && source "$ROOT/build/local.env"
GODOT="${GODOT:-$HOME/.local/bin/godot}"
export JAVA_HOME="${JAVA_HOME:-$HOME/opt/jdk17}"
export ANDROID_HOME="${ANDROID_HOME:-$HOME/opt/android-sdk}"
export PATH="$JAVA_HOME/bin:$PATH"
# Debug keystore (never committed). Godot reads these env vars.
export GODOT_ANDROID_KEYSTORE_DEBUG_PATH="${GODOT_ANDROID_KEYSTORE_DEBUG_PATH:-$HOME/.android/debug.keystore}"
export GODOT_ANDROID_KEYSTORE_DEBUG_USER="${GODOT_ANDROID_KEYSTORE_DEBUG_USER:-androiddebugkey}"
export GODOT_ANDROID_KEYSTORE_DEBUG_PASSWORD="${GODOT_ANDROID_KEYSTORE_DEBUG_PASSWORD:-android}"
OUT="$ROOT/Exports"
cd "$ROOT/Godot"

godot() { "$GODOT" --headless "$@"; }

ensure_keystore() {
  [ -f "$GODOT_ANDROID_KEYSTORE_DEBUG_PATH" ] && return
  mkdir -p "$(dirname "$GODOT_ANDROID_KEYSTORE_DEBUG_PATH")"
  keytool -genkeypair -keystore "$GODOT_ANDROID_KEYSTORE_DEBUG_PATH" -storepass "$GODOT_ANDROID_KEYSTORE_DEBUG_PASSWORD" \
    -alias "$GODOT_ANDROID_KEYSTORE_DEBUG_USER" -keypass "$GODOT_ANDROID_KEYSTORE_DEBUG_PASSWORD" \
    -keyalg RSA -keysize 2048 -validity 10000 -dname "CN=Android Debug,O=Android,C=US"
}

# The preset exports an APK; for the AAB we patch a temporary copy of the format option.
android() {
  ensure_keystore
  local tpl=(); [ -d android/build ] || tpl=(--install-android-build-template)
  mkdir -p "$OUT/Android"
  godot "${tpl[@]}" --export-debug Android "$OUT/Android/chinesepuzzle-debug.apk"
  cp export_presets.cfg /tmp/cp_presets.bak
  trap 'cp /tmp/cp_presets.bak "$ROOT/Godot/export_presets.cfg"' RETURN
  sed -i 's#^gradle_build/export_format=0#gradle_build/export_format=1#' export_presets.cfg
  godot --export-debug Android "$OUT/Android/chinesepuzzle-debug.aab"
  ls -la "$OUT/Android"/*.apk "$OUT/Android"/*.aab
}

macos() {
  mkdir -p "$OUT/macOS"
  godot --export-release macOS "$OUT/macOS/ChinesePuzzle.zip"
  ls -la "$OUT/macOS/ChinesePuzzle.zip"
}

# Linux can only generate the Xcode project; build/sign the .ipa in Xcode on a Mac.
ios() {
  rm -rf "$OUT/iOS" && mkdir -p "$OUT/iOS"
  cp export_presets.cfg /tmp/cp_presets.bak
  trap 'cp /tmp/cp_presets.bak "$ROOT/Godot/export_presets.cfg"' RETURN
  [ -n "${IOS_TEAM_ID:-}" ] && sed -i "s#^application/app_store_team_id=.*#application/app_store_team_id=\"$IOS_TEAM_ID\"#" export_presets.cfg
  godot --export-release iOS "$OUT/iOS/ChinesePuzzle.ipa"
  rm -f "$OUT/chinesepuzzle-ios-xcode.zip"
  (cd "$OUT/iOS" && python3 -m zipfile -c "$OUT/chinesepuzzle-ios-xcode.zip" *)
  ls -la "$OUT/chinesepuzzle-ios-xcode.zip"
}

godot --import
case "${1:-all}" in
  android) android ;; macos) macos ;; ios) ios ;;
  all) android; macos; ios ;;
  *) echo "usage: $0 android|macos|ios|all" >&2; exit 1 ;;
esac
