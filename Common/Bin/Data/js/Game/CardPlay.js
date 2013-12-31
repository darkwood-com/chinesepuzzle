/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.CardPlayColor = {
  Spade: 1,
  Club: 2,
  Heart: 3,
  Diamond: 4
};

cpz.CardPlayRank = {
  Ace: 1,
  Two: 2,
  Three: 3,
  Four: 4,
  Five: 5,
  Six: 6,
  Seven: 7,
  Eight: 8,
  Nine: 9,
  Ten: 10,
  Jack: 11,
  Queen: 12,
  King: 13
};

cpz.CardPlayFlipAction = cc.FiniteTimeAction.extend({
  _cardPlay: null,
  _isFaceUp: null,
  actionWithCardPlay: function(cardPlay) {},
  initWithCardPlay: function(cardPlay) {},
  update: function(time) {},
  copyWithZone: function(pZone) {}
});

cpz.CardPlay = cpz.Card.extend({
  _faceSprite: null,
  _backSprite: null,
  _color: null,
  _rank: null,
  _isLocked: null,
  _isFaceUp: null,
  cardBoardWithConfAndColorAndRank: function(conf, color, rank) {},
  initWithConfAndColorAndRank: function(conf, color, rank) {},
  isNextToCardPlay: function(cardPlay) {},
  setConf: function(conf) {},
  getColor: function() {
    return this._color;
  },
  getRank: function() {
    return this._rank;
  },
  getIsFaceUp: function() {
    return this._isFaceUp;
  },
  setIsFaceUp: function(_isFaceUp, force) {
    this._isFaceUp = _isFaceUp;
    return this;
  }
});

cpz.CardPlay.matchColor = function(color) {};

cpz.CardPlay.matchColor = function(color) {};

cpz.CardPlay.matchRank = function(rank) {};

cpz.CardPlay.matchRank = function(rank) {};
