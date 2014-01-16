###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuLabelContainer = cpz.MenuBox.extend(
  _container: null

  _margin: null

  ctor: ->
    @_super()
    
    @_container = null

  initWithConfAndContentSizeAndFntFile: (conf, size, fntFile) ->
    return false unless @_super(conf, size)
    
    @_container = new cpz.MenuLabel()
    @_container.initWithContentSizeAndFntFile(size, fntFile)
    @_container.setAnchorPoint(cc.p(0.5, 0.5))
    @addChild(@_container)
    
    @_margin = cc.size(0, 0)
    
    return true

  getString: -> @_container.getString()
  setString: (str) ->
    @_container.setString(str)
    @
    
  getWidth: -> @_container.getWidth()
  setWidth: (width) ->
    @_container.setWidth(width)
    @
    
  setAlignment: (alignment) ->
    @_container.setAlignment(alignment)
    @

  getMargin: -> @_margin
  setMargin: (@_margin) ->
    @_margin = margin
    
    @layout()
    @

  layout: (anim = true) ->
    @_super(anim)
    
    size = @getContentSize()
    
    if(@_container)
      @_container.setPosition(cc.p(size.width / 2, size.height / 2))
      @_container.setContentSize(cc.size(size.width - 2 * margin.width, size.height - 2 * margin.height))
      @_container.setWidth(size.width - 2 * margin.width)

  onTouchBegan: (touch, event) ->
    return false unless @_super(touch, event)
    
    return @_container.ccTouchBegan(touch, event)
  
  onTouchMoved: (touch, event) ->
    @_super(touch, event)
    
    @_container.ccTouchMoved(touch, event)

  onTouchEnded: (touch, event) ->
    @_super(touch, event)
    
    @_container.ccTouchEnded(touch, event)
  
  onTouchCancelled: (touch, event) ->
    @_super(touch, event)
      
    @_container.ccTouchCancelled(touch, event)

)
