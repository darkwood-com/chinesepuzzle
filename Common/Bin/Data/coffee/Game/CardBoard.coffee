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
    true

  getState: -> @_state
  setState: (state, force = false) ->
    if @_state isnt state or force
      switch state
        when 0
        else


  setConf: (conf) ->
)

cpz.CardBoard.createWithConf = (conf) ->
  obj = new cpz.CardBoard()
  return obj if obj and obj.initWithConf(conf)
  null