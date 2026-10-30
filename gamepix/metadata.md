# Chinese Puzzle — store listings (GamePix + itch.io)

- Studio: Darkwood
- Engine: Godot 4.7.2 (GL Compatibility, single-threaded Web export), project in `Godot/`
- GamePix: GamePix Godot SDK 1.2r (`Godot/addons/gpx-godot-plugin`, autoload `GPX`) with the v3 manual lifecycle
- Builds: `gamepix/build.sh` → `Exports/chinesepuzzle-gamepix.zip`; `itch/build.sh` → `Exports/chinesepuzzle-itch-html5.zip` (index.html at the root of both)
- Languages: English, French, German (auto-detected; GamePix language on GamePix)

## GamePix

- Orientation: Landscape
- Main tag: Card (alternatives: Solitaire, Puzzle)

### Description
Chinese Puzzle is a two-deck solitaire played on a grid of eight rows. Slide cards into the empty spaces to rebuild every row in a single suit, from Ace to King. Aces only go into the first column; any other gap can only take the next card of the same suit as the card on its left, so plan ahead and watch out for gaps stuck behind Kings. Undo moves, retry the same deal or shuffle a new one, and pick one of nine card themes.

### Controls
Mouse or touch: drag a card onto an empty space (the space turns green when the move is valid, red when it is not), or tap a card and then tap an empty space. Buttons on the right: New game, Retry, Undo, Rules, Sound on/off, Themes.

### Assets
- Icon 256x256: `gamepix/icon-256.png`
- Cover 1360x850: `gamepix/cover-1360x850.png` (also packed as `background.jpg` loading background)
- Smoke screenshots (headless Chrome): `gamepix/smoke-game.png`, `gamepix/smoke-themes.png`

## itch.io

- Title: Chinese Puzzle
- Short description / tagline: A two-deck solitaire puzzle: slide 104 cards through the gaps until every row runs from Ace to King in one suit.
- Genre: Card Game
- Tags: solitaire, card-game, patience, puzzle, cards, singleplayer, casual, relaxing, 2d, html5
- Kind of project: HTML — upload `chinesepuzzle-itch-html5.zip`, tick "This file will be played in the browser"
- Embed: viewport 960 x 640, fullscreen button: yes, mobile friendly: yes (landscape orientation), automatically start on page load: yes, no SharedArrayBuffer needed
- Cover 630x500: `itch/cover-630x500.png`
- Screenshots: `itch/screenshot-1-game.png`, `itch/screenshot-2-drag.png`, `itch/screenshot-3-themes.png`

### Description
Chinese Puzzle is a patience game for one player, played with two full decks of cards (104 cards) laid out in eight rows of thirteen cards, plus eight empty spaces.

Your goal is to sort the table so that every row holds a single suit in order, from Ace to King.

How to play:
- Move a card into an empty space. The card that was there leaves an empty space behind it.
- Aces can only be moved into the first column.
- Any other empty space can only be filled with the next card of the same suit as the card on its left (for example the 5 of hearts goes right after a 4 of hearts). Since there are two decks, two cards always fit each space.
- A space right after a King can never be filled, so think before you play.
- Cards that are already in place at the start of a row (Ace, 2, 3... of the same suit) are locked.

Features:
- Drag and drop with a live hint on the target space, or tap a card and then tap a space
- Unlimited undo, retry the same deal, or shuffle a new game
- Nine card themes and an alternative card face layout
- Your game is saved automatically
- English, French and German

### Controls
Mouse or touch: drag a card onto an empty space (green = valid move, red = invalid), or tap a card then tap an empty space. Right-hand buttons: New game, Retry, Undo, Rules, Sound on/off, Themes.
