###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.Card = cc.Node.extend(
  _batchNode: null

  initWithTexture: (tex, capacity) ->
    @_batchNode = cc.SpriteBatchNode.createWithTexture tex, capacity
    return false unless @_batchNode

    @addChild @_batchNode

    true

  setSpriteBatchNode: (node) ->
    cc.copySpriteBatchNode(node, @_batchNode)

    @setContentSize(node.getContentSize())
)
