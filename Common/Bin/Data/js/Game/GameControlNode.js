/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.GameControlNode = cpz.GameControl.extend({
  _nodes: [],
  step: function(dt) {},
  draw: function() {},
  addNode: function(node) {
    if (this._nodes.indexOf(node) === -1) {
      return this._nodes.push(node);
    }
  },
  removeNode: function(node) {
    var i, _i, _ref, _results;
    if (this._nodes.indexOf(node) > -1) {
      _results = [];
      for (i = _i = 0, _ref = this._nodes.length; 0 <= _ref ? _i <= _ref : _i >= _ref; i = 0 <= _ref ? ++_i : --_i) {
        if (this._nodes[i] === node) {
          _results.push(this._nodes.splice(i, 1));
        } else {
          _results.push(void 0);
        }
      }
      return _results;
    }
  },
  updateNode: function(node) {},
  checkPoint: function(point) {
    var n, rectNode, _i, _len, _ref;
    _ref = this._nodes;
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      n = _ref[_i];
      rectNode = n.getBoundingBox();
      rectNode._origin = n.convertToWorldSpace(cc.PointZero());
      if (cc.rectContainsPoint(rectNode, point)) {
        return n;
      }
    }
    return null;
  },
  checkPointNode: function(node) {
    var n, point, rectNode, _i, _len, _ref;
    _ref = this._nodes;
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      n = _ref[_i];
      if (n === node) {
        continue;
      }
      point = node.getPosition();
      rectNode = n.getBoundingBox();
      if (cc.rectContainsPoint(rectNode, point)) {
        return node;
      }
    }
    return null;
  },
  checkRect: function(rect, filter) {
    var dist, minDist, n, nodeRes, rectNode, vect, _i, _len, _ref;
    nodeRes = null;
    minDist = -1;
    _ref = this._nodes;
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      n = _ref[_i];
      if (!filter(n)) {
        continue;
      }
      rectNode = n.getBoundingBox();
      rectNode._origin = n.convertToWorldSpace(cc.PointZero());
      if (cc.rectIntersectsRect(rectNode, rect)) {
        vect = cc.pAdd(rect._origin, cc.pNeg(rectNode._origin));
        dist = vect.x * vect.x + vect.y * vect.y;
        if (minDist === -1 || dist < minDist) {
          minDist = dist;
          nodeRes = n;
        }
      }
    }
    return nodeRes;
  },
  checkRectNode: function(node, filter) {
    var dist, minDist, n, nodeRes, rect, rectNode, vect, _i, _len, _ref;
    nodeRes = null;
    minDist = -1;
    _ref = this._nodes;
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      n = _ref[_i];
      if (!filter(n)) {
        continue;
      }
      rect = node.getBoundingBox();
      rectNode = n.getBoundingBox();
      if (cc.rectIntersectsRect(rectNode, rect)) {
        vect = cc.pAdd(rect._origin, cc.pNeg(rectNode._origin));
        dist = vect.x * vect.x + vect.y * vect.y;
        if (minDist === -1 || dist < minDist) {
          minDist = dist;
          nodeRes = n;
        }
      }
    }
    return nodeRes;
  }
});
