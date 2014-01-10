###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.CardBoardState =
  Empty: 1
  Yes: 2
  No: 3

cpz.CardBoard = cpz.Card.extend(
  _emptySprite: null
  _yesSprite: null
  _noSprite: null

  _state: null

  ctor: ->
    @_super()

    @_state = cpz.CardBoardState.Empty

  initWithConf: (conf) ->
    return false unless @initWithTexture cc.textureNull(), 1

    @setConf conf

    true

  getState: -> @_state
  setState: (state, force = false) ->
    if @_state isnt state or force
      switch state
        when cpz.CardBoardState.Yes then @setSpriteBatchNode @_yesSprite
        when cpz.CardBoardState.No then @setSpriteBatchNode @_noSprite
        else @setSpriteBatchNode @_emptySprite

      @_state = state

  setConf: (conf) ->
    if @_emptySprite is null then @_emptySprite = cc.SpriteBatchNode.createWithTexture cc.textureNull(), 1
    if @_yesSprite is null then @_yesSprite = cc.SpriteBatchNode.createWithTexture cc.textureNull(), 1
    if @_noSprite is null then @_noSprite = cc.SpriteBatchNode.createWithTexture cc.textureNull(), 1

    conf.getNodeThemePath 'cardboardempty', @_emptySprite
    conf.getNodeThemePath 'cardboardyes', @_yesSprite
    conf.getNodeThemePath 'cardboardno', @_noSprite

    @setState @getState, true
)

cpz.CardBoard.createWithConf = (conf) ->
  obj = new cpz.CardBoard()
  return obj if obj and obj.initWithConf(conf)
  null