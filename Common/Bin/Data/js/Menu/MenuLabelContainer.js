/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuLabelContainer = cpz.MenuBox.extend({
  _container: null,
  _margin: null,
  ctor: function() {
    return this._super();
  },
  initWithConfAndContentSizeAndFntFile: function(conf, size, fntFile) {},
  getString: function() {},
  setString: function(str) {},
  getWidth: function() {},
  setWidth: function(width) {},
  setAlignment: function(alignment) {},
  getMargin: function() {
    return this._margin;
  },
  setMargin: function(_margin) {
    this._margin = _margin;
    return this;
  },
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  onTouchBegan: function(touch, event) {},
  onTouchMoved: function(touch, event) {},
  onTouchEnded: function(touch, event) {},
  onTouchCancelled: function(touch, event) {}
});
