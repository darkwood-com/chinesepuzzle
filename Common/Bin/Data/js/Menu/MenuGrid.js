/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuGridScrollLayerState = {
  Idle: 0,
  Sliding: 1
};

cpz.MenuGrid = cc.Node.extend({
  _itemsGrid: null,
  _resetGrid: function() {
    var a, coord, item, k, p, pageMax, pageMin, _i, _j, _len, _ref;
    _ref = this._itemsGrid.allKeys();
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      coord = _ref[_i];
      item = this._itemsGrid.object(coord);
      this.removeChild(item, true);
    }
    this._itemsGrid.removeAllObjects();
    a = this._gridSize.width * this._gridSize.height;
    pageMin = a * (this._page - 1);
    pageMax = a * (this._page + 2) - 1;
    for (k = _j = pageMin; pageMin <= pageMax ? _j <= pageMax : _j >= pageMax; k = pageMin <= pageMax ? ++_j : --_j) {
      if (k >= 0 && k < this._items.length) {
        item = this._items[k];
        item.setAnchorPoint(cc.p(0.5, 0.5));
        this.addChild(item);
        p = k / a;
        coord = cc.p(p * this._gridSize.width + k % this._gridSize.width, this._gridSize.height - 1 - (k - p * a) / this._gridSize.width);
        this._itemsGrid.setObject(item, coord);
      }
    }
    return this.layout();
  },
  _startSwipe: 0,
  _state: cpz.MenuGridScrollLayerState.Idle,
  _scrollTouch: null,
  _swipeToPageEnded: function() {
    this.setPage(this.getPage() - Math.round(this.getSwipe() / this.getContentSize().width));
    if (this._delegate) {
      return this._delegate.scrollLayerScrolledToPageNumber(this, this._page);
    }
  },
  _getMaxPage: function() {
    return Math.ceil(this._items.length / (this._gridSize.width * this._gridSize.height));
  },
  _selectedItem: null,
  _items: [],
  _gridSize: null,
  _offsetSwipe: null,
  _size: null,
  _page: null,
  _delegate: null,
  _minimumTouchLengthToSlide: null,
  _minimumTouchLengthToChangePage: null,
  ctor: function() {
    this._super();
    this._itemsGrid = new cc.Dictionary();
    this._gridSize = cc.size(0, 0);
    this._page = 0;
    this._delegate = null;
    this._startSwipe = 0;
    this._offsetSwipe = 0;
    this._scrollTouch = null;
    this._selectedItem = null;
    return this._state = cpz.MenuGridScrollLayerState.Idle;
  },
  init: function() {
    this._items = [];
    this._minimumTouchLengthToSlide = 10.5;
    this._minimumTouchLengthToChangePage = 100.5;
    return true;
  },
  initWithContentSize: function(size) {
    if (this.init()) {
      this.setContentSize(size);
      this._minimumTouchLengthToChangePage = size.width / 8;
      return true;
    }
    return false;
  },
  getItems: function() {
    return this._items;
  },
  setItems: function(_items) {
    this._items = _items;
    this._resetGrid();
    return this;
  },
  getGridSize: function() {
    return this._gridSize;
  },
  setGridSize: function(_gridSize) {
    this._gridSize = _gridSize;
    this._resetGrid();
    return this;
  },
  getSwipe: function() {
    return this._offsetSwipe;
  },
  setSwipe: function(_offsetSwipe) {
    this._offsetSwipe = _offsetSwipe;
    this.layout();
    return this;
  },
  setContentSize: function(size) {
    this._super(size);
    this.layout();
    return this;
  },
  layout: function(anim) {
    var coord, item, origin, pad, size, _i, _len, _ref, _results;
    if (anim == null) {
      anim = true;
    }
    size = this.getContentSize();
    if (this._gridSize.width > 0 && this._gridSize.height > 0) {
      pad = cc.size(size.width / this._gridSize.width, size.height / this._gridSize.height);
      origin = cc.p(size.width / (2 * this._gridSize.width) - this._page * size.width, size.height / (2 * this._gridSize.height));
      _ref = this._itemsGrid.allKeys();
      _results = [];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        coord = _ref[_i];
        item = this._itemsGrid.object(coord);
        _results.push(item.setPosition(cc.pAdd(origin, cc.p(coord.x * pad.width + this._offsetSwipe, coord.y * pad.height))));
      }
      return _results;
    }
  },
  visit: function() {
    var rect, size;
    size = this.getContentSize();
    rect = cc.rect(0, 0, size.width, size.height);
    rect.origin = this.convertToWorldSpace(rect.origin);
    cc.Director.getInstance().getOpenGLView().setScissorInPoints(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    return this._super();
  },
  getPage: function() {
    return this._page;
  },
  setPage: function(page) {
    if (page >= 0 && page < this._getMaxPage()) {
      this._page = page;
      this.setSwipe(0);
      this._resetGrid();
    }
    return this;
  },
  swipeToPage: function(page) {
    if (page >= 0 && page < this._getMaxPage()) {
      return this.runAction(cc.Sequence.create([]));
    }
  },
  getDelegate: function() {
    return this._delegate;
  },
  setDelegate: function(_delegate) {
    this._delegate = _delegate;
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
  onTouchBegan: function(touch, event) {
    var child, local, r, touchPoint, _i, _len, _ref;
    touchPoint = touch.getLocation();
    if (this._items && this._items.count() > 0) {
      _ref = this._items;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        child = _ref[_i];
        if (child instanceof cc.MenuItem && child.isVisible() && child.isEnabled()) {
          local = child.convertToNodeSpace(touchPoint);
          r = child.rect();
          r.x = 0;
          r.y = 0;
          if (cc.rectContainsPoint(r, local)) {
            if (this._selectedItem) {
              this._selectedItem.unselected();
            }
            this._selectedItem = child;
            this._selectedItem.selected();
            this._selectedItem.runAction(cc.Sequence.create([]));
          }
        }
      }
    }
    if (!this._scrollTouch) {
      this._scrollTouch = touch;
    } else {
      return false;
    }
    this._startSwipe = touchPoint.x;
    this._state = cpz.MenuGridScrollLayerState.Idle;
    return true;
  },
  onTouchMoved: function(touch, event) {
    var touchPoint;
    if (this._scrollTouch !== touch) {
      return;
    }
    touchPoint = touch.getLocation();
    if (this._state !== cpz.MenuGridScrollLayerState.Sliding && fabsf(touchPoint.x - this._startSwipe) >= this._minimumTouchLengthToSlide) {
      this._state = cpz.MenuGridScrollLayerState.Sliding;
      this._startSwipe = touchPoint.x;
      if (this._delegate) {
        this._delegate.scrollLayerScrollingStarted(this);
      }
    }
    if (this._state === cpz.MenuGridScrollLayerState.Sliding) {
      return this.setSwipe(touchPoint.x - this._startSwipe);
    }
  },
  onTouchEnded: function(touch, event) {
    var selectedPage, swipe, touchPoint;
    if (this._scrollTouch !== touch) {
      return;
    }
    this._scrollTouch = null;
    touchPoint = touch.getLocation();
    selectedPage = this.getPage();
    swipe = touchPoint.x - this._startSwipe;
    this.setSwipe(swipe);
    if (swipe > 0 && swipe >= this._minimumTouchLengthToChangePage) {
      selectedPage -= ((this.getSwipe() - this._minimumTouchLengthToChangePage) / this.getContentSize().width) + 1;
    } else if (swipe < 0 && swipe <= -this._minimumTouchLengthToChangePage) {
      selectedPage += -((this.getSwipe() + this._minimumTouchLengthToChangePage) / this.getContentSize().width) + 1;
    }
    if (selectedPage < 0) {
      selectedPage = 0;
    }
    if (selectedPage >= this._getMaxPage()) {
      selectedPage = this._getMaxPage() - 1;
    }
    return this.swipeToPage(selectedPage);
  },
  onTouchCancelled: function(touch, event) {
    if (this._scrollTouch === touch) {
      this._scrollTouch = null;
      return this.setPage(this._page);
    }
  }
});
