/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GridCoord = cc.Class.extend({
  i: 0,
  j: 0,
  ctor: function() {},
  encode: function() {
    return {
      i: this.i,
      j: this.j
    };
  },
  decode: function(data) {
    this.i = data['i'];
    return this.j = data['j'];
  }
});

cpz.GridCoord.decode = function(data) {
  var obj;
  obj = new cpz.GridCoord();
  if (obj && obj.decode(data)) {
    return obj;
  }
  return null;
};

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
  ctor: function() {},
  encode: function() {
    return {
      from: this._from.encode(),
      to: this._to.encode()
    };
  },
  decode: function(data) {
    this._from = cpz.GridCoord.decode(data['from']);
    return this._to = cpz.GridCoord.decode(data['to']);
  }
});

cpz.MoveCoord.decode = function(data) {
  var obj;
  obj = new cpz.MoveCoord();
  if (obj && obj.decode(data)) {
    return obj;
  }
  return null;
};

cpz.mv = function(from, to) {
  var coord;
  coord = new cpz.MoveCoord();
  coord.from = from;
  coord.to = to;
  return coord;
};
