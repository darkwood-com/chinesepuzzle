/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.Background = cc.Layer.extend({
  _bgPattern: null,
  _gs: null,
  initWithGameScene: function(gs) {
    var texParams;
    if (!this._super()) {
      return false;
    }
    ccTexParams(texParams = {
      GL_LINEAR: GL_LINEAR,
      GL_LINEAR: GL_LINEAR,
      GL_REPEAT: GL_REPEAT,
      GL_REPEAT: GL_REPEAT
    });
    this._bgPattern = cc.Sprite.create(gs.getConf().getRootPath('bgPattern.png'));
    this._bgPattern.setAnchorPoint(cc.p(0, 0));
    this.addChild(this._bgPattern, cpz.GameSceneZOrder.BG);
    this._gs = gs;
    this.setContentSize(this._gs.getConf().getResolutionSize());
    return true;
  },
  setContentSize: function(size) {
    var rect;
    this._super(size);
    if (this._bgPattern) {
      rect = cc.rect(0, 0, size.width, size.height);
      return this._bgPattern.setTextureRect(rect);
    }
  }
});

cpz.Background.create = function(gs) {
  var layer;
  layer = new cpz.Background();
  if (layer && layer.initWithGameScene(gs)) {
    return layer;
  }
  return null;
};
