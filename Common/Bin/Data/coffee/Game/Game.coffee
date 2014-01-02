###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.CheckMove =
  From: 0
  To: 1
  ToBefore: 2
  Ko: 3
  Ok: 4

cpz.Game = cc.Layer.extend(
  _deck: [] #deck cards
  _boardCards: [] #board cards
  _board: {} #board game that reference to the deck cards

  _gs: null
  _gl: null
  _gc: null

  #input touches/mouse
  _lastTouchLocation: null
  _dragCard: null
  _dragCardCoord: null
  _touchLastCard: null #visible hint last touched card, for semi-auto move
  _hintCard: null #card play hint on over card board
  _switchBoardCard: null #board card used for switch

  _makeMoveEnd: ->
  _makeMoveSound: ->
  _makeMoveUndoSound: ->
  _hintMove: ->

  ctor: ->
    @_super()

    for i in [0..7]
      @_board[i] = {}
      for j in [0..13]
        @_board[i][j] = null

  initWithGameScene: (gs) ->
    return false unless @init()

    @_gs = gs
    @_gl = new cpz.GameLayout()
    #@_gc = new cpz.GameControlChipmunk()
    @_gc = new cpz.GameControlNode()
    @setTouchEnabled true

    #init cards
    conf = @_gs.getConf()

    #for l in [0..7]
      #card = cpz.CardBoard.createWithConf conf
      #@addChild card, cpz.GameZOrder.Card
      #@_gc.addNode card
      #@_boardCards.push card

      #coord = cpz.gc l, 0
      #@_board[coord.i][coord.j] = card
      #card.setPosition @_gl.getPositionInBoardPoint(coord)

    #@_gl.layout()

    size = cc.Director.getInstance().getWinSize()
    helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38)
    helloLabel.setPosition cc.p(size.width / 2, size.height - 40)
    @addChild helloLabel, 5
    true

  newGame: ->
  retryGame: ->
  draw: ->
  step: (dt) ->
  layout: (anim = true) ->

  isBusy: ->
  getCard: (coord) ->
  checkMoveCoord: (move) ->
  checkMoveCard: (from, to) ->
  makeMoveCoord: (move) ->
  makeMoveCard: (from, to) ->
  undoMove: ->
  lockLine: (i) ->

  #input touches/mouse
  registerWithTouchDispatcher: ->

  tapDownAt: (location) ->
  tapMoveAt: (location) ->
  tapUpAt: (location) ->
  ccTouchBegan: (touch, event) ->
  ccTouchMoved: (touch, event) ->
  ccTouchEnded: (touch, event) ->
  ccTouchCancelled: (touch, event) ->

  getGameScene: -> @_gs
  getLayout: -> @_gl
  getControl: -> @_gc
)

cpz.Game.create = (gs) ->
  obj = new cpz.Game()
  return obj if obj and obj.initWithGameScene(gs)
  null
