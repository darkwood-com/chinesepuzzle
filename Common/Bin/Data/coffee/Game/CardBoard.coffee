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

  getState: -> @_state
  setState: (@_state, force) ->

  setConf: (conf) ->
)
