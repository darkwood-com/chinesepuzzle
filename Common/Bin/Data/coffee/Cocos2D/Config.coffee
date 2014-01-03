###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

#cc.SpriteBatchNode.extend = cc.Class.extend unless cc.SpriteBatchNode.extend

cc.textureNull = -> new cc.Texture2D()

cc.copySpriteBatchNode = (from, to) ->

cc.copyFirstSpriteBatchNode = (sprite) ->

###
Shuffle array
@function
@param {Array} arr
@return {Array}
###
cc.ArrayShuffle = (arr) ->
  currentIndex = arr.length
  temporaryValue = undefined
  randomIndex = undefined

  # While there remain elements to shuffle...
  while 0 isnt currentIndex

    # Pick a remaining element...
    randomIndex = Math.floor(Math.random() * currentIndex)
    currentIndex -= 1

    # And swap it with the current element.
    temporaryValue = arr[currentIndex]
    arr[currentIndex] = arr[randomIndex]
    arr[randomIndex] = temporaryValue
  arr

cc.ObjectHas = (obj, key) -> obj.hasOwnProperty key
cc.ObjectKeys = (obj) ->
  throw new TypeError("Invalid object") if obj isnt Object(obj)
  keys = []
  for key of obj
    keys.push key  if cc.ObjectHas(obj, key)
  keys
cc.ObjectSize = (obj) ->
  return 0 unless obj?
  if (obj.length is +obj.length) then obj.length else cc.ObjectKeys(obj).length

cc.Dictionary = cc.Class.extend(
  _keyMapTb: null
  _valueMapTb: null
  __currId: 0

  ctor: ->
    @_keyMapTb = {}
    @_valueMapTb = {}
    @__currId = 2 << (0 | (Math.random() * 10))

  __getKey: ->
    @__currId++
    "key_" + @__currId

  setObject: (value, key) ->
    return  unless key?
    keyId = @__getKey()
    @_keyMapTb[keyId] = key
    @_valueMapTb[keyId] = value

  objectForKey: (key) ->
    return null  unless key?
    locKeyMapTb = @_keyMapTb
    for keyId of locKeyMapTb
      return @_valueMapTb[keyId]  if locKeyMapTb[keyId] is key
    null

  valueForKey: (key) ->
    @objectForKey key

  removeObjectForKey: (key) ->
    return  unless key?
    locKeyMapTb = @_keyMapTb
    for keyId of locKeyMapTb
      if locKeyMapTb[keyId] is key
        delete @_valueMapTb[keyId]

        delete locKeyMapTb[keyId]

        return

  removeObjectsForKeys: (keys) ->
    return  unless keys?
    i = 0

    while i < keys.length
      @removeObjectForKey keys[i]
      i++

  allKeys: ->
    keyArr = []
    locKeyMapTb = @_keyMapTb
    for key of locKeyMapTb
      keyArr.push locKeyMapTb[key]
    keyArr

  removeAllObjects: ->
    @_keyMapTb = {}
    @_valueMapTb = {}

  count: ->
    @allKeys().length
)