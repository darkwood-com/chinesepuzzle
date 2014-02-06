###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.XML_FILE_NAME = "chinesePuzzleConf.plist"

cpz.GameConfigCommon = cc.Class.extend(
  _getNodePath: (mode, file, sprite) ->
    path = cpz.CommonPath + @_resolution + '/' + (if mode is 'theme' then 'themes/' + @_theme else 'ui')
    plistPath = path + '.plist'
    texturePath = path + '.png'
    nodePath = path + ':' + file

    node = cpz.GameConfigCommon._configPaths[nodePath]
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

        cpz.GameConfigCommon._configPathsSet(path + ':' + k, node)

      node = cpz.GameConfigCommon._configPaths[nodePath]

    cc.copySpriteBatchNode(node, sprite) if node

  _resolution: ''
  _theme: ''
  _isSoundOn: false
  _moves: []
  _initBoard: null

  ctor: ->
    @_initBoard = new cc.Dictionary()

  init: ->
    @_resolution = @defaultResolution()
    @_theme = @defaultTheme()
    @_isSoundOn = false

    true

  getNodeUiPath: (file, sprite) -> @_getNodePath 'ui', file, sprite
  getNodeThemePath: (file, sprite) -> @_getNodePath 'theme', file, sprite

  getResolutionSize: ->
    m = @_resolution.match /([0-9]+)x([0-9]+)/
    if m then cc.size(m[1], m[2]) else cc.sizeZero()

  defaultResolution: -> '480x320'
  defaultTheme: -> 'chinese'

  getResolution: -> @_resolution
  setResolution: (@_resolution) -> @
  getTheme: -> @_theme
  setTheme: (@_theme) -> @
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
      resolution: @_resolution
      theme: @_theme
      isSoundOn: @_isSoundOn
      moves: []
      board: []

    for move in @_moves
      data['moves'].push(move.encode())

    for coord in @_initBoard.allKeys()
      card = @_initBoard.object(coord)

      data['board'].push
        coord: coord.encode()
        card:
          color: card.getColor()
          rank: card.getRank()

    data

  decode: (data) ->
    @clearMoves()
    @_initBoard.removeAllObjects()

    @_resolution = data['resolution']
    @_theme = data['theme']
    @_isSoundOn = data['isSoundOn']

    for move in data['moves']
      @_moves.push(cpz.MoveCoord.decode(move))

    for board in data['board']
      card = cpz.CardPlay.createWithConfAndColorAndRank(@, board.card.color, board.card.rank)
      coord = cpz.GridCoord.decode(board.coord)
      @_initBoard.setObject card, coord

  save: (selector, target) ->
    data = @encode()
    console.log data
    
    true
    
  load: (selector, target) ->
    #data = {}
    #@decode(data)
    
    #@
    false

  preload: (selector, target) ->
    plistThemePath = cpz.CommonPath + @_resolution + '/themes/' + @_theme  + '.plist'
    textureThemePath = cpz.CommonPath + @_resolution + '/themes/' + @_theme + '.png'
    plistUIPath = cpz.CommonPath + @_resolution + '/ui' + '.plist'
    textureUIPath = cpz.CommonPath + @_resolution + '/ui' + '.png'

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

cpz.GameConfigCommon._configPaths = {};

cpz.GameConfigCommon._configPathsSet = (key, node) ->
  if cpz.GameConfigCommon._configPaths[key]
    cpz.GameConfigCommon._configPaths[key].release()
    cpz.GameConfigCommon._configPaths[key] = null
  cpz.GameConfigCommon._configPaths[key] = node
  node.retain()

cpz.GameConfigCommon.XML_FILE_NAME = 'chinesePuzzleConf.plist'

cpz.GameConfigCommon.getRootPath = (file) -> cpz.CommonPath + file
cpz.GameConfigCommon.getResolutionPath = (file, resolution) -> cpz.CommonPath + resolution + '/' + file
cpz.GameConfigCommon.getUiPath = (file, resolution) -> cpz.CommonPath + resolution + '/ui/' + file
cpz.GameConfigCommon.getThemePath = (file, resolution, theme) -> cpz.CommonPath + resolution + '/themes/' + theme + '/' + file
cpz.GameConfigCommon.getFontPath = (file) -> cpz.CommonPath + 'fonts/' + file

cpz.GameConfigCommon.getResolutions = ->
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

cpz.GameConfigCommon.getThemes = ->
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