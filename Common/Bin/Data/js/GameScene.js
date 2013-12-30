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

cpz.GameSceneCommon = cc.Scene.extend({
  _conf: null,
  _game: null,
  _menu: null,
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
  menu: function() {},
  menuWithLayout: function(ml) {},
  newGame: function() {},
  retryGame: function() {},
  setResolution: function(resolution) {},
  setTheme: function(theme) {},
  playSound: function(soundName) {},
  playBackgroundMusic: function(play) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
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
  var layer;
  layer = new cpz.GameScene();
  if (layer && layer.init()) {
    return layer;
  }
  return null;
};
