#!/usr/bin/env bash
# Build the itch.io HTML5 package: Godot 4.7.2 "Web" preset (no GamePix SDK, no threads), zip with index.html at root.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
GODOT="${GODOT:-$HOME/.local/bin/godot}"
OUT="$ROOT/Exports/Web"
rm -rf "$OUT" && mkdir -p "$OUT"
cd "$ROOT/Godot"
"$GODOT" --headless --import
"$GODOT" --headless --export-release Web "$OUT/index.html"
rm -f "$ROOT/Exports/chinesepuzzle-itch-html5.zip"
(cd "$OUT" && python3 -m zipfile -c "$ROOT/Exports/chinesepuzzle-itch-html5.zip" *)
echo "$ROOT/Exports/chinesepuzzle-itch-html5.zip"
