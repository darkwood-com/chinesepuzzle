###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GameControlNode = cpz.GameControl.extend(
  _nodes: []

  step: (dt) ->
  draw: ->

  addNode: (node) ->
    if @_nodes.indexOf(node) is -1
      @_nodes.push node

  removeNode: (node) ->
    if (@_nodes.indexOf(node) > -1)
      for i in [0..@_nodes.length]
        if (@_nodes[i] == node)
          @_nodes.splice(i, 1)

  updateNode: (node) ->


  checkPoint: (point) ->
    for n in @_nodes
      rectNode = n.boundingBox()
      rectNode.origin = n.convertToWorldSpace(cc.PointZero())

      if cc.rectContainsPoint rectNode, point then return n

    null

  checkPointNode: (node) ->
    for n in @_nodes
      continue if n is node

      point = node.getPosition()
      rectNode = n.boundingBox()

      if cc.rectContainsPoint rectNode, point then return node

    null

  checkRect: (rect, filter) ->
    nodeRes = null
    minDist = -1

    for n in @_nodes
      continue unless filter(n)

      rectNode = n.boundingBox()
      rectNode.origin = n.convertToWorldSpace(cc.PointZero())

      if cc.rectIntersectsRect rectNode, rect
        vect = cc.pAdd(rect.origin, cc.pNeg(rectNode.origin))
        dist = vect.x * vect.x + vect.y * vect.y
        if minDist is -1 or dist < minDist
          minDist = dist
          nodeRes = n

    nodeRes

  checkRectNode: (node, filter) ->
    nodeRes = null
    minDist = -1

    for n in @_nodes
      continue unless filter(n)

      rect = node.boundingBox()
      rectNode = n.boundingBox()

      if cc.rectIntersectsRect rectNode, rect
        vect = cc.pAdd(rect.origin, cc.pNeg(rectNode.origin))
        dist = vect.x * vect.x + vect.y * vect.y
        if minDist is -1 or dist < minDist
          minDist = dist
          nodeRes = n

    nodeRes
)
