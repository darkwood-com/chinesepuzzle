###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.MenuBoxTag =
  Title: 0

cpz.MenuBox = cc.Node.extend(
  _bg: null
  _validBtn: null
  _titleLabel: null

  _state: null
  _itemForTouch: (touch) ->
    touchLocation = touch.locationInView()
    touchLocation = cc.Director.getInstance().convertToGL touchLocation

    menuItems = @getItems()
    menuItems.addObject @_validBtn
    if (menuItems && menuItems.count() > 0)
      for child in menuItems
        if (child instanceof cc.MenuItem && child.isVisible() && child.isEnabled())
          local = child.convertToNodeSpace(touchLocation)
          CCRect r = child.rect()
          r.origin = cc.PointZero()
  
          if cc.rectContainsPoint(r, local)
            return child

    null

  _selectedItem: null

  _layoutFontFile: null

  _titlePosition: null
  _validPosition: null

  _items: []

  ctor: ->
    @_super()

  initWithConf: (conf) ->
    @_items = []

    @_state = cc.MENU_STATE_WAITING
    @_selectedItem = null

    spriteNodeBg = cc.SpriteBatchNode.createWithTexture cc.textureNull()
    conf.getNodeUiPath 'menuContainer', spriteNodeBg
    spriteBg = cc.copyFirstSpriteBatchNode spriteNodeBg

    @_bg = new cc.DecoratedBox()
    @_bg.initWithTexture spriteBg.getTexture(), spriteBg.getTextureRect(), @getContentSize()
    @_bg.setAnchorPoint cc.p(0.5, 0.5)
    @addChild @_bg

    spriteNodeValidBtn = cc.SpriteBatchNode.createWithTexture cc.textureNull()
    conf.getNodeUiPath 'menuItemOk', spriteNodeValidBtn
    spriteValidBtn = cc.copyFirstSpriteBatchNode spriteNodeValidBtn

    @_validBtn = new cc.MenuItemSprite()
    @_validBtn.initFromNormalSprite spriteValidBtn, null, null, null, null
    @_validBtn.setAnchorPoint cc.p(0.5, 0.5)
    @_validBtn.setScale 0.75
    @addChild @_validBtn

    true

  initWithConfAndContentSize: (conf, size) ->
    if @initWithConf(conf)
      @setContentSize size

      return true

    false

  getTitle: -> return if @_titleLabel then @_titleLabel.getString() else null
  setTitle: (title, fontFile) ->
    if(@_titleLabel && @_layoutFontFile is fontFile) @_titleLabel.setString(title)
    else
      @removeChildByTag cpz.MenuBoxTag.Title, true
      @_titleLabel = new cc.LabelBMFont()
      @_titleLabel.initWithString title, 'fonts/' + fontFile
      @_titleLabel.setAnchorPoint cc.p(0.0, 1.0)
      @addChild @_titleLabel, 0, cpz.MenuBoxTag.Title
  
      @_layoutFontFile = fontFile

    @layout()

  getTitlePosition: -> @_titlePosition
  setTitlePosition: (@_titlePosition) -> @
  getValidPosition: -> @_validPosition
  setValidPosition: (@_validPosition) -> @

  setItems: (items) ->
    if(@_items && @_items.count() > 0)
      for child in @_items
        @removeChild child, true

    @_items = items

    if(@_items.count() > 0)
      for child in @_items
        @addChild child

    @

  getItems: -> @_items
  addItem: (child, zOrder, tag) ->
    @_items.addObject(pChild)
    @addChild(pChild, zOrder, tag)

  removeItemByTag: (tag, cleanup) ->
    if tag is cc.NODE_TAG_INVALID
      cc.log("cc.MenuBox.removeChildByTag(): argument tag is an invalid tag")

    child = @getChildByTag(tag)

    if child is null
      CCLOG('cocos2d: removeItemByTag: child not found!')
    else
      @_items.removeObject child

    @removeChildByTag tag, cleanup

  setContentSize: (size) ->
    @_super(size)

    @layout()

  layout: (anim = true) ->
    size = @getContentSize()

    if @_titleLabel then @_titleLabel.setPosition cc.p(@_titlePosition.x, size.height - @_titlePosition.y)
    if @_validBtn then @_validBtn.setPosition cc.p(size.width - @_validPosition.x, size.height - @_validPosition.y)
    if @_bg
      @_bg.setPosition(cc.p(size.width / 2, size.height / 2))
      @_bg.setContentSize(CCSizeMake(size.width, size.height))

  setOkTarget: (rec, selector) ->
    @_validBtn.setTarget(rec, selector)

  onTouchBegan: (touch, event) ->
    return false  if @_state isnt cc.MENU_STATE_WAITING or not @_visible or not @_enabled

    c = @_parent
    while c?
      return false  unless c.isVisible()
      c = c.getParent()

    @_selectedItem = @_itemForTouch(touch)
    if @_selectedItem
      @_state = cc.MENU_STATE_TRACKING_TOUCH
      @_selectedItem.selected()
      return true
    false

  onTouchMoved: (touch, event) ->
    if @_state isnt cc.MENU_STATE_TRACKING_TOUCH
      cc.log "cc.Menu.onTouchMoved(): invalid state"
      return

    currentItem = @_itemForTouch(touch)
    unless currentItem is @_selectedItem
      @_selectedItem.unselected()  if @_selectedItem
      @_selectedItem = currentItem
      @_selectedItem.selected()  if @_selectedItem

  onTouchEnded: (touch, event) ->
    if @_state isnt cc.MENU_STATE_TRACKING_TOUCH
      cc.log "cc.Menu.onTouchEnded(): invalid state"
      return

    if @_selectedItem
      @_selectedItem.unselected()
      @_selectedItem.activate()
    @_state = cc.MENU_STATE_WAITING
    
  onTouchCancelled: (touch, event) ->
    if @_state isnt cc.MENU_STATE_TRACKING_TOUCH
      cc.log "cc.Menu.onTouchCancelled(): invalid state"
      return

    @_selectedItem.unselected()  if @_selectedItem
    @_state = cc.MENU_STATE_WAITING
)
