/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.CardBoardState = {
  Empty: 1,
  Yes: 2,
  No: 3
};

cpz.CardBoard = cpz.Card.extend({
  _emptySprite: null,
  _yesSprite: null,
  _noSprite: null,
  _state: null,
  ctor: function() {
    this._super();
    return this._state = cpz.CardBoardState.Empty;
  },
  initWithConf: function(conf) {
    return true;
  },
  getState: function() {
    return this._state;
  },
  setState: function(state, force) {
    if (force == null) {
      force = false;
    }
    if (this._state !== state || force) {
      switch (state) {
        case 0:
          break;
      }
    }
  },
  setConf: function(conf) {}
});

cpz.CardBoard.createWithConf = function(conf) {
  var obj;
  obj = new cpz.CardBoard();
  if (obj && obj.initWithConf(conf)) {
    return obj;
  }
  return null;
};
