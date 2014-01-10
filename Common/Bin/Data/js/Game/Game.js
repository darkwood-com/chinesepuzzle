/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.CheckMove = {
  From: 0,
  To: 1,
  ToBefore: 2,
  Ko: 3,
  Ok: 4
};

cpz.Game = cc.Layer.extend({
  _deck: [],
  _boardCards: [],
  _board: {},
  _gs: null,
  _gl: null,
  _gc: null,
  _lastTouchLocation: null,
  _dragCard: null,
  _dragCardCoord: null,
  _touchLastCard: null,
  _hintCard: null,
  _switchBoardCard: null,
  _makeMoveEnd: function() {},
  _makeMoveSound: function() {},
  _makeMoveUndoSound: function() {},
  _hintMove: function() {},
  ctor: function() {
    var i, j, _i, _results;
    this._super();
    _results = [];
    for (i = _i = 0; _i <= 7; i = ++_i) {
      this._board[i] = {};
      _results.push((function() {
        var _j, _results1;
        _results1 = [];
        for (j = _j = 0; _j <= 13; j = ++_j) {
          _results1.push(this._board[i][j] = null);
        }
        return _results1;
      }).call(this));
    }
    return _results;
  },
  initWithGameScene: function(gs) {
    var cSwitch, card, color, conf, coord, i, initBoard, j, k, l, move, rank, _i, _j, _k, _l, _len, _len1, _len2, _len3, _m, _n, _o, _p, _q, _r, _ref, _ref1, _ref2, _ref3;
    if (!this.init()) {
      return false;
    }
    this._gs = gs;
    this._gl = new cpz.GameLayout(this);
    this._gc = new cpz.GameControlNode();
    this.setTouchMode(cc.TOUCH_ONE_BY_ONE);
    this.setTouchEnabled(true);
    conf = this._gs.getConf();
    for (l = _i = 0; _i <= 7; l = ++_i) {
      card = cpz.CardBoard.createWithConf(conf);
      this.addChild(card, cpz.GameZOrder.Card);
      this._gc.addNode(card);
      this._boardCards.push(card);
      coord = cpz.gc(l, 0);
      this._board[coord.i][coord.j] = card;
      card.setPosition(this._gl.getPositionInBoardPoint(coord));
    }
    this._gl.layout();
    initBoard = this._gs.getConf().getInitBoard();
    if (initBoard.count() === 0) {
      for (k = _j = 1; _j <= 2; k = ++_j) {
        _ref = cc.ObjectValues(cpz.CardPlayColor);
        for (_k = 0, _len = _ref.length; _k < _len; _k++) {
          color = _ref[_k];
          _ref1 = cc.ObjectValues(cpz.CardPlayRank);
          for (_l = 0, _len1 = _ref1.length; _l < _len1; _l++) {
            rank = _ref1[_l];
            card = cpz.CardPlay.createWithConfAndColorAndRank(conf, color, rank);
            this.addChild(card, cpz.GameZOrder.Card);
            this._gc.addNode(card);
            this._deck.push(card);
          }
        }
      }
      this._deck = cc.ArrayShuffle(this._deck);
      k = 0;
      for (i = _m = 0; _m <= 7; i = ++_m) {
        for (j = _n = 1; _n <= 13; j = ++_n) {
          card = this._deck[k];
          card.setIsLocked(false);
          coord = cpz.gc(i, j);
          this._board[i][j] = card;
          card.setPosition(this._gl.getPositionInBoardPoint(coord));
          initBoard.removeObject(coord);
          initBoard.setObject(card, coord);
          k++;
        }
      }
    } else {
      _ref2 = initBoard.allKeys();
      for (_o = 0, _len2 = _ref2.length; _o < _len2; _o++) {
        coord = _ref2[_o];
        card = initBoard.object(coord);
        this.addChild(card, cpz.GameZOrder.Card);
        this._gc.addNode(card);
        this._deck.push(card);
        card.setIsLocked(false);
        this._board[coord.i][coord.j] = card;
      }
      _ref3 = this._gs.getConf().getMoves();
      for (_p = 0, _len3 = _ref3.length; _p < _len3; _p++) {
        move = _ref3[_p];
        cSwitch = this.getCard(move.to);
        this._board[move.to.i][move.to.j] = this._board[move.from.i][move.from.j];
        this._board[move.from.i][move.from.j] = cSwitch;
      }
      for (i = _q = 0; _q <= 7; i = ++_q) {
        for (j = _r = 1; _r <= 13; j = ++_r) {
          coord = cpz.gc(i, j);
          card = this.getCard(coord);
          if (card) {
            card.setPosition(this._gl.getPositionInBoardPoint(coord));
            card.setRotation(1.0);
          }
        }
      }
    }
    this.layout();
    this.schedule(this.step);
    return true;
  },
  newGame: function() {
    var card, coord, i, j, k, l, _i, _j;
    this._deck = cc.ArrayShuffle(this._deck);
    k = 0;
    l = 0;
    for (i = _i = 0; _i <= 7; i = ++_i) {
      for (j = _j = 0; _j <= 13; j = ++_j) {
        coord = cpz.gc(i, j);
        if (j === 0) {
          card = this._boardCards[l];
          this._board[i][j] = card;
          card.setPosition(this._gl.getPositionInBoardPoint(coord));
          l++;
        } else {
          card = this._deck[k];
          card.setIsLocked(false);
          this._board[i][j] = card;
          this._gs.getConf().getInitBoard().removeObject(coord);
          this._gs.getConf().getInitBoard().setObject(card, coord);
          k++;
        }
      }
    }
    cc.ArrayClear(this._gs.getConf().getMoves());
    this.layout();
    return this._gs.getConf().save();
  },
  retryGame: function() {
    var card, coord, i, initBoard, _i, _j, _len, _ref;
    for (i = _i = 0; _i <= 7; i = ++_i) {
      this._board[i][0] = this._boardCards[i];
    }
    initBoard = this._gs.getConf().getInitBoard();
    _ref = initBoard.allKeys();
    for (_j = 0, _len = _ref.length; _j < _len; _j++) {
      coord = _ref[_j];
      card = initBoard.object(coord);
      this._board[coord.i][coord.j] = card;
      card.setIsLocked(false);
    }
    this.layout();
    return this._gs.getConf().save();
  },
  draw: function() {
    return this._super();
  },
  step: function(dt) {
    return this._gc.step(dt);
  },
  layout: function(anim) {
    var actions, card, conf, coord, coordPos, i, j, _i, _j, _results;
    if (anim == null) {
      anim = true;
    }
    this._gl.layout(anim);
    conf = this._gs.getConf();
    if (!this._touchLastCard) {
      this._touchLastCard = new cpz.Card();
      this._touchLastCard.initWithTexture(cc.textureNull(), 4);
      this._touchLastCard.setVisible(false);
      this.addChild(this._touchLastCard, cpz.GameZOrder.HintCard);
    }
    conf.getNodeThemePath('cardtouched', this._touchLastCard);
    if (!this._switchBoardCard) {
      this._switchBoardCard = new cpz.CardBoard();
      this._switchBoardCard.initWithTexture(cc.textureNull(), 4);
      this._switchBoardCard.setVisible(false);
      this.addChild(this._switchBoardCard, cpz.GameZOrder.Board);
    }
    this._switchBoardCard.setConf(conf);
    _results = [];
    for (i = _i = 0; _i <= 7; i = ++_i) {
      for (j = _j = 0; _j <= 13; j = ++_j) {
        coord = cpz.gc(i, j);
        card = this.getCard(coord);
        if (card) {
          card.setConf(conf);
          if (card instanceof cpz.CardBoard) {
            card.setPosition(this._gl.getPositionInBoardPoint(coord));
          } else if (card instanceof cpz.CardPlay) {
            coordPos = this._gl.getPositionInBoardPoint(coord);
            if (false) {
              actions = [];
              actions.push(cc.DelayTime.create(0.05 * (7 - coord.i + coord.j - 1)));
              if (!cc.pointEqualToPoint(card.getPosition(), coordPos)) {
                actions.push(cc.MoveTo.create(1.0, coordPos));
              }
              if (!card.getIsFaceUp()) {
                actions.push(cc.OrbitCamera.create(0.1, 1, 0, 0, 90, 0, 0));
                actions.push(cc.CallFunc.create(function() {
                  return this.setIsFaceUp(true);
                }, card));
                actions.push(cc.OrbitCamera.create(0.1, 1, 0, 270, 90, 0, 0));
              }
              card.runAction(cc.Sequence.create(actions));
            } else {
              card.setPosition(coordPos);
              card.setIsFaceUp(true);
            }
          }
        }
      }
      _results.push(this.lockLine(i));
    }
    return _results;
  },
  isBusy: function() {
    var i, j, _i, _j;
    for (i = _i = 0; _i <= 7; i = ++_i) {
      for (j = _j = 0; _j <= 13; j = ++_j) {
        if (this._board[i][j] && this._board[i][j].getNumberOfRunningActions()) {
          return true;
        }
      }
    }
    return false;
  },
  getCard: function(coord) {
    if (0 <= coord.i && coord.i < 8 && 0 <= coord.j && coord.j < 14) {
      return this._board[coord.i][coord.j];
    } else {
      return null;
    }
  },
  checkMoveCoord: function(move) {},
  checkMoveCard: function(from, to) {},
  makeMoveCoord: function(move) {},
  makeMoveCard: function(from, to) {},
  undoMove: function() {},
  lockLine: function(i) {},
  tapDownAt: function(location) {
    var dragCardPos, tapCard;
    if (this._gl.tapDownAt(location)) {
      return;
    }
    if (!this._dragCard && !this.isBusy()) {
      tapCard = this._gc.checkPoint(location);
      if (tapCard instanceof cpz.CardBoard && this._touchLastCard.getIsVisible() && this.checkMoveCard(this._touchLastCard, tapCard) === cpz.CheckMove.Ok) {
        this._switchBoardCard.setPosition(this._touchLastCard.getPosition());
        this._switchBoardCard.setVisible(true);
        this.makeMoveCard(this._touchLastCard, tapCard);
      }
      if (tapCard instanceof cpz.CardPlay && !tapCard.getIsLocked()) {
        this._dragCardCoord = this._gl.getPositionInGridCoord(tapCard.getPosition());
        this._dragCard = tapCard;
        dragCardPos = this._gl.getPositionInBoardPoint(this._dragCardCoord);
        this._switchBoardCard.setPosition(dragCardPos);
        this._switchBoardCard.setVisible(true);
        this._touchLastCard.setPosition(dragCardPos);
        this.reorderChild(this._dragCard, cpz.GameZOrder.MoveCard);
      }
      this._touchLastCard.setVisible(false);
    }
    this._hintMove();
    return this._lastTouchLocation = location;
  },
  tapMoveAt: function(location) {
    var movePos;
    if (this._gl.tapMoveAt(location)) {
      return;
    }
    this._touchLastCard.setVisible(false);
    movePos = cc.pAdd(location, cc.pNeg(this._lastTouchLocation));
    if (this._dragCard) {
      this._dragCard.setPosition(cc.pAdd(this._dragCard.getPosition(), movePos));
    }
    this._hintMove();
    return this._lastTouchLocation = location;
  },
  tapUpAt: function(location) {
    var cToCard, check, coord, move;
    if (this._gl.tapUpAt(location)) {
      return;
    }
    if (this._dragCard) {
      cToCard = this._gc.checkRectNode(this._dragCard, cpz.Game.filterCardBoard);
      if (!cToCard) {
        cToCard = this._dragCard;
      }
      coord = this._gl.getPositionInGridCoord(cToCard.getPosition());
      move = cpz.mv(this._dragCardCoord, coord);
      check = this.makeMoveCoord(move);
      if (check !== cpz.CheckMove.Ok && cc.pointEqualToPoint(this._dragCard.getPosition(), this._touchLastCard.getPosition())) {
        this._touchLastCard.setVisible(true);
      }
      this._dragCard = null;
    }
    return this._lastTouchLocation = location;
  },
  onTouchBegan: function(touch, event) {
    var location;
    location = touch.getLocation();
    location = cc.Director.getInstance().convertToGL(location);
    this.tapDownAt(location);
    return true;
  },
  onTouchMoved: function(touch, event) {
    var location;
    location = touch.getLocation();
    location = cc.Director.getInstance().convertToGL(location);
    return this.tapMoveAt(location);
  },
  onTouchEnded: function(touch, event) {
    var location;
    location = touch.getLocation();
    location = cc.Director.getInstance().convertToGL(location);
    return this.tapUpAt(location);
  },
  onTouchCancelled: function(touch, event) {
    var location;
    location = touch.getLocation();
    location = cc.Director.getInstance().convertToGL(location);
    return this.tapUpAt(location);
  },
  getGameScene: function() {
    return this._gs;
  },
  getLayout: function() {
    return this._gl;
  },
  getControl: function() {
    return this._gc;
  }
});

cpz.Game.create = function(gs) {
  var obj;
  obj = new cpz.Game();
  if (obj && obj.initWithGameScene(gs)) {
    return obj;
  }
  return null;
};

cpz.Game.filterCardBoard = function(node) {
  return node instanceof cpz.CardBoard;
};
