###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuLabelScrollLayerState =
  Idle: 0
  Sliding: 1

cpz.MenuLabel = cc.Node.extend(
  _label: null

  _startSwipe: null
  _state: null
  _scrollTouch: null

  _offsetSwipe: null
  _offsetScroll: null

  ctor: ->
    @_super()

    @_label = null
    @_startSwipe = 0
    @_offsetSwipe = 0
    @_offsetScroll = 0
    @_scrollTouch = null
    @_state = cpz.MenuLabelScrollLayerState.Idle

  initWithContentSizeAndFntFile: (size, fntFile) ->
    @setContentSize size
    
    @_label = new cc.LabelBMFont()
    @_label.initWithString("", fntFile, 0, cc.TEXT_ALIGNMENT_LEFT)
    @_label.setAnchorPoint(cc.p(0.5, 1.0))
    @addChild(@_label)
    
    return true

  getString: -> @_label.getString()
  setString: (str) ->
    @_label.setString(str)
    @

  getWidth: -> @_label.getContentSize().width
  setWidth: (width) ->
    @_label.setWidth(width)
    @
    
  setAlignment: (alignment) ->
    @_label.setAlignment(alignment)
    @
    
  getOffsetSwipe: -> @_offsetSwipe
  setOffsetSwipe: (offsetSwipe) ->
    @_offsetSwipe = offsetSwipe
    
    @layout()
    @
    
  getOffsetScroll: -> @_offsetScroll
  setOffsetScroll: (@_offsetScroll) -> @
  
  setContentSize: (size) ->
    @_super(size)
    
    @layout()
    @

  layout: (anim = true) ->
    size = @getContentSize()
    
    if(@_label)
      @_label.setPosition(cc.pAdd(cc.p(size.width / 2, size.height), cc.p(0, @_offsetScroll + @_offsetSwipe)))
    
  visit: ->
    #glEnable(GL_SCISSOR_TEST)
    
    #CCSize size = @getContentSize()
    #CCRect rect = CCRectMake(0, 0, size.width, size.height)
    #rect.origin = @convertToWorldSpace(rect.origin)
    #cc.Director.getInstance().getOpenGLView().setScissorInPoints(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height)
    
    @_super()
    
    #glDisable(GL_SCISSOR_TEST)

  onTouchBegan: (touch, event) ->
    if not @_scrollTouch
      @_scrollTouch = touch
    else
      return false
    
    touchPoint = touch.getLocation()
    
    @_startSwipe = touchPoint.y
    @_state = cpz.MenuLabelScrollLayerState.Idle
    
    true
    
  onTouchMoved: (touch, event) ->
    return if @_scrollTouch isnt touch
    
    touchPoint = touch.getLocation()
    
    # If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
    # Of course only if we not already in sliding mode
    if @_state isnt cpz.MenuLabelScrollLayerState.Sliding
      @_state = cpz.MenuLabelScrollLayerState.Sliding
      
      # Avoid jerk after state change.
      @_startSwipe = touchPoint.y
    
    if @_state is cpz.MenuLabelScrollLayerState.Sliding
      @setSwipe(touchPoint.y - @_startSwipe)
    
  onTouchEnded: (touch, event) ->
    return if @_scrollTouch isnt touch
    
    @_scrollTouch = null
    
    touchPoint = touch.getLocation()
    
    @setScroll(@getScroll() + touchPoint.y - @_startSwipe)
    @setSwipe(0)
    
  onTouchCancelled: (touch, event) ->
    if @_scrollTouch is touch
      @_scrollTouch = null
)
