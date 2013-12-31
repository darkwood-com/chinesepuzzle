###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuLabel = cc.Node.extend(
  _label: null

  _resetLabel: ->

  _startSwipe: null
  _state: null
  _scrollTouch: null

  _offsetSwipe: null
  _offsetScroll: null

  ctor: ->
    @_super()

  initWithContentSizeAndFntFile: (size, fntFile) ->

  setString: (str) ->
  getString: ->
  setWidth: (width) ->
  getWidth: ->
  setAlignment: (alignment) ->
  getOffsetSwipe: -> @_offsetSwipe
  setOffsetSwipe: (@_offsetSwipe) -> @
  getOffsetScroll: -> @_offsetScroll
  setOffsetScroll: (@_offsetScroll) -> @
  setContentSize: (size) ->

  layout: (anim = true) ->
  visit: ->

  ccTouchBegan: (touch, event) ->
  ccTouchMoved: (touch, event) ->
  ccTouchEnded: (touch, event) ->
  ccTouchCancelled: (touch, event) ->
)
