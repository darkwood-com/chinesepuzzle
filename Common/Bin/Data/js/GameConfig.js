/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.XML_FILE_NAME = "chinesepuzzle.data";

cpz.GameConfigCommon = cc.Class.extend({
  _getNodePath: function(mode, file, sprite) {
    var box, cardBGSprite, color, colors, k, node, nodePath, nodeSize, path, plistPath, rank, ranks, s, spriteFrameCache, sprites, texturePath, zone, zoneAnchor, zonePosition, zoneSprite, _i, _j, _k, _len, _len1, _len2;
    path = cpz.CommonPath + this._resolution + '/' + (mode === 'theme' ? 'themes/' + this._theme : 'ui');
    plistPath = path + '.plist';
    texturePath = path + '.png';
    nodePath = path + ':' + file;
    node = cpz.GameConfigCommon._configPaths[nodePath];
    if (!node) {
      spriteFrameCache = cc.SpriteFrameCache.getInstance();
      spriteFrameCache.removeSpriteFramesFromFile(plistPath);
      spriteFrameCache.addSpriteFrames(plistPath);
      sprites = {};
      if (mode === 'ui') {
        sprites['menuMask'] = 'auto';
        sprites['menuContainer'] = 'auto';
        sprites['menuItemYes'] = 'auto';
        sprites['menuItemNo'] = 'auto';
        sprites['menuItemOk'] = 'auto';
        sprites['menuItemThemeClassic'] = 'auto';
        sprites['menuItemThemeChinese'] = 'auto';
        sprites['menuItemThemeCircle'] = 'auto';
        sprites['menuItemThemePolkadots'] = 'auto';
        sprites['menuItemThemeSeamless'] = 'auto';
        sprites['menuItemThemeSkullshearts'] = 'auto';
        sprites['menuItemThemeSplash'] = 'auto';
        sprites['menuItemThemeSpring'] = 'auto';
        sprites['menuItemThemeStripes'] = 'auto';
        sprites['menuItemThemeVivid'] = 'auto';
      } else if (mode === 'theme') {
        sprites['bg'] = 'auto';
        sprites['cardplaybg'] = 'auto';
        sprites['cardboardempty'] = 'auto';
        sprites['cardboardyes'] = 'auto';
        sprites['cardboardno'] = 'auto';
        sprites['cardtouched'] = 'auto';
        sprites['newBtn'] = 'auto';
        sprites['retryBtn'] = 'auto';
        sprites['hintBtn'] = 'auto';
        sprites['soundOnBtn'] = 'auto';
        sprites['soundOffBtn'] = 'auto';
        sprites['themeBtn'] = 'auto';
        sprites['undoBtn'] = 'auto';
        cardBGSprite = cc.Sprite.createWithSpriteFrameName('cardbg.png');
        box = cardBGSprite.getBoundingBox();
        colors = ['D', 'S', 'H', 'C'];
        ranks = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'];
        for (_i = 0, _len = colors.length; _i < _len; _i++) {
          color = colors[_i];
          for (_j = 0, _len1 = ranks.length; _j < _len1; _j++) {
            rank = ranks[_j];
            sprites['card_' + color + rank] = [
              {
                from: 'cardbg',
                to: [0, 0]
              }, {
                from: 'rank_' + color + rank,
                to: [box.width / 4, 3 * box.height / 4],
                anchor: [0.5, 0.5]
              }, {
                from: 'big_' + color,
                to: [2 * box.width / 4, box.height / 4],
                anchor: [0.5, 0.5]
              }, {
                from: 'small_' + color,
                to: [3 * box.width / 4, 3 * box.height / 4],
                anchor: [0.5, 0.5]
              }
            ];
          }
        }
      }
      for (k in sprites) {
        s = sprites[k];
        if (s === 'auto') {
          s = [
            {
              from: k,
              to: [0, 0]
            }
          ];
        }
        node = cc.SpriteBatchNode.create(texturePath);
        nodeSize = cc.SizeZero();
        for (_k = 0, _len2 = s.length; _k < _len2; _k++) {
          zone = s[_k];
          if (!zone['anchor']) {
            zone['anchor'] = [0, 0];
          }
          zonePosition = cc.p(zone['to'][0], zone['to'][1]);
          zoneAnchor = cc.p(zone['anchor'][0], zone['anchor'][1]);
          zoneSprite = cc.Sprite.createWithSpriteFrameName(zone['from'] + '.png');
          zoneSprite.setAnchorPoint(zoneAnchor);
          zoneSprite.setPosition(zonePosition);
          node.addChild(zoneSprite);
          box = zoneSprite.getBoundingBox();
          nodeSize.width = Math.max(box.x + box.width, nodeSize.width);
          nodeSize.height = Math.max(box.y + box.height, nodeSize.height);
        }
        node.setContentSize(nodeSize);
        cpz.GameConfigCommon._configPathsSet(path + ':' + k, node);
      }
      node = cpz.GameConfigCommon._configPaths[nodePath];
    }
    if (node) {
      return cc.copySpriteBatchNode(node, sprite);
    }
  },
  _resolution: '',
  _theme: '',
  _isSoundOn: false,
  _moves: [],
  _initBoard: null,
  ctor: function() {
    return this._initBoard = new cc.Dictionary();
  },
  init: function() {
    this._resolution = this.defaultResolution();
    this._theme = this.defaultTheme();
    this._isSoundOn = true;
    return true;
  },
  getNodeUiPath: function(file, sprite) {
    return this._getNodePath('ui', file, sprite);
  },
  getNodeThemePath: function(file, sprite) {
    return this._getNodePath('theme', file, sprite);
  },
  getResolutionSize: function() {
    var m;
    m = this._resolution.match(/([0-9]+)x([0-9]+)/);
    if (m) {
      return cc.size(m[1], m[2]);
    } else {
      return cc.sizeZero();
    }
  },
  defaultResolution: function() {
    return '480x320';
  },
  defaultTheme: function() {
    return 'chinese';
  },
  getResolution: function() {
    return this._resolution;
  },
  setResolution: function(_resolution) {
    this._resolution = _resolution;
    return this;
  },
  getTheme: function() {
    return this._theme;
  },
  setTheme: function(_theme) {
    this._theme = _theme;
    return this;
  },
  getIsSoundOn: function() {
    return this._isSoundOn;
  },
  setIsSoundOn: function(_isSoundOn) {
    this._isSoundOn = _isSoundOn;
    return this;
  },
  getMoves: function() {
    return this._moves;
  },
  clearMoves: function() {
    cc.ArrayClear(this._moves);
    return this;
  },
  pushMove: function(move) {
    this._moves.push(move);
    return this;
  },
  popMove: function() {
    return this._moves.pop();
  },
  getInitBoard: function() {
    return this._initBoard;
  },
  encode: function() {
    var card, coord, data, move, _i, _j, _len, _len1, _ref, _ref1;
    data = {
      resolution: this._resolution,
      theme: this._theme,
      isSoundOn: this._isSoundOn,
      moves: [],
      board: []
    };
    _ref = this._initBoard.allKeys();
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      coord = _ref[_i];
      card = this._initBoard.object(coord);
      data['board'].push({
        coord: coord.encode(),
        card: card
      });
    }
    _ref1 = this._moves;
    for (_j = 0, _len1 = _ref1.length; _j < _len1; _j++) {
      move = _ref1[_j];
      data['moves'].push(move.encode());
    }
    return data;
  },
  decode: function(data) {
    var board, card, coord, move, _i, _j, _len, _len1, _ref, _ref1;
    this.clearMoves();
    this._initBoard.removeAllObjects();
    this._resolution = data['resolution'];
    this._theme = data['theme'];
    this._isSoundOn = data['isSoundOn'];
    _ref = data['board'];
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      board = _ref[_i];
      card = board.card;
      coord = cpz.GridCoord.decode(board.coord);
      this._initBoard.setObject(card, coord);
    }
    _ref1 = data['moves'];
    for (_j = 0, _len1 = _ref1.length; _j < _len1; _j++) {
      move = _ref1[_j];
      this._moves.push(cpz.MoveCoord.decode(move));
    }
    return this;
  },
  save: function() {
    var data;
    data = this.encode();
    data = base64.encode(JSON.stringify(data));
    sys.localStorage.setItem(cpz.XML_FILE_NAME, data);
    return this;
  },
  load: function() {
    var data;
    data = sys.localStorage.getItem(cpz.XML_FILE_NAME);
    if (data) {
      data = JSON.parse(base64.decode(data));
      this.decode(data);
    }
    return this;
  },
  preload: function(selector, target) {
    var plistThemePath, plistUIPath, textureThemePath, textureUIPath;
    plistThemePath = cpz.CommonPath + this._resolution + '/themes/' + this._theme + '.plist';
    textureThemePath = cpz.CommonPath + this._resolution + '/themes/' + this._theme + '.png';
    plistUIPath = cpz.CommonPath + this._resolution + '/ui' + '.plist';
    textureUIPath = cpz.CommonPath + this._resolution + '/ui' + '.png';
    return cc.Loader.preload([
      {
        src: plistThemePath
      }, {
        src: textureThemePath
      }, {
        src: plistUIPath
      }, {
        src: textureUIPath
      }
    ], selector, target);
  }
});

