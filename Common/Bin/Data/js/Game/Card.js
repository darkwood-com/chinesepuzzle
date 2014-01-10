/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.Card = cc.Node.extend({
  _batchNode: null,
  initWithTexture: function(tex, capacity) {
    this._batchNode = cc.SpriteBatchNode.createWithTexture(tex, capacity);
    if (!this._batchNode) {
      return false;
    }
    this.addChild(this._batchNode);
    return true;
  },
  setSpriteBatchNode: function(node) {
    cc.copySpriteBatchNode(node, this._batchNode);
    return this.setContentSize(node.getContentSize());
  }
});
