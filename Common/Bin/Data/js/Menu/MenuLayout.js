/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.MenuLayoutType = {
  None: 0,
  NewGame: 1,
  RetryGame: 2,
  Hint: 3,
  Theme: 4
};

cpz.MenuLayout = cc.Class.extend({
  _layoutRes: function(key) {},
  _menu: null,
  _themes: [],
  _selectTheme: function(themeNode) {},
  _bg: null,
  _mBox: null,
  _miTheme: null,
  _layoutLastFontFile: null,
  _type: null,
  ctor: function(game) {
    return this._super();
  },
  initWithType: function(type) {},
  layout: function(anim) {
    if (anim == null) {
      anim = true;
    }
  },
  getType: function() {
    return this._type;
  },
  setType: function(_type) {
    this._type = _type;
    return this;
  }
});
