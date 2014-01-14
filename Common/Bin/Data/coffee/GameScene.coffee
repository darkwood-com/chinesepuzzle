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

cpz.GameSceneBGMusicTheme =
  ThemeNone: 0
  Theme1: 1
  Theme2: 2
  Theme3: 3

cpz.GameSceneCommon = cc.Scene.extend(
  _bgMusicTheme: null

  _conf: null
  _game: null
  _menu: null

  ctor: ->
    @_super()

    @_bgMusicTheme = cpz.GameSceneBGMusicTheme.ThemeNone

  init: ->
    return false unless @_super()

    #set langage
    lang = cc.CCLang.getInstance()
    lang.setLang cc.Application.getCurrentLanguage()
    lang.addLang 'lang'

    @_conf = new cpz.GameConfig()
    @_conf.init()
    @_conf.load()
    @_conf.preload ->
      @playBackgroundMusic @_conf.getIsSoundOn()

      @_game = null
      @_menu = null

      @game()
    , @

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

  menu: -> @menuWithLayout(cpz.MenuLayoutType.None)

  menuWithLayout: (layout) ->
    if @_menu is null
      @_menu = cpz.Menu.create @, layout

    if @_menu.getParent() is null
      @addChild @_menu, cpz.GameSceneZOrder.Menu

    @_menu

  newGame: ->
    game = @game()
    game.newGame()

    @playSound 'shuffle'
    @

  retryGame: ->
    game = @game()
    game.retryGame()

    @playSound 'shuffle'
    @

  setResolution: (resolution) ->
    @_conf.setResolution resolution
    @setContentSize @_conf.getResolutionSize()

    @layout(false)
    @_conf.save()
    @

  setTheme: (theme) ->
    @_conf.setTheme theme

    @layout()
    @_conf.save()
    @

  playSound: (soundName) ->
    audio = cc.AudioEngine.getInstance()

    if @_conf.getIsSoundOn()
      audio.playEffect(cpz.CommonPath + 'sound/' + soundName + '.mp3')
    @

  playBackgroundMusic: (play) ->
    audio = cc.AudioEngine.getInstance()

    if play and @_conf.getIsSoundOn()
      audio.setMusicVolume 0.5
      switch @_bgMusicTheme
        when cpz.GameSceneBGMusicTheme.Theme1
          audio.playMusic cpz.CommonPath + 'sound/bgm2.mp3', true
          @_bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme2
        when cpz.GameSceneBGMusicTheme.Theme2
          audio.playMusic cpz.CommonPath + 'sound/bgm3.mp3', true
          @_bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme3
        else
          audio.playMusic cpz.CommonPath + 'sound/bgm1.mp3', true
          @_bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme1


    else if @_bgMusicTheme isnt cpz.GameSceneBGMusicTheme.ThemeNone
      audio.stopMusic()

  layout: (anim = true) ->
    if @_game then @_game.layout(anim)
    if @_menu then @_menu.layout(anim)
    @

  getConf: -> @_conf
  getGame: -> @_game
  getMenu: -> @_menu
)

cpz.GameSceneCommon.create = ->
  obj = new cpz.GameScene()
  return obj if obj and obj.init()
  null