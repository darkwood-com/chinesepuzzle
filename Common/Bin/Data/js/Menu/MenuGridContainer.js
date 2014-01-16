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
  initWithConf: function(conf) {
    if (!this._super(conf)) {
      return false;
    }
    this._container = new MenuGrid();
    this._container.init();
    this._container.setAnchorPoint(cc.p(0.5, 0.5));
    this.addChild(this._container);
    this._margin = cc.size(0, 0);
    return true;
  },
  getGridSize: function() {
    return this._container.getGridSize();
  },
  setGridSize: function(gridSize) {
    this._container.setGridSize(gridSize);
    return this;
  },
  getMargin: function() {
    return this._margin;
  },
  setMargin: function(margin) {
    this._margin = margin;
    this.layout();
    return this;
  },
  getPage: function() {
    return this._container.getPage();
  },
  setPage: function(page) {
    this._container.setPage(page);
    return this;
  },
  getMinimumTouchLengthToSlide: function() {
    return this._container.getMinimumTouchLengthToSlide();
  },
  setMinimumTouchLengthToSlide: function(length) {
    this._container.setMinimumTouchLengthToSlide(length);
    return this;
  },
  getMinimumTouchLengthToChangePage: function() {
    return this._container.getMinimumTouchLengthToChangePage();
  },
  setMinimumTouchLengthToChangePage: function(length) {
    this._container.setMinimumTouchLengthToChangePage(length);
    return this;
  },
  getItems: function() {
    return this._container.getItems();
  },
  setItems: function(items) {
    this._container.setItems(items);
    return this;
  },
  layout: function(anim) {
    var size;
    if (anim == null) {
      anim = true;
    }
    this._super(anim);
    size = this.getContentSize();
    if (this._container) {
      this._container.setPosition(cc.p(size.width / 2, size.height / 2));
      return this._container.setContentSize(cc.size(size.width - 2 * this._margin.width, size.height - 2 * this._margin.height));
    }
  },
  onTouchBegan: function(touch, event) {
    if (!this._super(touch, event)) {
      return false;
    }
    return this._container.ccTouchBegan(touch, event);
  },
  onTouchMoved: function(touch, event) {
    this._super(touch, event);
    return this._container.ccTouchMoved(touch, event);
  },
  onTouchEnded: function(touch, event) {
    this._super(touch, event);
    return this._container.ccTouchEnded(touch, event);
  },
  onTouchCancelled: function(touch, event) {
    this._super(touch, event);
    return this._container.ccTouchCancelled(touch, event);
  }
});
