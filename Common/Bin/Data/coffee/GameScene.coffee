###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GameLayer = cc.Layer.extend(
  isMouseDown: false
  helloImg: null
  helloLabel: null
  circle: null
  sprite: null
  ctor: ->
    @_super()
    cc.associateWithNative this, cc.Layer

  init: ->
    @_super()
    size = cc.Director.getInstance().getWinSize()
    @helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38)
    @helloLabel.setPosition cc.p(size.width / 2, size.height - 40)
    @addChild @helloLabel, 5
    true
)
cpz.GameSceneCommon = cc.Scene.extend(
  ctor: ->
    @_super()
    cc.associateWithNative this, cc.Scene

    #set langage
    lang = cc.CCLang.getInstance()
    lang.setLang cc.LANGUAGE_FRENCH
    lang.addLang 'lang'

  onEnter: ->
    @_super()
    layer = new cpz.GameLayer()
    @addChild layer
    layer.init()
)