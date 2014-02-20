###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.XML_FILE_NAME = "chinesepuzzle.data"

cpz.GameConfig = cc.Class.extend(
  _getNodePath: (mode, file, sprite) ->
    path = cpz.CommonPath + @_resolution + '/' + (if mode is 'theme' then 'themes/' + @_theme else 'ui')
    plistPath = path + '.plist'
    texturePath = path + '.png'
    nodePath = path + ':' + file

    node = cpz.GameConfig._configPaths[nodePath]
    unless node
      spriteFrameCache = cc.SpriteFrameCache.getInstance()
      spriteFrameCache.removeSpriteFramesFromFile(plistPath)
      spriteFrameCache.addSpriteFrames(plistPath)

      sprites = {}
      if mode is 'ui'
        sprites['menuMask'] =                  'auto'
        sprites['menuContainer'] =             'auto'
        sprites['menuItemYes'] =               'auto'
        sprites['menuItemNo'] =                'auto'
        sprites['menuItemOk'] =                'auto'
        sprites['menuItemThemeClassic'] =      'auto'
        sprites['menuItemThemeChinese'] =      'auto'
        sprites['menuItemThemeCircle'] =       'auto'
        sprites['menuItemThemePolkadots'] =    'auto'
        sprites['menuItemThemeSeamless'] =     'auto'
        sprites['menuItemThemeSkullshearts'] = 'auto'
        sprites['menuItemThemeSplash'] =       'auto'
        sprites['menuItemThemeSpring'] =       'auto'
        sprites['menuItemThemeStripes'] =      'auto'
        sprites['menuItemThemeVivid'] =        'auto'
      else if mode is 'theme'
        sprites['bg'] =					               'auto'
        sprites['cardplaybg'] =			           'auto'
        sprites['cardboardempty'] =		         'auto'
        sprites['cardboardyes'] =  			       'auto'
        sprites['cardboardno'] =		  	       'auto'
        sprites['cardtouched'] =			         'auto'
        sprites['newBtn'] =				             'auto'
        sprites['retryBtn'] =				           'auto'
        sprites['hintBtn'] =				           'auto'
        sprites['soundOnBtn'] =			           'auto'
        sprites['soundOffBtn'] =  			       'auto'
        sprites['themeBtn'] =		  		         'auto'
        sprites['undoBtn'] =				           'auto'

        cardBGSprite = cc.Sprite.createWithSpriteFrameName 'cardbg.png'
        box = cardBGSprite.getBoundingBox()

        colors = ['D', 'S', 'H', 'C']
        ranks = ['A','2','3','4','5','6','7','8','9','10','J','Q','K']
        for color in colors
          for rank in ranks
            sprites['card_' + color + rank] = [
              from: 'cardbg'
              to: [0, 0]
            ,
              from: 'rank_' + color + rank
              to: [box.width / 4, 3 * box.height / 4]
              anchor: [0.5, 0.5]
            ,
              from: 'big_' + color
              to: [2 * box.width / 4, box.height / 4]
              anchor: [0.5, 0.5]
            ,
              from: 'small_' + color
              to: [3 * box.width / 4, 3 * box.height / 4]
              anchor: [0.5, 0.5]
            ]

      for k, s of sprites
        if s is'auto'
          s = [
            from: k
            to: [0, 0]
          ]

        node = cc.SpriteBatchNode.create texturePath

        nodeSize = cc.SizeZero()
        for zone in s
          unless zone['anchor']
            zone['anchor'] = [0, 0]

          zonePosition = cc.p(zone['to'][0], zone['to'][1])
          zoneAnchor = cc.p(zone['anchor'][0], zone['anchor'][1])

          zoneSprite = cc.Sprite.createWithSpriteFrameName(zone['from'] + '.png')
          zoneSprite.setAnchorPoint zoneAnchor
          zoneSprite.setPosition zonePosition
          node.addChild zoneSprite

          box = zoneSprite.getBoundingBox()
          nodeSize.width = Math.max box.x + box.width, nodeSize.width
          nodeSize.height = Math.max box.y + box.height, nodeSize.height

        node.setContentSize(nodeSize)

        cpz.GameConfig._configPathsSet(path + ':' + k, node)

      node = cpz.GameConfig._configPaths[nodePath]

    cc.copySpriteBatchNode(node, sprite) if node

  _resolution: ''
  _theme: ''
  _isCardLayout: false
  _isSoundOn: false
  _moves: []
  _initBoard: null

  ctor: ->
    @_initBoard = new cc.Dictionary()

  init: ->
    @_resolution = @defaultResolution()
    @_theme = @defaultTheme()
    @_isSoundOn = true

    true

  getNodeUiPath: (file, sprite) -> @_getNodePath 'ui', file, sprite
  getNodeThemePath: (file, sprite) -> @_getNodePath 'theme', file, sprite

  getResolutionSize: ->
    cpz.GameConfig.parseResolution @_resolution

  defaultResolution: -> '480x320'
  defaultTheme: -> 'chinese'

  getResolution: -> @_resolution
  setResolution: (@_resolution) -> @
  getTheme: -> @_theme
  setTheme: (@_theme) -> @
  getIsCardLayout: -> @_isCardLayout
  setIsCardLayout: (@_isCardLayout) -> @
  getIsSoundOn: -> @_isSoundOn
  setIsSoundOn: (@_isSoundOn) -> @
  getMoves: -> @_moves
  clearMoves: ->
    cc.ArrayClear(@_moves)
    @
  pushMove: (move) ->
    @_moves.push move
    @
  popMove: ->
    @_moves.pop()
  getInitBoard: -> @_initBoard

  encode: ->
    data =
      #resolution: @_resolution
      theme: @_theme
      isCardLayout: @_isCardLayout
      isSoundOn: @_isSoundOn
      moves: []
      board: []

    for coord in @_initBoard.allKeys()
      card = @_initBoard.object(coord)

      data['board'].push
        coord: coord.encode()
        card: card

    for move in @_moves
      data['moves'].push(move.encode())

    data

  decode: (data) ->
    @clearMoves()
    @_initBoard.removeAllObjects()

    #@_resolution = data['resolution']
    @_theme = data['theme']
    @_isCardLayout = data['isCardLayout']
    @_isSoundOn = data['isSoundOn']

    for board in data['board']
      card = board.card
      coord = cpz.GridCoord.decode(board.coord)
      @_initBoard.setObject card, coord

    for move in data['moves']
      @_moves.push(cpz.MoveCoord.decode(move))
    @

  save: ->
    data = @encode()
    data = base64.encode(JSON.stringify(data))
    sys.localStorage.setItem(cpz.XML_FILE_NAME, data);

    @
    
  load: ->
    data = sys.localStorage.getItem(cpz.XML_FILE_NAME);
    if data
      data = JSON.parse(base64.decode(data))
      @decode(data)

    @

  preload: (selector, target, resolution = null, theme = null) ->
    resolution = @_resolution unless resolution
    theme = @_theme unless theme

    plistThemePath = cpz.CommonPath + resolution + '/themes/' + theme  + '.plist'
    textureThemePath = cpz.CommonPath + resolution + '/themes/' + theme + '.png'
    plistUIPath = cpz.CommonPath + resolution + '/ui' + '.plist'
    textureUIPath = cpz.CommonPath + resolution + '/ui' + '.png'

    cc.Loader.preload [
      src: plistThemePath
    ,
      src: textureThemePath
    ,
      src: plistUIPath
    ,
      src: textureUIPath
    ], selector, target
)

