#!/usr/bin/env python3
"""Regenerate Godot/assets atlases from the original 960x640 Photoshop sources.

Requires psd-tools (pip install psd-tools). Run from the repo root:
    python3 Godot/tools/extract_assets.py
"""
import glob, os
from psd_tools import PSDImage

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, "Common/Bin/Design/960x640")
DST = os.path.join(ROOT, "Godot/assets")
THEMES = ["chinese", "classic", "polkadots", "seamless", "shullshearts", "splash", "spring", "stripes", "vivid"]

PSDImage.open(os.path.join(SRC, "ui.psd")).composite().save(os.path.join(DST, "ui.png"))
for t in THEMES:
    PSDImage.open(os.path.join(SRC, "themes", t + ".psd")).composite().save(os.path.join(DST, "themes", t + ".png"))
print("done")
