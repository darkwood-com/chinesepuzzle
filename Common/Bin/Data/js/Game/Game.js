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
    var cSwitch, card, color, conf, coord, helloLabel, i, initBoard, j, k, l, move, rank, size, _i, _j, _k, _l, _len, _len1, _len2, _len3, _m, _n, _o, _p, _q, _r, _ref, _ref1, _ref2, _ref3;
    if (!this.init()) {
      return false;
    }
    this._gs = gs;
    this._gl = new cpz.GameLayout();
    this._gc = new cpz.GameControlNode();
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
    size = cc.Director.getInstance().getWinSize();
    helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38);
    helloLabel.setPosition(cc.p(size.width / 2, size.height - 40));
    this.addChild(helloLabel, 5);
    return true;
  },
  newGame: function() {},
  retryGame: function() {},
  draw: function() {},
  step: function(dt) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  isBusy: function() {},
  getCard: function(coord) {},
  checkMoveCoord: function(move) {},
  checkMoveCard: function(from, to) {},
  makeMoveCoord: function(move) {},
  makeMoveCard: function(from, to) {},
  undoMove: function() {},
  lockLine: function(i) {},
  registerWithTouchDispatcher: function() {},
  tapDownAt: function(location) {},
  tapMoveAt: function(location) {},
  tapUpAt: function(location) {},
  ccTouchBegan: function(touch, event) {},
  ccTouchMoved: function(touch, event) {},
  ccTouchEnded: function(touch, event) {},
  ccTouchCancelled: function(touch, event) {},
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
