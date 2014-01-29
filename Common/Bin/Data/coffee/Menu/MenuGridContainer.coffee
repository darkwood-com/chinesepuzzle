###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuGridContainer = cpz.MenuBox.extend(
  _container: null

  _gridSize: null
  _margin: null
  _page: null
  _minimumTouchLengthToSlide: null
  _minimumTouchLengthToChangePage: null

  ctor: ->
    @_super()

  initWithConf: (conf) ->
    return false unless @_super conf

    @_container = new cpz.MenuGrid()
    @_container.init()
    @_container.setAnchorPoint cc.p(0.5, 0.5)
    @addChild @_container

    @_margin = cc.size(0, 0)

    true

  getGridSize: -> @_container.getGridSize()
  setGridSize: (gridSize) ->
    @_container.setGridSize(gridSize)
    @
  
  getMargin: -> @_margin
  setMargin: (margin) ->
    @_margin = margin

    @layout()
    @
    
  getPage: -> @_container.getPage()
  setPage: (page) ->
    @_container.setPage(page)
    @
    
  getMinimumTouchLengthToSlide: -> @_container.getMinimumTouchLengthToSlide()
  setMinimumTouchLengthToSlide: (length) ->
    @_container.setMinimumTouchLengthToSlide(length)
    @
  
  getMinimumTouchLengthToChangePage: -> @_container.getMinimumTouchLengthToChangePage()
  setMinimumTouchLengthToChangePage: (length) ->
    @_container.setMinimumTouchLengthToChangePage(length)
    @
    
  getItems: -> @_container.getItems()
  setItems: (items) ->
    @_container.setItems(items)
    @

  layout: (anim = true) ->
    @_super anim
    
    size = @getContentSize()
    
    if @_container
      @_container.setPosition(cc.p(size.width / 2, size.height / 2))
      @_container.setContentSize(cc.size(size.width - 2 * @_margin.width, size.height - 2 * @_margin.height))

  onTouchBegan: (touch, event) ->
    return false if @_super(touch, event)

    return @_container.onTouchBegan(touch, event)
    
  onTouchMoved: (touch, event) ->
    @_super(touch, event)
    
    @_container.onTouchMoved(touch, event)
  
  onTouchEnded: (touch, event) ->
    @_super(touch, event)
    
    @_container.onTouchEnded(touch, event)
    
  onTouchCancelled: (touch, event) ->
    @_super(touch, event)
    
    @_container.onTouchCancelled(touch, event)
)
