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
  getState: function() {
    return this._state;
  },
  setState: function(_state, force) {
    this._state = _state;
  },
  setConf: function(conf) {}
});
