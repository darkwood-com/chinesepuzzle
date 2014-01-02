/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GameSceneZOrder = {
  BG: 0,
  Game: 1,
  Menu: 2
};

cpz.GameSceneBGMusicTheme = {
  ThemeNone: 0,
  Theme1: 1,
  Theme2: 2,
  Theme3: 3
};

cpz.GameSceneCommon = cc.Scene.extend({
  _bgMusicTheme: null,
  _conf: null,
  _game: null,
  _menu: null,
  ctor: function() {
    this._super();
    return this._bgMusicTheme = cpz.GameSceneBGMusicTheme.ThemeNone;
  },
  init: function() {
    var lang;
    if (!this._super()) {
      return false;
    }
    lang = cc.CCLang.getInstance();
    lang.setLang(cc.LANGUAGE_FRENCH);
    lang.addLang('lang');
    this._conf = new cpz.GameConfig();
    this._conf.init();
    this._conf.load();
    this.playBackgroundMusic(this._conf.getIsSoundOn());
    this._game = null;
    this._menu = null;
    this.game();
    return true;
  },
  game: function() {
    if (this._menu) {
      this.removeChild(this._menu, true);
      this._menu = null;
    }
    if (this._game === null) {
      this._game = cpz.Game.create(this);
    }
    if (this._game.getParent() === null) {
      this.addChild(this._game, cpz.GameSceneZOrder.Game);
    }
    return this._game;
  },
  menu: function() {
    return this.menuWithLayout(cpz.MenuLayoutType.None);
  },
  menuWithLayout: function(layout) {
    if (this._menu === null) {
      this._menu = cpz.Menu.create(this, layout);
    }
    if (this._menu.getParent() === null) {
      this.addChild(this._menu, cpz.GameSceneZOrder.Menu);
    }
    return this._menu;
  },
  newGame: function() {
    var game;
    game = this.game();
    game.newGame();
    this.playSound('shuffle');
    return this;
  },
  retryGame: function() {
    var game;
    game = this.game();
    game.retryGame();
    this.playSound('shuffle');
    return this;
  },
  setResolution: function(resolution) {
    this._conf.setResolution(resolution);
    this.setContentSize(this._conf.getResolutionSize());
    this.layout(false);
    this._conf.save();
    return this;
  },
  setTheme: function(theme) {
    this._conf.setTheme(theme);
    this.layout();
    this._conf.save();
    return this;
  },
  playSound: function(soundName) {
    var audio;
    audio = cc.AudioEngine.getInstance();
    if (this._conf.getIsSoundOn()) {
      audio.playEffect(cpz.CommonPath + 'sound/' + soundName + '.mp3');
    }
    return this;
  },
  playBackgroundMusic: function(play) {
    var audio;
    audio = cc.AudioEngine.getInstance();
    if (play && this._conf.getIsSoundOn()) {
      audio.setMusicVolume(0.5);
      switch (this._bgMusicTheme) {
        case cpz.GameSceneBGMusicTheme.Theme1:
          audio.playMusic(cpz.CommonPath + 'sound/bgm2.mp3', true);
          return this._bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme2;
        case cpz.GameSceneBGMusicTheme.Theme2:
          audio.playMusic(cpz.CommonPath + 'sound/bgm3.mp3', true);
          return this._bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme3;
        default:
          audio.playMusic(cpz.CommonPath + 'sound/bgm1.mp3', true);
          return this._bgMusicTheme = cpz.GameSceneBGMusicTheme.Theme1;
      }
    } else if (this._bgMusicTheme !== cpz.GameSceneBGMusicTheme.ThemeNone) {
      return audio.stopMusic();
    }
  },
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
    if (this._game) {
      this._game.layout(anim);
    }
    if (this._menu) {
      this._menu.layout(anim);
    }
    return this;
  },
  getConf: function() {
    return this._conf;
  },
  getGame: function() {
    return this._game;
  },
  getMenu: function() {
    return this._menu;
  }
});

cpz.GameSceneCommon.create = function() {
  var obj;
  obj = new cpz.GameScene();
  if (obj && obj.init()) {
    return obj;
  }
  return null;
};
