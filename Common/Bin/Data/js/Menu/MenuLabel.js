/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuLabel = cc.Node.extend({
  _label: null,
  _resetLabel: function() {},
  _startSwipe: null,
  _state: null,
  _scrollTouch: null,
  _offsetSwipe: null,
  _offsetScroll: null,
  ctor: function() {
    return this._super();
  },
  initWithContentSizeAndFntFile: function(size, fntFile) {},
  setString: function(str) {},
  getString: function() {},
  setWidth: function(width) {},
  getWidth: function() {},
  setAlignment: function(alignment) {},
  getOffsetSwipe: function() {
    return this._offsetSwipe;
  },
  setOffsetSwipe: function(_offsetSwipe) {
    this._offsetSwipe = _offsetSwipe;
    return this;
  },
  getOffsetScroll: function() {
    return this._offsetScroll;
  },
  setOffsetScroll: function(_offsetScroll) {
    this._offsetScroll = _offsetScroll;
    return this;
  },
  setContentSize: function(size) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  visit: function() {},
  onTouchBegan: function(touch, event) {},
  onTouchMoved: function(touch, event) {},
  onTouchEnded: function(touch, event) {},
  onTouchCancelled: function(touch, event) {}
});