cpz.GameConfigCommon._configPaths = {};

cpz.GameConfigCommon._configPathsSet = function(key, node) {
  if (cpz.GameConfigCommon._configPaths[key]) {
    cpz.GameConfigCommon._configPaths[key].release();
    cpz.GameConfigCommon._configPaths[key] = null;
  }
  cpz.GameConfigCommon._configPaths[key] = node;
  return node.retain();
};

cpz.GameConfigCommon.getRootPath = function(file) {
  return cpz.CommonPath + file;
};

cpz.GameConfigCommon.getResolutionPath = function(file, resolution) {
  return cpz.CommonPath + resolution + '/' + file;
};

cpz.GameConfigCommon.getUiPath = function(file, resolution) {
  return cpz.CommonPath + resolution + '/ui/' + file;
};

cpz.GameConfigCommon.getThemePath = function(file, resolution, theme) {
  return cpz.CommonPath + resolution + '/themes/' + theme + '/' + file;
};

cpz.GameConfigCommon.getFontPath = function(file) {
  return cpz.CommonPath + 'fonts/' + file;
};

cpz.GameConfigCommon.getResolutions = function() {
  return ['480x320', '960x640', '1024x768', '1280x800', '1280x1024', '1366x768', '1440x900', '1680x1050', '1920x1080', '1920x1200'];
};

cpz.GameConfigCommon.getThemes = function() {
  return ['chinese', 'circle', 'classic', 'polkadots', 'seamless', 'shullshearts', 'splash', 'spring', 'stripes', 'vivid'];
};
