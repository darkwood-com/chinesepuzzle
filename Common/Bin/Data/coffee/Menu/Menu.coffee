###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.Menu = cc.Layer.extend(
  _nav: []

  _gs: null
  _ml: null

  ctor: ->
    @_super()

  initWithGameSceneAndLayout: (gs, layout) ->
    return false unless @init()

    true

  draw: ->
  step: (dt) ->
  layout: (anim = true) ->

  pushNav: (mBox) ->
  popNav: ->

  okMenu: (item) ->

  #input touches/mouse
  registerWithTouchDispatcher: ->

  ccTouchBegan: (touch, event) ->
  ccTouchMoved: (touch, event) ->
  ccTouchEnded: (touch, event) ->
  ccTouchCancelled: (touch, event) ->

  getGameScene: -> @_gs
  getLayout: -> @_ml
)

cpz.Menu.create = (gs, layout) ->
  obj = new cpz.Menu()
  return obj if obj and obj.initWithGameSceneAndLayout(gs, layout)
  null
