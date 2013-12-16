/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

var GameLayer, GameScene;

GameLayer = cc.Layer.extend({
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

GameScene = cc.Scene.extend({
  ctor: function() {
    this._super();
    return cc.associateWithNative(this, cc.Scene);
  },
  onEnter: function() {
    var layer;
    this._super();
    layer = new GameLayer();
    this.addChild(layer);
    return layer.init();
  }
});
