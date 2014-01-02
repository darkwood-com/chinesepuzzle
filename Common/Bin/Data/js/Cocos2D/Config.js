/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

if (!cc.SpriteBatchNode.extend) {
  cc.SpriteBatchNode.extend = cc.Class.extend;
}

cc.textureNull = function() {
  return new cc.Texture2D();
};
