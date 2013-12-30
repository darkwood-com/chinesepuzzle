###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

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

    @playBackgroundMusic @_conf.getIsSoundOn()

    @_game = null
    @_menu = null

    @game()

    true

  game: ->
    if @_menu
      @removeChild @_menu, true
      @_menu = null

    if @_game is null
      @_game = cpz.Game.create @

    if @_game.getParent() is null
      @addChild @_game, cpz.GameSceneZOrder.Game

    @_game

  menu: ->
  menuWithLayout: (ml) ->

  newGame: ->
  retryGame: ->
  setResolution: (resolution) ->
  setTheme: (theme) ->

  playSound: (soundName) ->
  playBackgroundMusic: (play) ->

  layout: (anim = true) ->

  getConf: -> @_conf
  getGame: -> @_game
  getMenu: -> @_menu
)

cpz.GameSceneCommon.create = ->
  layer = new cpz.GameScene()
  return layer if layer and layer.init()
  null