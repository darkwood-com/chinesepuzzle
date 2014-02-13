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
  _background : null
  _game: null
  _menu: null

  ctor: ->
    @_super()

    @_bgMusicTheme = cpz.GameSceneBGMusicTheme.ThemeNone

  onExit: ->
    cc.SafeRelease @_game
    cc.SafeRelease @_menu
    @_super()

  init: ->
    return false unless @_super()

    #set langage
    lang = cc.Lang.getInstance()
    lang.setLang cc.Application.getInstance().getCurrentLanguage()
    lang.addLang 'lang'

    @ignoreAnchorPointForPosition(false)

    @_conf = new cpz.GameConfig()
    @_conf.init()
    @_conf.load()

    @reshape ->
      @playBackgroundMusic @_conf.getIsSoundOn()

      @_game = null
      @_menu = null

      @_background = cpz.Background.create(@)
      @addChild(@_background, cpz.GameSceneZOrder.BG)
      
      @game()

      @reshape()
      @layout()

    , @

    true

  game: ->
    if @_menu
      @removeChild @_menu, true
      cc.SafeRelease(@_menu)
      @_menu = null

    if @_game is null
      @_game = cpz.Game.create @
      @_game.retain()

    if @_game.getParent() is null
      @addChild @_game, cpz.GameSceneZOrder.Game

    @_game

  menu: -> @menuWithLayout(cpz.MenuLayoutType.None)

  menuWithLayout: (layout) ->
    if @_menu is null
      @_menu = cpz.Menu.create @, layout
      @_menu.retain()

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

  setResolution: (resolution, selector = null, target = null) ->
    @_conf.preload ->
      @_conf.setResolution resolution
      @setContentSize @_conf.getResolutionSize()

      @layout(false)
      @_conf.save()

      selector.call(target) if selector
    , @, resolution

    @

  setTheme: (theme, selector = null, target = null) ->
    @_conf.preload ->
      @_conf.setTheme theme
      @layout()
      @_conf.save()

      selector.call(target) if selector
    , @, null, theme

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

  reshape: (selector = null, target = null) ->
    winsize = cc.Director.getInstance().getWinSize()
    wincenter = cc.pMult(cc.p(winsize.width, winsize.height), 0.5)

    @setPosition(wincenter)
    @_background.setContentSize(winsize) if @_background

    #change resolution
    autoRes = null
    for res in cpz.GameConfigCommon.getResolutions()
      newRes = cpz.GameConfigCommon.parseResolution res
      oldRes = cpz.GameConfigCommon.parseResolution autoRes

      if autoRes is null or
        ((oldRes.width < newRes.width and oldRes.height < newRes.height) and
        (newRes.width < winsize.width and newRes.height < winsize.height))
          autoRes = res

    @setResolution(autoRes, selector, target) if autoRes

  layout: (anim = true) ->
    if @_game then @_game.layout(anim)
    if @_menu then @_menu.layout(anim)

    confsize = @_conf.getResolutionSize()
    confcenter = cc.pMult(cc.p(confsize.width, confsize.height), 0.5)

    @setContentSize(confsize)
    @_background.setPosition(confcenter) if @_background
    
    @

  getConf: -> @_conf
  getGame: -> @_game
  getMenu: -> @_menu
)

cpz.GameSceneCommon.create = ->
  obj = new cpz.GameScene()
  return obj if obj and obj.init()
  null