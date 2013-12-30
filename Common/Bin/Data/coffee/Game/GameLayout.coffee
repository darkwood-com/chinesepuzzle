###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GameZOrder =
  BG: 0
  UI: 1
  Board: 2
  Card: 3
  MoveCard: 4
  HintCard: 5

cpz.GameLayout = cc.Class.extend(
  _layoutRes: (key) ->
  _actionBtn: (btn) ->

  _game: null
  _activesBtn: []

  _bg: null

  #button layout
  _newBtn: null
  _retryBtn: null
  _hintBtn: null
  _undoBtn: null
  _soundBtn: null
  _themeBtn: null

  #card grid layout stuff
  _gridCardSize: null
  _gridSpaceSize: null
  _gridPosition: null

  ctor: (game) ->
    @_super()

  layout: (anim = true) ->

  tapDownAt: (location) ->
  tapMoveAt: (location) ->
  tapUpAt: (location) ->

  getPositionInBoardPoint: (coord) ->
  getPositionInGridCoord: (point) ->
)
