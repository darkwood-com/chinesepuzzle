###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.DecoratedBox = cc.Node.extend(
  _cell: null
  
  _boxWidth: null
  _boxHeight: null
  
  getCell: -> @_cell
  getBoxWidth: -> @_boxWidth
  getBoxHeight: -> @_boxHeight

  initWithTexture: (texture, rect, size) ->
    return false unless @_super(texture, 9)
    
    @_cell.origin = rect.origin
    @_cell = cc.size(rect.width / 3, rect.height / 3)
    @setAnchorPoint cc.p(0.5, 0.5)
    @setContentSize size
    
    return true
    
  initWithFile: (filename, size) ->
    return false unless @_super(filename, 9)
    
    textureSize = @getTextureAtlas().getTexture().getContentSize()
    
    @_cell.origin = cc.p(0, 0)
    @_cell = cc.size(textureSize.width / 3, textureSize.height / 3)
    @setAnchorPoint(cc.p(0.5, 0.5))
    @setContentSize(size)
    
    return true

  setContentSize: (size) ->
    @removeAllChildrenWithCleanup(true)

    @_super size

    uw = Math.ceil(size.width / @_cell.width)
    uh = Math.ceil(size.height / @_cell.height)
    offw = size.width % @_cell.width
    offh = size.height % @_cell.height

    for j in [0..uh-1]
      for i in [0..uw-1]
  
        rect = cc.rect()
  
        if i is (uw - 2) and j is (uw - 2)
          rect = cc.rect(@_cell.width, @_cell.height, offw, offh)
        else if i is (uw - 2)
          if j is (uh - 1)
            # Top border
            rect = cc.rect(@_cell.width, 0, offw, @_cell.height)
          else if j is 0
            # Bottom border
            rect = cc.rect(@_cell.width, @_cell.height * 2, offw, @_cell.height)
          else
            # Middle
            rect = cc.rect(@_cell.width, @_cell.height, offw, @_cell.height)
        else if j is (uw - 2)
          if i is (uh - 1)
            # Right border
            rect = cc.rect(@_cell.width * 2, @_cell.height, @_cell.width, offh)
          else if i is 0
            # Left border
            rect = cc.rect(0, @_cell.height, @_cell.width, offh)
          else
            # Middle
            rect = cc.rect(@_cell.width, @_cell.height, @_cell.width, offh)
        else if i is 0
          if j is (uh - 1)
            # Top left cap
            rect = cc.rect(0, 0, @_cell.width, @_cell.height)
          else if j is 0
            # Bottom left cap
            rect = cc.rect(0, @_cell.height * 2, @_cell.width, @_cell.height)
          else
            # Left border
            rect = cc.rect(0, @_cell.height, @_cell.width, @_cell.height)
        else if i is (uw - 1)
          if j is (uh - 1)
            # Top right cap
            rect = cc.rect(@_cell.width * 2, 0, @_cell.width, @_cell.height)
          else if j is 0
            # Bottom right cap
            rect = cc.rect(@_cell.width * 2, @_cell.height * 2, @_cell.width, @_cell.height)
          else
            # Right border
            rect = cc.rect(@_cell.width * 2, @_cell.height, @_cell.width, @_cell.height)
        else if j is (uh - 1)
          # Top border
          rect = cc.rect(@_cell.width, 0, @_cell.width, @_cell.height)
        else if j is 0
          # Bottom border
          rect = cc.rect(@_cell.width, @_cell.height * 2, @_cell.width, @_cell.height)
        else
          # Middle
          rect = cc.rect(@_cell.width, @_cell.height, @_cell.width, @_cell.height)
      
        rect.origin = cc.pAdd(rect.origin, @_cell.origin)
        
        b = cc.Sprite.createWithTexture(@getTexture(), rect)
        b.setAnchorPoint(cc.p(0, 0))
        if j is (uh - 1) and i is (uw - 1)
          b.setPosition(cc.p((i - 1) * @_cell.width + offw, (j - 1) * @_cell.height + offh))
        else if j is (uh - 1)
          b.setPosition(cc.p(i * @_cell.width, (j - 1) * @_cell.height + offh))
        else if i is (uw - 1)
          b.setPosition(cc.p((i - 1) * @_cell.width + offw, j * @_cell.height))
        else
          b.setPosition(cc.p(i * @_cell.width, j * @_cell.height))
        b.setTag(j * @_cell.height + i)
        
        @addChild(b)
    
)

cpz.DecoratedBox.createWithTexture = (texture, rect, size) ->
  box = new DecoratedBox()
  return box if box and box.initWithTexture(texture, rect, size)
  null

cpz.DecoratedBox.createWithFile = (filename, size) ->
  box = new DecoratedBox()
  return box if box and box.initWithFile(filename, size)
  null