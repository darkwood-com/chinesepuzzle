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

  getGridSize: -> @_gridSize
  setGridSize: (@_gridSize) -> @
  getMargin: -> @_margin
  setMargin: (@_margin) -> @
  getPage: -> @_page
  setPage: (@_page) -> @
  getMinimumTouchLengthToSlide: -> @_minimumTouchLengthToSlide
  setMinimumTouchLengthToSlide: (@_minimumTouchLengthToSlide) -> @
  getMinimumTouchLengthToChangePage: -> @_minimumTouchLengthToChangePage
  setMinimumTouchLengthToChangePage: (@_minimumTouchLengthToChangePage) -> @
  getItems: -> @_items
  setItems: (@_items) -> @

  layout: (anim = true) ->

  ccTouchBegan: (touch, event) ->
  ccTouchMoved: (touch, event) ->
  ccTouchEnded: (touch, event) ->
  ccTouchCancelled: (touch, event) ->
)
