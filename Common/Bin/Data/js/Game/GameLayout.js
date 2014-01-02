/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GameZOrder = {
  BG: 0,
  UI: 1,
  Board: 2,
  Card: 3,
  MoveCard: 4,
  HintCard: 5
};

cpz.GameLayout = cc.Class.extend({
  _layoutRes: function(key) {},
  _actionBtn: function(btn) {},
  _game: null,
  _activesBtn: [],
  _bg: null,
  _newBtn: null,
  _retryBtn: null,
  _hintBtn: null,
  _undoBtn: null,
  _soundBtn: null,
  _themeBtn: null,
  _gridCardSize: null,
  _gridSpaceSize: null,
  _gridPosition: null,
  ctor: function(game) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  tapDownAt: function(location) {},
  tapMoveAt: function(location) {},
  tapUpAt: function(location) {},
  getPositionInBoardPoint: function(coord) {},
  getPositionInGridCoord: function(point) {}
});
