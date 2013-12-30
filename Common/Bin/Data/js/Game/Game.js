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
  _deck: null,
  _boardCards: null,
  _board: null,
  _gc: null,
  _gl: null,
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
    return this._super();
  },
  initWithGameScene: function(gs) {
    var helloLabel, size;
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
  ccTouchCancelled: function(touch, event) {}
});

cpz.Game.create = function(gs) {
  var layer;
  layer = new cpz.Game();
  if (layer && layer.initWithGameScene(gs)) {
    return layer;
  }
  return null;
};
