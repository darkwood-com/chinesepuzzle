###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.GridCoord = cc.Class.extend(
  i: 0
  j: 0

  ctor: ->
)

cpz.gc = (i, j) ->
  coord = new cpz.GridCoord()
  coord.i = i
  coord.j = j
  coord

cpz.MoveCoord = cc.Class.extend(
  from: null
  to: null

  ctor: ->
)

cpz.mv = (from, to) ->
  coord = new cpz.MoveCoord()
  coord.from = from
  coord.to = to
  coord