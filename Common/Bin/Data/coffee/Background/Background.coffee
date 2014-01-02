###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.Background = cc.Layer.extend(
  _bgPattern: null
  _gs: null

  initWithGameScene: (gs) ->
    return false unless @_super()

    ccTexParams texParams = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT}
    @_bgPattern = cc.Sprite.create gs.getConf().getRootPath('bgPattern.png')
    #@_bgPattern.getTexture().setTexParameters(&texParams)
    @_bgPattern.setAnchorPoint cc.p(0, 0)
    @addChild @_bgPattern, cpz.GameSceneZOrder.BG

    @_gs = gs
    @setContentSize @_gs.getConf().getResolutionSize()

    true

  setContentSize: (size) ->
    @_super size

    if @_bgPattern
      rect = cc.rect 0, 0, size.width, size.height
      @_bgPattern.setTextureRect rect

  getGameScene: -> @_gs
)

cpz.Background.create = (gs) ->
  obj = new cpz.Background()
  return obj if obj and obj.initWithGameScene(gs)
  null