cpz.GameConfig._configPaths = {};

cpz.GameConfig._configPathsSet = (key, node) ->
  if cpz.GameConfig._configPaths[key]
    cpz.GameConfig._configPaths[key].release()
    cpz.GameConfig._configPaths[key] = null
  cpz.GameConfig._configPaths[key] = node
  node.retain()

cpz.GameConfig.getRootPath = (file) -> cpz.CommonPath + file
cpz.GameConfig.getResolutionPath = (file, resolution) -> cpz.CommonPath + resolution + '/' + file
cpz.GameConfig.getUiPath = (file, resolution) -> cpz.CommonPath + resolution + '/ui/' + file
cpz.GameConfig.getThemePath = (file, resolution, theme) -> cpz.CommonPath + resolution + '/themes/' + theme + '/' + file
cpz.GameConfig.getFontPath = (file) -> cpz.CommonPath + 'fonts/' + file

cpz.GameConfig.parseResolution = (res) ->
  return cc.SizeZero() unless res
  m = res.match /([0-9]+)x([0-9]+)/
  if m then cc.size(parseInt(m[1]), parseInt(m[2])) else cc.SizeZero()

cpz.GameConfig.getResolutions = ->
  [
    '480x320',
    '960x640',
    '1024x768',
    '1280x800',
    '1280x1024',
    '1366x768',
    '1440x900',
    '1680x1050',
    '1920x1080',
    '1920x1200',
  ]

cpz.GameConfig.getThemes = ->
  [
    'chinese',
    'circle',
    'classic',
    'polkadots',
    'seamless',
    'shullshearts',
    'splash',
    'spring',
    'stripes',
    'vivid',
  ]