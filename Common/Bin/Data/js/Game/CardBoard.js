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
    if (!this.initWithTexture(cc.textureNull(), 1)) {
      return false;
    }
    this.setConf(conf);
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
        case cpz.CardBoardState.Yes:
          cc.copySpriteBatchNode(this._yesSprite, this._batchNode);
          break;
        case cpz.CardBoardState.No:
          cc.copySpriteBatchNode(this._noSprite, this._batchNode);
          break;
        default:
          cc.copySpriteBatchNode(this._emptySprite, this._batchNode);
      }
      return this._state = state;
    }
  },
  setConf: function(conf) {
    if (this._emptySprite === null) {
      this._emptySprite = cc.SpriteBatchNode.createWithTexture(cc.textureNull(), 1);
    }
    if (this._yesSprite === null) {
      this._yesSprite = cc.SpriteBatchNode.createWithTexture(cc.textureNull(), 1);
    }
    if (this._noSprite === null) {
      this._noSprite = cc.SpriteBatchNode.createWithTexture(cc.textureNull(), 1);
    }
    conf.getNodeThemePath('cardboardempty', this._emptySprite);
    conf.getNodeThemePath('cardboardyes', this._yesSprite);
    conf.getNodeThemePath('cardboardno', this._noSprite);
    return this.setState(this.getState, true);
  }
});

cpz.CardBoard.createWithConf = function(conf) {
  var obj;
  obj = new cpz.CardBoard();
  if (obj && obj.initWithConf(conf)) {
    return obj;
  }
  return null;
};
