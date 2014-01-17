###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with @ source code.
###

cpz.MenuLayoutType =
  None: 0
  NewGame: 1
  RetryGame: 2
  Hint: 3
  Theme: 4
  
cpz.MenuTag =
  Bg: 0
  NewTitle: 1
  NewYes: 2
  NewNo: 3
  RetryTitle: 4
  RetryYes: 5
  RetryNo: 6

cpz.MenuLayout = cc.Class.extend(
  _layoutRes: (key) ->
    unless cpz.MenuLayout.datas
      cpz.MenuLayout.datas =
        '480x320':
          font: 'arial16.fnt'
          titlePosition: cc.p(20, 20)
          validPosition: cc.p(5, 5)
          margin: cc.size(50, 50)
          menuNewBoxSize: cc.size(300,200)
          menuNewTitle: cc.p(150,100)
          menuNewYes: cc.p(200,50)
          menuNewNo: cc.p(100,50)
          menuRetryBoxSize: cc.size(300,200)
          menuRetryTitle: cc.p(150,100)
          menuRetryYes: cc.p(200,50)
          menuRetryNo: cc.p(100,50)
          menuHintBoxSize: cc.size(400,250)
          menuThemeBoxSize: cc.size(300,300)
          menuNoneBoxSize: cc.size(200,200)
        '960x640':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(600,600)
          menuNoneBoxSize: cc.size(400,400)
        '1024x768':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(600,600)
          menuNoneBoxSize: cc.size(400,400)
        '1280x800':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(600,600)
          menuNoneBoxSize: cc.size(400,400)
        '1280x1024':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(600,600)
          menuNoneBoxSize: cc.size(400,400)
        '1366x768':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(600,600)
          menuNoneBoxSize: cc.size(400,400)
        '1440x900':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(800,800)
          menuNoneBoxSize: cc.size(400,400)
        '1680x1050':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(800,800)
          menuNoneBoxSize: cc.size(400,400)
        '1920x1080':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(800,800)
          menuNoneBoxSize: cc.size(400,400)
        '1920x1200':
          font: 'arial32.fnt'
          titlePosition: cc.p(40, 40)
          validPosition: cc.p(10, 10)
          margin: cc.size(100, 100)
          menuNewBoxSize: cc.size(600,400)
          menuNewTitle: cc.p(300,200)
          menuNewYes: cc.p(400,100)
          menuNewNo: cc.p(200,100)
          menuRetryBoxSize: cc.size(600,400)
          menuRetryTitle: cc.p(300,200)
          menuRetryYes: cc.p(400,100)
          menuRetryNo: cc.p(200,100)
          menuHintBoxSize: cc.size(800,500)
          menuThemeBoxSize: cc.size(800,800)
          menuNoneBoxSize: cc.size(400,400)
    
    sRes = @_menu.getGameScene().getConf().getResolution()
    return cpz.MenuLayout.datas[sRes][key]

  _menu: null
  _themes: null
  _selectTheme: (themeNode) ->
    for theme in @_themes
      if(theme is themeNode)
        @_menu.getGameScene().setTheme(theme)
        @_menu.getGameScene().playSound('menu_select')

  _bg: null

  _mBox: null
  _miTheme: null

  _layoutLastFontFile: null

  _type: null

  ctor: (menu) ->
    @_menu = menu
    @_themes = null
    @_bg = null
    @_mBox = null
    @_miTheme = null

  initWithType: (type) ->
    @_type = type
    
    true

  layout: (anim = true) ->
    lang = cc.Lang.getInstance()
    
    conf = @_menu.getGameScene().getConf()
    center = cc.pMult(cc.p(conf.getResolutionSize().width, conf.getResolutionSize().height), 0.5)
  
    unless @_bg
      @_bg = cc.SpriteBatchNode.createWithTexture cc.textureNull()
      @_menu.addChild(@_bg, 0, cpz.MenuTag.Bg)

    conf.getNodeUiPath('menuMask', @_bg)
    @_bg.setPosition(cc.p(0, 0))
    @_bg.setAnchorPoint(cc.p(0, 0))
    
    yesNode = cc.SpriteBatchNode.createWithTexture cc.textureNull()
    conf.getNodeUiPath('menuItemYes', yesNode)
    yesSprite = cc.copyFirstSpriteBatchNode(yesNode)
    
    noNode = cc.SpriteBatchNode.createWithTexture cc.textureNull()
    conf.getNodeUiPath('menuItemNo', noNode)
    noSprite = cc.copyFirstSpriteBatchNode(noNode)
    
    currentFontFile = @_layoutRes('font')
    
    switch (@_type)
      when cpz.MenuLayoutType.NewGame
        unless @_mBox
          @_mBox = new cpz.MenuBox()
          @_mBox.initWithConf(conf)
          @_mBox.setOkTarget(@_menu, cpz.Menu.okMenu)
          
          @_menu.pushNav(@_mBox)
        
        @_mBox.setTitle(lang.get('menu.newgame.title'), currentFontFile)
        @_mBox.setTitlePosition(@_layoutRes('titlePosition'))
        @_mBox.setValidPosition(@_layoutRes('validPosition'))
        @_mBox.setContentSize(@_layoutRes('menuNewBoxSize'))
        @_mBox.setPosition(center)
        @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
        
        itemTitle = @_mBox.getChildByTag(cpz.MenuTag.NewTitle)
        if not itemTitle or currentFontFile isnt @_layoutLastFontFile
          @_mBox.removeChildByTag(cpz.MenuTag.NewTitle, true)
          itemTitle = cc.LabelBMFont.create(lang.get('menu.newgame.content'), cpz.GameConfigCommon.getFontPath(currentFontFile))
          itemTitle.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addChild(itemTitle, 0, cpz.MenuTag.NewTitle)
        itemTitle.setPosition(@_layoutRes('menuNewTitle'))
        
        itemYes = @_mBox.getChildByTag(cpz.MenuTag.NewYes)
        unless itemYes
          itemYes = new cc.MenuItemSprite()
          itemYes.initWithTarget(@_menu.getGameScene(), cpz.GameSceneCommon.newGame)
          itemYes.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addItem(itemYes, 1, cpz.MenuTag.NewYes)
        itemYes.setNormalImage(yesSprite)
        itemYes.setContentSize(yesSprite.getContentSize())
        itemYes.setPosition(@_layoutRes('menuNewYes'))
        
        itemNo = @_mBox.getChildByTag(cpz.MenuTag.NewNo)
        unless itemNo
          itemNo = new cc.MenuItemSprite()
          itemNo.initWithTarget(@_menu, cpz.Menu.okMenu)
          itemNo.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addItem(itemNo, 2, cpz.MenuTag.NewNo)
        itemNo.setNormalImage(noSprite)
        itemNo.setContentSize(noSprite.getContentSize())
        itemNo.setPosition(@_layoutRes('menuNewNo'))
        
        @_mBox.layout(anim)
        
      when cpz.MenuLayoutType.RetryGame
        unless @_mBox
          @_mBox = new cpz.MenuBox()
          @_mBox.initWithConf(conf)
          @_mBox.setOkTarget(@_menu, cpz.Menu.okMenu)
          
          @_menu.pushNav(@_mBox)
        
        @_mBox.setTitle(lang.get('menu.retrygame.title'), currentFontFile)
        @_mBox.setTitlePosition(@_layoutRes('titlePosition'))
        @_mBox.setValidPosition(@_layoutRes('validPosition'))
        @_mBox.setContentSize(@_layoutRes('menuRetryBoxSize'))
        @_mBox.setPosition(center)
        @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
        
        itemTitle = @_mBox.getChildByTag(cpz.MenuTag.RetryTitle)
        if(!itemTitle or currentFontFile isnt @_layoutLastFontFile)
          @_mBox.removeChildByTag(cpz.MenuTag.RetryTitle, true)
          itemTitle = cc.LabelBMFont.create(lang.get('menu.retrygame.content'), cpz.GameConfigCommon.getFontPath(currentFontFile))
          itemTitle.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addChild(itemTitle, 0, cpz.MenuTag.RetryTitle)
        itemTitle.setPosition(@_layoutRes('menuRetryTitle'))
        
        itemYes = @_mBox.getChildByTag(cpz.MenuTag.RetryYes)
        unless itemYes
          itemYes = new cc.MenuItemSprite()
          itemYes.initWithTarget(@_menu.getGameScene(), cpz.GameSceneCommon.retryGame)
          itemYes.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addItem(itemYes, 1, cpz.MenuTag.RetryYes)
        itemYes.setNormalImage(yesSprite)
        itemYes.setContentSize(yesSprite.getContentSize())
        itemYes.setPosition(@_layoutRes('menuRetryYes'))
        
        itemNo = @_mBox.getChildByTag(cpz.MenuTag.RetryNo)
        unless itemNo
          itemNo = new cc.MenuItemSprite()
          itemNo.initWithTarget(@_menu, cpz.Menu.okMenu)
          itemNo.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.addItem(itemNo, 2, cpz.MenuTag.RetryNo)
        itemNo.setNormalImage(noSprite)
        itemNo.setContentSize(noSprite.getContentSize())
        itemNo.setPosition(@_layoutRes('menuRetryNo'))
        
        @_mBox.layout(anim)
      
      when cpz.MenuLayoutType.Hint
        unless !@_mBox
          @_mBox = new MenuLabelContainer()
          @_mBox.initWithConfAndContentSizeAndFntFile(conf, @_layoutRes('menuHintBoxSize'), cpz.GameConfigCommon.getFontPath((@_layoutRes('font'))))
          @_mBox.setPosition(center)
          @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.setOkTarget(@_menu, cpz.Menu.okMenu)
          @_mBox.setString(lang.get('menu.hintgame.content'))
          
          @_menu.pushNav(@_mBox)
        
        @_mBox.setMargin(@_layoutRes('margin'))
        @_mBox.setTitle(lang.get('menu.hintgame.title'), currentFontFile)
        @_mBox.setTitlePosition(@_layoutRes('titlePosition'))
        @_mBox.setValidPosition(@_layoutRes('validPosition'))
        @_mBox.setContentSize(@_layoutRes('menuHintBoxSize'))
        @_mBox.setPosition(center)
        @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
        @_mBox.layout(anim)
        
      when cpz.MenuLayoutType.Theme
        unless @_themes
          themeNodes =
            classic     : 'menuItemThemeClassic'
            chinese     : 'menuItemThemeChinese'
          # circle      : 'menuItemThemeCircle'
            polkadots   : 'menuItemThemePolkadots'
            seamless    : 'menuItemThemeSeamless'
            shullshearts: 'menuItemThemeSkullshearts'
            splash      : 'menuItemThemeSplash'
            spring      : 'menuItemThemeSpring'
            stripes     : 'menuItemThemeStripes'
            vivid       : 'menuItemThemeVivid'

          @_themes = {}
          for key, theme of themeNodes
            themeNode = cc.SpriteBatchNode.createWithTexture cc.textureNull()
            themeNodeSelected = cc.SpriteBatchNode.createWithTexture cc.textureNull()
            conf.getNodeUiPath(theme, themeNode)
            conf.getNodeUiPath(theme + 'Select', themeNodeSelected)
            
            @_themes[key] = cc.MenuItemSprite.create(themeNode, null, @, cpz.MenuLayout._selectTheme)
        
        unless @_mBox
          @_mBox = new cpz.MenuGridContainer()
          @_mBox.initWithConf(conf)
          @_mBox.setMargin(cc.size(50, 50))
          @_mBox.setGridSize(ccg(2, 2))
          @_mBox.setPage(0)
          @_mBox.setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8)
          @_mBox.setOkTarget(@_menu, cpz.Menu.okMenu)
          
          items = []
          for theme in @_themes
            items.push theme
          
          @_mBox.setItems(items)
          
          @_menu.pushNav(@_mBox)
        
        @_mBox.setTitle(lang.get('menu.themegame.title'), currentFontFile)
        @_mBox.setTitlePosition(@_layoutRes('titlePosition'))
        @_mBox.setValidPosition(@_layoutRes('validPosition'))
        @_mBox.setContentSize(@_layoutRes('menuThemeBoxSize'))
        @_mBox.setPosition(center)
        @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
        @_mBox.layout(anim)
      
      when cpz.MenuLayoutType.None
        unless @_mBox
          @_mBox = new cpz.MenuBox()
          @_mBox.initWithConfAndContentSize(conf, @_layoutRes('menuNoneBoxSize'))
          @_mBox.setPosition(center)
          @_mBox.setAnchorPoint(cc.p(0.5, 0.5))
          @_mBox.setOkTarget(@_menu, cpz.Menu.okMenu)

          items = []
          
          item = new cc.MenuItemFont()
          item.initFromString('Exit menu', @_menu, cpz.Menu.okMenu)
          item.setAnchorPoint(cc.p(0.5, 0.5))
          item.setPosition(cc.p(0, 0))
          items.addObject(item)

          @_mBox.setItems(items)
          @_mBox.layout(anim)
          
          @_menu.pushNav(@_mBox)
        
        @_mBox.setTitle('None', currentFontFile)
        @_mBox.setTitlePosition(@_layoutRes('titlePosition'))
        @_mBox.setValidPosition(@_layoutRes('validPosition'))
        @_mBox.layout(anim)

      else
    
    @_layoutLastFontFile = currentFontFile

  getType: -> @_type
  setType: (@_type) -> @
)

cpz.MenuLayout.datas = null
