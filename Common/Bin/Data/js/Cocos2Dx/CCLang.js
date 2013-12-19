/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cc.CCLang = cc.Class.extend({
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
    var dict, filePath, fileUtils, fullPath, key, value;
    fileUtils = cc.FileUtils.getInstance();
    filePath = cpz.CommonPath + fileName;
    switch (this._lang) {
      case cc.LANGUAGE_FRENCH:
        filePath += '-fr';
        break;
      case cc.LANGUAGE_GERMAN:
        filePath += '-de';
        break;
      case cc.LANGUAGE_ENGLISH:
        filePath += '-en';
        break;
      default:
        filePath += '-en';
    }
    fullPath = fileUtils.fullPathForFilename(filePath + '.plist');
    dict = fileUtils.getDataFromPlistFile(fullPath);
    for (key in dict) {
      value = dict[key];
      if (value) {
        this.set(key, value);
      }
    }
    return this;
  }
});

cc.CCLang.s_sharedLang = null;

cc.CCLang.getInstance = function() {
  if (!this.s_sharedLang) {
    this.s_sharedLang = new cc.CCLang();
  }
  return this.s_sharedLang;
};
