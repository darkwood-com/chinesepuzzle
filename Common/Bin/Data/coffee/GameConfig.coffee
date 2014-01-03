###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GameConfigCommon = cc.Class.extend(
  _resolution: ''
  _theme: ''
  _isSoundOn: false
  _moves: []
  _initBoard: null

  ctor: ->
    @_initBoard = new cc.Dictionary()

  init: ->
  defaultResolution: ->
  getRootPath: (file) ->
  getResolutionPath: (file) ->
  getUiPath: (file) ->
  getThemePath: (file) ->
  getFontPath: (file) ->
  getNodeUiPath: (file, sprite) ->
  getNodeThemePath: (file, sprite) ->

  getResolutionSize: ->
  getResolution: -> @_resolution
  setResolution: (@_resolution) -> @
  getTheme: -> @_theme
  setTheme: (@_theme) -> @
  getIsSoundOn: -> @_isSoundOn
  setIsSoundOn: (@_isSoundOn) -> @
  getMoves: -> @_moves
  getInitBoard: -> @_initBoard

  encode: ->
  decode: (data) ->

  save: ->
  load: ->
)

cpz.GameConfigCommon.XML_FILE_NAME = 'chinesePuzzleConf.plist'