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
    @_gl = new cpz.GameLayout(@)
    #@_gc = new cpz.GameControlChipmunk()
    @_gc = new cpz.GameControlNode()

    @setTouchMode cc.TOUCH_ONE_BY_ONE
    @setTouchEnabled true

    #init cards
    conf = @_gs.getConf()

    for l in [0..7]
      card = cpz.CardBoard.createWithConf conf
      @addChild card, cpz.GameZOrder.Card
      @_gc.addNode card
      @_boardCards.push card

      coord = cpz.gc l, 0
      @_board[coord.i][coord.j] = card
      card.setPosition @_gl.getPositionInBoardPoint(coord)

    @_gl.layout()
    initBoard = @_gs.getConf().getInitBoard()
    if initBoard.count() is 0
      for k in [1..2]
        for color in cc.ObjectValues(cpz.CardPlayColor)
          for rank in cc.ObjectValues(cpz.CardPlayRank)
            card = cpz.CardPlay.createWithConfAndColorAndRank conf, color, rank
            @addChild card, cpz.GameZOrder.Card
            @_gc.addNode card
            @_deck.push card

      @_deck = cc.ArrayShuffle @_deck

      k = 0
      for i in [0..7]
        for j in [1..13]
          card = @_deck[k]
          card.setIsLocked false

          coord = cpz.gc i, j
          @_board[i][j] = card
          card.setPosition @_gl.getPositionInBoardPoint(coord)

          initBoard.removeObject coord
          initBoard.setObject card, coord

          k++
    else
      for coord in initBoard.allKeys()
        card = initBoard.object(coord)
        @addChild card, cpz.GameZOrder.Card
        @_gc.addNode card
        @_deck.push card

        card.setIsLocked false
        @_board[coord.i][coord.j] = card

      for move in @_gs.getConf().getMoves()
        cSwitch = @getCard move.to
        @_board[move.to.i][move.to.j] = @_board[move.from.i][move.from.j]
        @_board[move.from.i][move.from.j] = cSwitch

      for i in [0..7]
        for j in [1..13]
          coord = cpz.gc i, j

          card = @getCard coord
          if card
            card.setPosition @_gl.getPositionInBoardPoint(coord)
            card.setRotation 1.0

    @layout()
    @schedule(@step)

    true

  newGame: ->
    @_deck = cc.ArrayShuffle @_deck

    k = 0
    l = 0
    for i in [0..7]
      for j in [0..13]
        coord = cpz.gc i, j

        if j is 0
          card = @_boardCards[l]

          @_board[i][j] = card

          card.setPosition @_gl.getPositionInBoardPoint(coord)

          l++
        else
          card = @_deck[k]
          card.setIsLocked false

          @_board[i][j] = card

          @_gs.getConf().getInitBoard().removeObject coord
          @_gs.getConf().getInitBoard().setObject card, coord

          k++
    cc.ArrayClear(@_gs.getConf().getMoves())

    @layout()

    @_gs.getConf().save() #save conf state

  retryGame: ->
    for i in [0..7]
      @_board[i][0] = @_boardCards[i]

    initBoard = @_gs.getConf().getInitBoard()
    for coord in initBoard.allKeys()
      card = initBoard.object(coord)

      @_board[coord.i][coord.j] = card
      card.setIsLocked false

    @layout()

    @_gs.getConf().save() #save conf state

  draw: ->
    @_super()

    #debug game control draw
    #@_gc.draw()

  step: (dt) ->
    #update game step
    @_gc.step(dt)

  layout: (anim = true) ->
    @_gl.layout anim

    conf = @_gs.getConf()

    unless @_touchLastCard
      @_touchLastCard = new cpz.Card()
      @_touchLastCard.initWithTexture cc.textureNull(), 4
      @_touchLastCard.setVisible false
      @addChild @_touchLastCard, cpz.GameZOrder.HintCard
    conf.getNodeThemePath 'cardtouched', @_touchLastCard

    unless @_switchBoardCard
      @_switchBoardCard = new cpz.CardBoard()
      @_switchBoardCard.initWithTexture cc.textureNull(), 4
      @_switchBoardCard.setVisible false
      @addChild @_switchBoardCard, cpz.GameZOrder.Board
    @_switchBoardCard.setConf conf

    for i in [0..7]
      for j in [0..13]
        coord = cpz.gc i, j

        card = @getCard coord
        if card
          card.setConf conf

          if card instanceof cpz.CardBoard
            card.setPosition @_gl.getPositionInBoardPoint coord
          else if card instanceof cpz.CardPlay
            coordPos = @_gl.getPositionInBoardPoint coord
            if false #anim
              #card animation
              actions = []
              actions.push cc.DelayTime.create(0.05 * (7 - coord.i + coord.j - 1))
              unless cc.pointEqualToPoint(card.getPosition(), coordPos)
                actions.push cc.MoveTo.create(1.0, coordPos)
              unless card.getIsFaceUp()
                actions.push cc.OrbitCamera.create(0.1, 1, 0, 0, 90, 0, 0)
                actions.push cc.CallFunc.create(->
                  @setIsFaceUp true
                , card)
                actions.push cc.OrbitCamera.create(0.1, 1, 0, 270, 90, 0, 0)
              card.runAction cc.Sequence.create(actions)
            else
              card.setPosition coordPos
              card.setIsFaceUp true

      @lockLine i

  isBusy: ->
    for i in [0..7]
      for j in [0..13]
        if @_board[i][j] and @_board[i][j].getNumberOfRunningActions()
          return true
    false

  getCard: (coord) ->
    if 0 <= coord.i and coord.i < 8 and 0 <= coord.j and coord.j < 14 then @_board[coord.i][coord.j] else null

  checkMoveCoord: (move) ->
  checkMoveCard: (from, to) ->
  makeMoveCoord: (move) ->
  makeMoveCard: (from, to) ->
  undoMove: ->
  lockLine: (i) ->

  #input touches/mouse
  #registerWithTouchDispatcher: ->

  tapDownAt: (location) ->
    return if @_gl.tapDownAt(location)

    if not @_dragCard and not @isBusy()
      tapCard = @_gc.checkPoint(location)
      if tapCard instanceof cpz.CardBoard and @_touchLastCard.getIsVisible() and @checkMoveCard(@_touchLastCard, tapCard) is cpz.CheckMove.Ok
        @_switchBoardCard.setPosition @_touchLastCard.getPosition()
        @_switchBoardCard.setVisible true
        @makeMoveCard @_touchLastCard, tapCard

      if tapCard instanceof cpz.CardBoard and not tapCard.getIsLocked()
        @_dragCardCoord = @_gl.getPositionInGridCoord(tapCard.getPosition())
        @_dragCard = tapCard
        dragCardPos = @_gl.getPositionInBoardPoint(@_dragCardCoord)

        @_switchBoardCard.setPosition dragCardPos
        @_switchBoardCard.setVisible true
        @_touchLastCard.setPosition dragCardPos

        @reorderChild @_dragCard, cpz.GameZOrder.MoveCard

      @_touchLastCard.setVisible false

    @_hintMove()
    @_lastTouchLocation = location

  tapMoveAt: (location) ->
    return if @_gl.tapMoveAt(location)

    @_touchLastCard.setVisible false

    movePos = cc.pAdd location, cc.pNeg(@_lastTouchLocation)
    if(@_dragCard)
      @_dragCard.setPosition cc.pAdd(@_dragCard.getPosition(), movePos)

    @_hintMove()
    @_lastTouchLocation = location

  tapUpAt: (location) ->
    return if @_gl.tapUpAt(location)

    if(@_dragCard)
      #check drop
      cToCard = @_gc.checkRectNode @_dragCard, cpz.Game.filterCardBoard
      cToCard = @_dragCard unless cToCard
      coord = @_gl.getPositionInGridCoord cToCard.getPosition()
      move = cpz.mv dragCardCoord, coord
      check = @makeMoveCoord move
      if check isnt cpz.CheckMove.Ok && cc.pointEqualToPoint @_dragCard.getPosition(), @_touchLastCard.getPosition()
        @_touchLastCard.setVisible true

      @_dragCard = NULL

    @_lastTouchLocation = location

  onTouchBegan: (touch, event) ->
    location = touch.getLocation()
    location = cc.Director.getInstance().convertToGL(location)
    @tapDownAt(location)
    true

  onTouchMoved: (touch, event) ->
    location = touch.getLocation()
    location = cc.Director.getInstance().convertToGL(location)
    @tapMoveAt(location)

  onTouchEnded: (touch, event) ->
    location = touch.getLocation()
    location = cc.Director.getInstance().convertToGL(location)
    @tapUpAt(location)

  onTouchCancelled: (touch, event) ->
    location = touch.getLocation()
    location = cc.Director.getInstance().convertToGL(location)
    @tapUpAt(location)

  getGameScene: -> @_gs
  getLayout: -> @_gl
  getControl: -> @_gc
)

cpz.Game.create = (gs) ->
  obj = new cpz.Game()
  return obj if obj and obj.initWithGameScene(gs)
  null

cpz.Game.filterCardBoard = (node) ->
  return node instanceof cpz.CardBoard
