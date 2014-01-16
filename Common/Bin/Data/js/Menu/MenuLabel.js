/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuLabelScrollLayerState = {
  Idle: 0,
  Sliding: 1
};

cpz.MenuLabel = cc.Node.extend({
  _label: null,
  _startSwipe: null,
  _state: null,
  _scrollTouch: null,
  _offsetSwipe: null,
  _offsetScroll: null,
  ctor: function() {
    this._super();
    this._label = null;
    this._startSwipe = 0;
    this._offsetSwipe = 0;
    this._offsetScroll = 0;
    this._scrollTouch = null;
    return this._state = cpz.MenuLabelScrollLayerState.Idle;
  },
  initWithContentSizeAndFntFile: function(size, fntFile) {
    this.setContentSize(size);
    this._label = new cc.LabelBMFont();
    this._label.initWithString("", fntFile, 0, cc.TEXT_ALIGNMENT_LEFT);
    this._label.setAnchorPoint(cc.p(0.5, 1.0));
    this.addChild(this._label);
    return true;
  },
  getString: function() {
    return this._label.getString();
  },
  setString: function(str) {
    this._label.setString(str);
    return this;
  },
  getWidth: function() {
    return this._label.getContentSize().width;
  },
  setWidth: function(width) {
    this._label.setWidth(width);
    return this;
  },
  setAlignment: function(alignment) {
    this._label.setAlignment(alignment);
    return this;
  },
  getOffsetSwipe: function() {
    return this._offsetSwipe;
  },
  setOffsetSwipe: function(offsetSwipe) {
    this._offsetSwipe = offsetSwipe;
    this.layout();
    return this;
  },
  getOffsetScroll: function() {
    return this._offsetScroll;
  },
  setOffsetScroll: function(_offsetScroll) {
    this._offsetScroll = _offsetScroll;
    return this;
  },
  setContentSize: function(size) {
    this._super(size);
    this.layout();
    return this;
  },
  layout: function(anim) {
    var size;
    if (anim == null) {
      anim = true;
    }
    size = this.getContentSize();
    if (this._label) {
      return this._label.setPosition(cc.pAdd(cc.p(size.width / 2, size.height), cc.p(0, this._offsetScroll + this._offsetSwipe)));
    }
  },
  visit: function() {
    return this._super();
  },
  onTouchBegan: function(touch, event) {
    var touchPoint;
    if (!this._scrollTouch) {
      this._scrollTouch = touch;
    } else {
      return false;
    }
    touchPoint = touch.locationInView();
    touchPoint = cc.Director.getInstance().convertToGL(touchPoint);
    this._startSwipe = touchPoint.y;
    this._state = cpz.MenuLabelScrollLayerState.Idle;
    return true;
  },
  onTouchMoved: function(touch, event) {
    var touchPoint;
    if (this._scrollTouch !== touch) {
      return;
    }
    touchPoint = touch.locationInView();
    touchPoint = cc.Director.getInstance().convertToGL(touchPoint);
    if (this._state !== cpz.MenuLabelScrollLayerState.Sliding) {
      this._state = cpz.MenuLabelScrollLayerState.Sliding;
      this._startSwipe = touchPoint.y;
    }
    if (this._state === cpz.MenuLabelScrollLayerState.Sliding) {
      return this.setSwipe(touchPoint.y - this._startSwipe);
    }
  },
  onTouchEnded: function(touch, event) {
    var touchPoint;
    if (this._scrollTouch !== touch) {
      return;
    }
    this._scrollTouch = null;
    touchPoint = touch.locationInView();
    touchPoint = cc.Director.getInstance().convertToGL(touchPoint);
    this.setScroll(this.getScroll() + touchPoint.y - this._startSwipe);
    return this.setSwipe(0);
  },
  onTouchCancelled: function(touch, event) {
    if (this._scrollTouch === touch) {
      return this._scrollTouch = null;
    }
  }
});
