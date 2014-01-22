/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GridCoord = cc.Class.extend({
  i: 0,
  j: 0,
  ctor: function() {}
});

cpz.gc = function(i, j) {
  var coord;
  coord = new cpz.GridCoord();
  coord.i = i;
  coord.j = j;
  return coord;
};

cpz.MoveCoord = cc.Class.extend({
  from: null,
  to: null,
  ctor: function() {}
});

cpz.mv = function(from, to) {
  var coord;
  coord = new cpz.MoveCoord();
  coord.from = from;
  coord.to = to;
  return coord;
};
