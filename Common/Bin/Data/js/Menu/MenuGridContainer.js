/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuGridContainer = cpz.MenuBox.extend({
  _container: null,
  _gridSize: null,
  _margin: null,
  _page: null,
  _minimumTouchLengthToSlide: null,
  _minimumTouchLengthToChangePage: null,
  ctor: function() {
    return this._super();
  },
  initWithConf: function(conf) {},
  getGridSize: function() {
    return this._gridSize;
  },
  setGridSize: function(_gridSize) {
    this._gridSize = _gridSize;
    return this;
  },
  getMargin: function() {
    return this._margin;
  },
  setMargin: function(_margin) {
    this._margin = _margin;
    return this;
  },
  getPage: function() {
    return this._page;
  },
  setPage: function(_page) {
    this._page = _page;
    return this;
  },
  getMinimumTouchLengthToSlide: function() {
    return this._minimumTouchLengthToSlide;
  },
  setMinimumTouchLengthToSlide: function(_minimumTouchLengthToSlide) {
    this._minimumTouchLengthToSlide = _minimumTouchLengthToSlide;
    return this;
  },
  getMinimumTouchLengthToChangePage: function() {
    return this._minimumTouchLengthToChangePage;
  },
  setMinimumTouchLengthToChangePage: function(_minimumTouchLengthToChangePage) {
    this._minimumTouchLengthToChangePage = _minimumTouchLengthToChangePage;
    return this;
  },
  getItems: function() {
    return this._items;
  },
  setItems: function(_items) {
    this._items = _items;
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
