/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuBox = cc.Node.extend({
  _bg: null,
  _validBtn: null,
  _titleLabel: null,
  _state: null,
  _itemForTouch: function(touch) {},
  _selectedItem: null,
  _layoutFontFile: null,
  _titlePosition: null,
  _validPosition: null,
  _items: [],
  ctor: function() {
    return this._super();
  },
  initWithConf: function(conf) {},
  initWithConfAndContentSize: function(conf, size) {},
  getTitle: function() {},
  setTitle: function(title, fontFile) {},
  getTitlePosition: function() {
    return this._titlePosition;
  },
  setTitlePosition: function(_titlePosition) {
    this._titlePosition = _titlePosition;
    return this;
  },
  getValidPosition: function() {
    return this._validPosition;
  },
  setValidPosition: function(_validPosition) {
    this._validPosition = _validPosition;
    return this;
  },
  setItems: function(_items) {
    this._items = _items;
    return this;
  },
  getItems: function() {
    return this._items;
  },
  addItem: function(child, zOrder, tag) {},
  removeItemByTag: function(tag, cleanup) {},
  setContentSize: function(size) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  setOkTarget: function(rec, selector) {},
  ccTouchBegan: function(touch, event) {},
  ccTouchMoved: function(touch, event) {},
  ccTouchEnded: function(touch, event) {},
  ccTouchCancelled: function(touch, event) {}
});
