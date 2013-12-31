/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.Menu = cc.Layer.extend({
  _nav: [],
  _gs: null,
  _ml: null,
  ctor: function() {
    return this._super();
  },
  initWithGameSceneAndLayout: function(gs, layout) {
    if (!this.init()) {
      return false;
    }
    return true;
  },
  draw: function() {},
  step: function(dt) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  pushNav: function(mBox) {},
  popNav: function() {},
  okMenu: function(item) {},
  registerWithTouchDispatcher: function() {},
  ccTouchBegan: function(touch, event) {},
  ccTouchMoved: function(touch, event) {},
  ccTouchEnded: function(touch, event) {},
  ccTouchCancelled: function(touch, event) {},
  getGameScene: function() {
    return this._gs;
  },
  getLayout: function() {
    return this._ml;
  }
});

cpz.Menu.create = function(gs, layout) {
  var layer;
  layer = new cpz.Menu();
  if (layer && layer.initWithGameSceneAndLayout(gs, layout)) {
    return layer;
  }
  return null;
};
