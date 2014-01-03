/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GameConfigCommon = cc.Class.extend({
  _resolution: '',
  _theme: '',
  _isSoundOn: false,
  _moves: [],
  _initBoard: null,
  ctor: function() {
    return this._initBoard = new cc.Dictionary();
  },
  init: function() {},
  defaultResolution: function() {},
  getRootPath: function(file) {},
  getResolutionPath: function(file) {},
  getUiPath: function(file) {},
  getThemePath: function(file) {},
  getFontPath: function(file) {},
  getNodeUiPath: function(file, sprite) {},
  getNodeThemePath: function(file, sprite) {},
  getResolutionSize: function() {},
  getResolution: function() {
    return this._resolution;
  },
  setResolution: function(_resolution) {
    this._resolution = _resolution;
    return this;
  },
  getTheme: function() {
    return this._theme;
  },
  setTheme: function(_theme) {
    this._theme = _theme;
    return this;
  },
  getIsSoundOn: function() {
    return this._isSoundOn;
  },
  setIsSoundOn: function(_isSoundOn) {
    this._isSoundOn = _isSoundOn;
    return this;
  },
  getMoves: function() {
    return this._moves;
  },
  getInitBoard: function() {
    return this._initBoard;
  },
  encode: function() {},
  decode: function(data) {},
  save: function() {},
  load: function() {}
});

cpz.GameConfigCommon.XML_FILE_NAME = 'chinesePuzzleConf.plist';
