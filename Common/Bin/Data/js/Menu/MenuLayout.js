/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with @ source code.
*/

cpz.MenuLayoutType = {
  None: 0,
  NewGame: 1,
  RetryGame: 2,
  Hint: 3,
  Theme: 4
};

cpz.MenuTag = {
  Bg: 0,
  NewTitle: 1,
  NewYes: 2,
  NewNo: 3,
  RetryTitle: 4,
  RetryYes: 5,
  RetryNo: 6
};

cpz.MenuLayout = cc.Class.extend({
  _layoutRes: function(key) {
    var sRes;
    if (cpz.MenuLayout._res === null) {
      cpz.MenuLayout._res = {
        '480x320': {
          font: 'arial16.fnt',
          titlePosition: cc.p(20, 20),
          validPosition: cc.p(5, 5),
          margin: cc.size(50, 50),
          menuNewBoxSize: cc.size(300, 200),
          menuNewTitle: cc.p(150, 100),
          menuNewYes: cc.p(200, 50),
          menuNewNo: cc.p(100, 50),
          menuRetryBoxSize: cc.size(300, 200),
          menuRetryTitle: cc.p(150, 100),
          menuRetryYes: cc.p(200, 50),
          menuRetryNo: cc.p(100, 50),
          menuHintBoxSize: cc.size(400, 250),
          menuThemeBoxSize: cc.size(300, 300),
          menuNoneBoxSize: cc.size(200, 200)
        },
        '960x640': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(600, 600),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1024x768': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(600, 600),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1280x800': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(600, 600),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1280x1024': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(600, 600),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1366x768': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(600, 600),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1440x900': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(800, 800),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1680x1050': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(800, 800),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1920x1080': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(800, 800),
          menuNoneBoxSize: cc.size(400, 400)
        },
        '1920x1200': {
          font: 'arial32.fnt',
          titlePosition: cc.p(40, 40),
          validPosition: cc.p(10, 10),
          margin: cc.size(100, 100),
          menuNewBoxSize: cc.size(600, 400),
          menuNewTitle: cc.p(300, 200),
          menuNewYes: cc.p(400, 100),
          menuNewNo: cc.p(200, 100),
          menuRetryBoxSize: cc.size(600, 400),
          menuRetryTitle: cc.p(300, 200),
          menuRetryYes: cc.p(400, 100),
          menuRetryNo: cc.p(200, 100),
          menuHintBoxSize: cc.size(800, 500),
          menuThemeBoxSize: cc.size(800, 800),
          menuNoneBoxSize: cc.size(400, 400)
        }
      };
    }
    sRes = this._menu.getGameScene().getConf().getResolution();
    return cpz.MenuLayout._res[sRes][key];
  },
  _menu: null,
  _themes: null,
  _selectTheme: function(themeNode) {
    var theme, _i, _len, _ref, _results;
    _ref = this._themes;
    _results = [];
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      theme = _ref[_i];
      if (theme === themeNode) {
        this._menu.getGameScene().setTheme(theme);
        _results.push(this._menu.getGameScene().playSound('menu_select'));
      } else {
        _results.push(void 0);
      }
    }
    return _results;
  },
  _bg: null,
  _mBox: null,
  _miTheme: null,
  _layoutLastFontFile: null,
  _type: null,
  ctor: function(menu) {
    this._menu = menu;
    this._themes = null;
    this._bg = null;
    this._mBox = null;
    return this._miTheme = null;
  },
  initWithType: function(type) {
    this._type = type;
    return true;
  },
  layout: function(anim) {
    var center, conf, currentFontFile, item, itemNo, itemTitle, itemYes, items, key, lang, noNode, noSprite, theme, themeNode, themeNodeSelected, themeNodes, yesNode, yesSprite, _i, _len, _ref;
    if (anim == null) {
      anim = true;
    }
    lang = cc.Lang.getInstance();
    conf = this._menu.getGameScene().getConf();
    center = cc.pMult(cc.p(conf.getResolutionSize().width, conf.getResolutionSize().height), 0.5);
    if (!this._bg) {
      this._bg = cc.SpriteBatchNode.createWithTexture(cc.textureNull());
      this._menu.addChild(this._bg, 0, cpz.MenuTag.Bg);
    }
    conf.getNodeUiPath('menuMask', this._bg);
    this._bg.setPosition(cc.p(0, 0));
    this._bg.setAnchorPoint(cc.p(0, 0));
    yesNode = cc.SpriteBatchNode.createWithTexture(cc.textureNull());
    conf.getNodeUiPath('menuItemYes', yesNode);
    yesSprite = cc.copyFirstSpriteBatchNode(yesNode);
    noNode = cc.SpriteBatchNode.createWithTexture(cc.textureNull());
    conf.getNodeUiPath('menuItemNo', noNode);
    noSprite = cc.copyFirstSpriteBatchNode(noNode);
    currentFontFile = this._layoutRes('font');
    switch (this._type) {
      case cpz.MenuLayoutType.NewGame:
        if (!this._mBox) {
          this._mBox = new cpz.MenuBox();
          this._mBox.initWithConf(conf);
          this._mBox.setOkTarget(this._menu, cpz.Menu.okMenu);
          this._menu.pushNav(this._mBox);
        }
        this._mBox.setTitle(lang.get('menu.newgame.title'), currentFontFile);
        this._mBox.setTitlePosition(this._layoutRes('titlePosition'));
        this._mBox.setValidPosition(this._layoutRes('validPosition'));
        this._mBox.setContentSize(this._layoutRes('menuNewBoxSize'));
        this._mBox.setPosition(center);
        this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
        itemTitle = this._mBox.getChildByTag(cpz.MenuTag.NewTitle);
        if (!itemTitle || currentFontFile !== this._layoutLastFontFile) {
          this._mBox.removeChildByTag(cpz.MenuTag.NewTitle, true);
          itemTitle = cc.LabelBMFont.create(lang.get('menu.newgame.content'), cpz.GameConfigCommon.getFontPath(currentFontFile));
          itemTitle.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addChild(itemTitle, 0, cpz.MenuTag.NewTitle);
        }
        itemTitle.setPosition(this._layoutRes('menuNewTitle'));
        itemYes = this._mBox.getChildByTag(cpz.MenuTag.NewYes);
        if (!itemYes) {
          itemYes = cc.MenuItemSprite.create(yesSprite, null, null, cpz.GameSceneCommon.newGame, this._menu.getGameScene());
          itemYes.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addItem(itemYes, 1, cpz.MenuTag.NewYes);
        }
        itemYes.setNormalImage(yesSprite);
        itemYes.setContentSize(yesSprite.getContentSize());
        itemYes.setPosition(this._layoutRes('menuNewYes'));
        itemNo = this._mBox.getChildByTag(cpz.MenuTag.NewNo);
        if (!itemNo) {
          itemNo = cc.MenuItemSprite.create(noSprite, null, null, cpz.Menu.okMenu, this._menu);
          itemNo.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addItem(itemNo, 2, cpz.MenuTag.NewNo);
        }
        itemNo.setNormalImage(noSprite);
        itemNo.setContentSize(noSprite.getContentSize());
        itemNo.setPosition(this._layoutRes('menuNewNo'));
        this._mBox.layout(anim);
        break;
      case cpz.MenuLayoutType.RetryGame:
        if (!this._mBox) {
          this._mBox = new cpz.MenuBox();
          this._mBox.initWithConf(conf);
          this._mBox.setOkTarget(this._menu, cpz.Menu.okMenu);
          this._menu.pushNav(this._mBox);
        }
        this._mBox.setTitle(lang.get('menu.retrygame.title'), currentFontFile);
        this._mBox.setTitlePosition(this._layoutRes('titlePosition'));
        this._mBox.setValidPosition(this._layoutRes('validPosition'));
        this._mBox.setContentSize(this._layoutRes('menuRetryBoxSize'));
        this._mBox.setPosition(center);
        this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
        itemTitle = this._mBox.getChildByTag(cpz.MenuTag.RetryTitle);
        if (!itemTitle || currentFontFile !== this._layoutLastFontFile) {
          this._mBox.removeChildByTag(cpz.MenuTag.RetryTitle, true);
          itemTitle = cc.LabelBMFont.create(lang.get('menu.retrygame.content'), cpz.GameConfigCommon.getFontPath(currentFontFile));
          itemTitle.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addChild(itemTitle, 0, cpz.MenuTag.RetryTitle);
        }
        itemTitle.setPosition(this._layoutRes('menuRetryTitle'));
        itemYes = this._mBox.getChildByTag(cpz.MenuTag.RetryYes);
        if (!itemYes) {
          itemYes = cc.MenuItemSprite.create(yesSprite, null, null, cpz.GameSceneCommon.retryGame, this._menu.getGameScene());
          itemYes.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addItem(itemYes, 1, cpz.MenuTag.RetryYes);
        }
        itemYes.setNormalImage(yesSprite);
        itemYes.setContentSize(yesSprite.getContentSize());
        itemYes.setPosition(this._layoutRes('menuRetryYes'));
        itemNo = this._mBox.getChildByTag(cpz.MenuTag.RetryNo);
        if (!itemNo) {
          itemNo = cc.MenuItemSprite.create(noSprite, null, null, cpz.Menu.okMenu, this._menu);
          itemNo.initWithTarget(this._menu, cpz.Menu.okMenu);
          itemNo.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.addItem(itemNo, 2, cpz.MenuTag.RetryNo);
        }
        itemNo.setNormalImage(noSprite);
        itemNo.setContentSize(noSprite.getContentSize());
        itemNo.setPosition(this._layoutRes('menuRetryNo'));
        this._mBox.layout(anim);
        break;
      case cpz.MenuLayoutType.Hint:
        if (!!this._mBox) {
          this._mBox = new cpz.MenuLabelContainer();
          this._mBox.initWithConfAndContentSizeAndFntFile(conf, this._layoutRes('menuHintBoxSize'), cpz.GameConfigCommon.getFontPath(this._layoutRes('font')));
          this._mBox.setPosition(center);
          this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.setOkTarget(this._menu, cpz.Menu.okMenu);
          this._mBox.setString(lang.get('menu.hintgame.content'));
          this._menu.pushNav(this._mBox);
        }
        this._mBox.setMargin(this._layoutRes('margin'));
        this._mBox.setTitle(lang.get('menu.hintgame.title'), currentFontFile);
        this._mBox.setTitlePosition(this._layoutRes('titlePosition'));
        this._mBox.setValidPosition(this._layoutRes('validPosition'));
        this._mBox.setContentSize(this._layoutRes('menuHintBoxSize'));
        this._mBox.setPosition(center);
        this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
        this._mBox.layout(anim);
        break;
      case cpz.MenuLayoutType.Theme:
        if (!this._themes) {
          themeNodes = {
            classic: 'menuItemThemeClassic',
            chinese: 'menuItemThemeChinese',
            polkadots: 'menuItemThemePolkadots',
            seamless: 'menuItemThemeSeamless',
            shullshearts: 'menuItemThemeSkullshearts',
            splash: 'menuItemThemeSplash',
            spring: 'menuItemThemeSpring',
            stripes: 'menuItemThemeStripes',
            vivid: 'menuItemThemeVivid'
          };
          this._themes = {};
          for (key in themeNodes) {
            theme = themeNodes[key];
            themeNode = cc.SpriteBatchNode.createWithTexture(cc.textureNull());
            themeNodeSelected = cc.SpriteBatchNode.createWithTexture(cc.textureNull());
            conf.getNodeUiPath(theme, themeNode);
            conf.getNodeUiPath(theme + 'Select', themeNodeSelected);
            this._themes[key] = cc.MenuItemSprite.create(themeNode, null, null, cpz.MenuLayout._selectTheme, this);
          }
        }
        if (!this._mBox) {
          this._mBox = new cpz.MenuGridContainer();
          this._mBox.initWithConf(conf);
          this._mBox.setMargin(cc.size(50, 50));
          this._mBox.setGridSize(ccg(2, 2));
          this._mBox.setPage(0);
          this._mBox.setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
          this._mBox.setOkTarget(this._menu, cpz.Menu.okMenu);
          items = [];
          _ref = this._themes;
          for (_i = 0, _len = _ref.length; _i < _len; _i++) {
            theme = _ref[_i];
            items.push(theme);
          }
          this._mBox.setItems(items);
          this._menu.pushNav(this._mBox);
        }
        this._mBox.setTitle(lang.get('menu.themegame.title'), currentFontFile);
        this._mBox.setTitlePosition(this._layoutRes('titlePosition'));
        this._mBox.setValidPosition(this._layoutRes('validPosition'));
        this._mBox.setContentSize(this._layoutRes('menuThemeBoxSize'));
        this._mBox.setPosition(center);
        this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
        this._mBox.layout(anim);
        break;
      case cpz.MenuLayoutType.None:
        if (!this._mBox) {
          this._mBox = new cpz.MenuBox();
          this._mBox.initWithConfAndContentSize(conf, this._layoutRes('menuNoneBoxSize'));
          this._mBox.setPosition(center);
          this._mBox.setAnchorPoint(cc.p(0.5, 0.5));
          this._mBox.setOkTarget(this._menu, cpz.Menu.okMenu);
          items = [];
          item = new cc.MenuItemFont();
          item.initFromString('Exit menu', this._menu, cpz.Menu.okMenu);
          item.setAnchorPoint(cc.p(0.5, 0.5));
          item.setPosition(cc.p(0, 0));
          items.addObject(item);
          this._mBox.setItems(items);
          this._mBox.layout(anim);
          this._menu.pushNav(this._mBox);
        }
        this._mBox.setTitle('None', currentFontFile);
        this._mBox.setTitlePosition(this._layoutRes('titlePosition'));
        this._mBox.setValidPosition(this._layoutRes('validPosition'));
        this._mBox.layout(anim);
        break;
    }
    return this._layoutLastFontFile = currentFontFile;
  },
  getType: function() {
    return this._type;
  },
  setType: function(_type) {
    this._type = _type;
    return this;
  }
});

cpz.MenuLayout._res = null;
