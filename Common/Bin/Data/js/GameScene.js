/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GameLayer = cc.Layer.extend({
  isMouseDown: false,
  helloImg: null,
  helloLabel: null,
  circle: null,
  sprite: null,
  ctor: function() {
    this._super();
    return cc.associateWithNative(this, cc.Layer);
  },
  init: function() {
    var size;
    this._super();
    size = cc.Director.getInstance().getWinSize();
    this.helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38);
    this.helloLabel.setPosition(cc.p(size.width / 2, size.height - 40));
    this.addChild(this.helloLabel, 5);
    return true;
  }
});

cpz.GameSceneCommon = cc.Scene.extend({
  ctor: function() {
    var lang;
    this._super();
    cc.associateWithNative(this, cc.Scene);
    lang = cc.CCLang.getInstance();
    lang.setLang(cc.LANGUAGE_FRENCH);
    return lang.addLang('lang');
  },
  onEnter: function() {
    var layer;
    this._super();
    layer = new cpz.GameLayer();
    this.addChild(layer);
    return layer.init();
  }
});
