###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuBox = cc.Node.extend(
  _bg: null
  _validBtn: null
  _titleLabel: null

  _state: null
  _itemForTouch: (touch) ->
  _selectedItem: null

  _layoutFontFile: null

  _titlePosition: null
  _validPosition: null

  _items: []

  ctor: ->
    @_super()

  initWithConf: (conf) ->
  initWithConfAndContentSize: (conf, size) ->

  getTitle: ->
  setTitle: (title, fontFile) ->
  getTitlePosition: -> @_titlePosition
  setTitlePosition: (@_titlePosition) -> @
  getValidPosition: -> @_validPosition
  setValidPosition: (@_validPosition) -> @

  setContentSize: (size) ->

  layout: (anim = true) ->

  setOkTarget: (rec, selector) ->

  ccTouchBegan: (touch, event) ->
  ccTouchMoved: (touch, event) ->
  ccTouchEnded: (touch, event) ->
  ccTouchCancelled: (touch, event) ->

  setItems: (@_items) -> @
  getItems: -> @_items
  addItem: (child, zOrder, tag) ->
  removeItemByTag: (tag, cleanup) ->
)
