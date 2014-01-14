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

  initWithConfAndContentSizeAndFntFile: (conf, size, fntFile) ->

  getString: ->
  setString: (str) ->
  getWidth: ->
  setWidth: (width) ->
  setAlignment: (alignment) ->

  getMargin: -> @_margin
  setMargin: (@_margin) -> @

  layout: (anim = true) ->

  onTouchBegan: (touch, event) ->
  onTouchMoved: (touch, event) ->
  onTouchEnded: (touch, event) ->
  onTouchCancelled: (touch, event) ->
)
