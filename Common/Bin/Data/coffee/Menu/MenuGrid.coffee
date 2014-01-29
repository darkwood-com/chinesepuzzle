###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuGridScrollLayerState =
  Idle: 0
  Sliding: 1

cpz.MenuGrid = cc.Node.extend(
  _itemsGrid: null #items (=3x gridSize)

  _resetGrid: ->
    for coord in @_itemsGrid.allKeys()
      item = @_itemsGrid.object(coord)
      @removeChild(item, true)
    @_itemsGrid.removeAllObjects()

    a = @_gridSize.width * @_gridSize.height
    pageMin = a * (@_page - 1)
    pageMax = a * (@_page + 2) - 1
    for k in [pageMin..pageMax]
      if(k >= 0 and k < @_items.length)
        item = @_items[k]
        item.setAnchorPoint cc.p(0.5, 0.5)
        @addChild(item)

        p = k / a
        coord = cc.p(p * @_gridSize.width + k % @_gridSize.width, @_gridSize.height - 1 - (k - p * a) / @_gridSize.width)
        @_itemsGrid.setObject item, coord

    @layout()

  #The x coord of initial point the user starts their swipe.
  _startSwipe: 0

  #Internal state of scroll (scrolling or idle).
  _state: cpz.MenuGridScrollLayerState.Idle

  #Holds the touch that started the scroll
  _scrollTouch: null

  _swipeToPageEnded: ->
    @setPage @getPage() - Math.round(@getSwipe() / @getContentSize().width)

    @_delegate.scrollLayerScrolledToPageNumber(@, @_page) if @_delegate
    
  _getMaxPage: ->
    return Math.ceil(@_items.length / (@_gridSize.width * @_gridSize.height))

  _selectedItem: null

  _items: []
  _gridSize: null
  _offsetSwipe: null
  _size: null

  _page: null
  _delegate: null
  _minimumTouchLengthToSlide: null
  _minimumTouchLengthToChangePage: null

  ctor: ->
    @_super()

    @_itemsGrid = new cc.Dictionary()
    @_gridSize = cc.size 0, 0
    @_page = 0
    @_delegate = null
    @_startSwipe = 0
    @_offsetSwipe = 0
    @_scrollTouch = null
    @_selectedItem = null
    @_state = cpz.MenuGridScrollLayerState.Idle

  init: ->
    @_items = []

    # Set default minimum touch length to scroll.
    @_minimumTouchLengthToSlide = 10.5
    @_minimumTouchLengthToChangePage = 100.5

    true

  initWithContentSize: (size) ->
    if @init()
      @setContentSize(size)
  
      # Set default minimum touch length to scroll.
      @_minimumTouchLengthToChangePage = size.width / 8
  
      return true

    false

  getItems: -> @_items
  setItems: (@_items) ->
    @_resetGrid()
    @
  getGridSize: -> @_gridSize
  setGridSize: (@_gridSize) ->
    @_resetGrid()
    @
  getSwipe: -> @_offsetSwipe
  setSwipe: (@_offsetSwipe) ->
    @layout()
    @
  setContentSize: (size) ->
    @_super(size)
    @layout()
    @

  layout: (anim = true) ->
    size = @getContentSize()

    if(@_gridSize.width > 0 and @_gridSize.height > 0)
      pad = cc.size(size.width / @_gridSize.width, size.height / @_gridSize.height)
      origin = cc.p(size.width / (2 * @_gridSize.width) - @_page * size.width, size.height / (2 * @_gridSize.height))

      for coord in @_itemsGrid.allKeys()
        item = @_itemsGrid.object(coord)
        item.setPosition(cc.pAdd(origin, cc.p(coord.x * pad.width + @_offsetSwipe, coord.y * pad.height)))

  getPage: -> @_page
  setPage: (page) ->
    if(page >= 0 and page < @_getMaxPage())
      @_page = page
  
      @setSwipe(0)
      @_resetGrid()

    @

  # Moves scrollLayer to page with given number & invokes delegate
  # method scrollLayer:scrolledToPageNumber: at the end of CCMoveTo action.
  # Does nothing if number >= totalScreens or < 0.
  swipeToPage: (page) ->
    if(page >= 0 and page < @_getMaxPage())
      @runAction(cc.Sequence.create([
        #MenuGridSwipeTo::actionWithDuration(0.3, (@_page - page) * @getContentSize().width),
        #CCCallFunc::actionWithTarget(@, callfunc_selector(MenuGrid::swipeToPageEnded))
      ]))

  getDelegate: -> @_delegate
  setDelegate: (@_delegate) -> @
  getMinimumTouchLengthToSlide: -> @_minimumTouchLengthToSlide
  setMinimumTouchLengthToSlide: (@_minimumTouchLengthToSlide) -> @
  getMinimumTouchLengthToChangePage: -> @_minimumTouchLengthToChangePage
  setMinimumTouchLengthToChangePage: (@_minimumTouchLengthToChangePage) -> @

  onTouchBegan: (touch, event) ->
    touchPoint = touch.getLocation()
    
    if @_items and @_items.count() > 0
      for child in @_items
        if child instanceof cc.MenuItem and child.isVisible() and child.isEnabled()
          local = child.convertToNodeSpace(touchPoint)
          r = child.rect()
          r.x = 0
          r.y = 0

          if cc.rectContainsPoint(r, local)
            if @_selectedItem
              @_selectedItem.unselected()
            
            @_selectedItem = child
            @_selectedItem.selected()
            @_selectedItem.runAction(cc.Sequence.create([
              #CCEaseIn::actionWithAction(CCScaleTo::actionWithDuration(0.1, 0.75), 2.5),
              #CCEaseOut::actionWithAction(CCScaleTo::actionWithDuration(0.1, 1.5), 2.5),
            ]))
    
    if !@_scrollTouch
      @_scrollTouch = touch
    else
      return false
    
    @_startSwipe = touchPoint.x
    @_state = cpz.MenuGridScrollLayerState.Idle
    
    return true
    
  onTouchMoved: (touch, event) ->
    return if(@_scrollTouch isnt touch)
    
    touchPoint = touch.getLocation()
    
    # If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
    # Of course only if we not already in sliding mode
    if @_state isnt cpz.MenuGridScrollLayerState.Sliding and fabsf(touchPoint.x - @_startSwipe) >= @_minimumTouchLengthToSlide
      @_state = cpz.MenuGridScrollLayerState.Sliding
      
      # Avoid jerk after state change.
      @_startSwipe = touchPoint.x

      @_delegate.scrollLayerScrollingStarted(@) if @_delegate
    
    if @_state is cpz.MenuGridScrollLayerState.Sliding
      @setSwipe(touchPoint.x - @_startSwipe)
    
  onTouchEnded: (touch, event) ->
    return if(@_scrollTouch isnt touch)
    
    @_scrollTouch = null
    
    touchPoint = touch.getLocation()
    
    selectedPage = @getPage()
    swipe = touchPoint.x - @_startSwipe
    
    @setSwipe(swipe)
    if swipe > 0 and swipe >= @_minimumTouchLengthToChangePage
      selectedPage -= ((@getSwipe() - @_minimumTouchLengthToChangePage) / @getContentSize().width) + 1
    else if(swipe < 0 and swipe <= -@_minimumTouchLengthToChangePage)
      selectedPage += - ((@getSwipe() + @_minimumTouchLengthToChangePage) / @getContentSize().width) + 1
    if selectedPage < 0 then selectedPage = 0
    if selectedPage >= @_getMaxPage() then selectedPage = @_getMaxPage() - 1
    
    @swipeToPage(selectedPage)

  onTouchCancelled: (touch, event) ->
    if @_scrollTouch is touch
      @_scrollTouch = null
      @setPage(@_page)
)
