###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.CardPlayColor =
  Spade: 1
  Club: 2
  Heart: 3
  Diamond: 4

cpz.CardPlayRank =
  Ace: 1
  Two: 2
  Three: 3
  Four: 4
  Five: 5
  Six: 6
  Seven: 7
  Eight: 8
  Nine: 9
  Ten: 10
  Jack: 11
  Queen: 12
  King: 13

cpz.CardPlayFlipAction = cc.Class.extend(
  _cardPlay: null
  _isFaceUp: null

  initWithCardPlay: (card) ->
  update: (time) ->
  copyWithZone: (pZone) ->
)

cpz.CardPlayFlipAction.create = (card) ->


cpz.CardPlay = cpz.Card.extend(
  _faceSprite: null
  _backSprite: null

  _color: null
  _rank: null
  _isLocked: false
  _isFaceUp: false

  initWithConfAndColorAndRank: (conf, color, rank) ->
    return false unless @initWithTexture cc.textureNull(), 1

    @_color = color
    @_rank = rank

    @setConf conf

    true

  isNextToCardPlay: (cardPlay) ->

  setConf: (conf) ->

  getColor: -> @_color
  getRank: -> @_rank
  getIsLocked: -> @_isLocked
  setIsLocked: (@_isLocked) -> @
  getIsFaceUp: -> @_isFaceUp
  setIsFaceUp: (@_isFaceUp, force) -> @
)

cpz.CardPlay.createWithConfAndColorAndRank = (conf, color, rank) ->
  obj = new cpz.CardPlay()
  return obj if obj and obj.initWithConfAndColorAndRank(conf, color, rank)
  null

cpz.CardPlay.matchColor = (color) ->
cpz.CardPlay.matchColor = (color) ->
cpz.CardPlay.matchRank = (rank) ->
cpz.CardPlay.matchRank = (rank) ->
