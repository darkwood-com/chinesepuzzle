###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GameLayer = cc.Layer.extend(
  isMouseDown: false
  helloImg: null
  helloLabel: null
  circle: null
  sprite: null
  ctor: ->
    @_super()
    cc.associateWithNative this, cc.Layer

  init: ->
    @_super()
    size = cc.Director.getInstance().getWinSize()
    @helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38)
    @helloLabel.setPosition cc.p(size.width / 2, size.height - 40)
    @addChild @helloLabel, 5
    true
)

cpz.GameSceneZOrder =
  BG: 0
  Game: 1
  Menu: 2

cpz.GameSceneCommon = cc.Scene.extend(
  _conf: null
  _game: null
  _menu: null

  init: ->
    return false unless @_super()

    #set langage
    lang = cc.CCLang.getInstance()
    lang.setLang cc.LANGUAGE_FRENCH
    lang.addLang 'lang'

    @_conf = new cpz.GameConfig()
    @_conf.init()
    @_conf.load()

    true
  
  game: ->
  menu: ->
  menuWithLayout: (ml) ->

  newGame: ->
  retryGame: ->
  setResolution: (resolution) ->
  setTheme: (theme) ->

  playSound: (soundName) ->
  playBackgroundMusic: (play) ->

  layout: (anim = true) ->

  onEnter: ->
    @_super()
    layer = new cpz.GameLayer()
    @addChild layer
    layer.init()

  getConf: -> @_conf
  getGame: -> @_game
  getMenu: -> @_menu
)

cpz.GameSceneCommon.create = ->
  layer = new cpz.GameScene()
  return layer if layer and layer.init()
  null