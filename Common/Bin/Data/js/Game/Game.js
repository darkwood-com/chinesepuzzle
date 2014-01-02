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
    var card, conf, coord, helloLabel, l, size, _i;
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
