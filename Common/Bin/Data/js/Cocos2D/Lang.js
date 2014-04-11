/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cc.Lang = cc.Class.extend({
  _data: null,
  _lang: null,
  ctor: function() {
    return this._data = {};
  },
  getLang: function() {
    return this._lang;
  },
  setLang: function(lang) {
    return this._lang = lang;
  },
  get: function(key) {
    return this._data[key] || key;
  },
  set: function(key, value) {
    return this._data[key] = value;
  },
  addLang: function(fileName) {
    return this;
  }
});

cc.Lang.s_sharedLang = null;

cc.Lang.getInstance = function() {
  if (!this.s_sharedLang) {
    this.s_sharedLang = new cc.Lang();
  }
  return this.s_sharedLang;
};
