###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cc.CCLang = cc.Class.extend(
  _data: null
  _lang: null

  ctor: ->
    @_data = {}

  getLang: ->
    @_lang

  setLang: (lang) ->
    @_lang = lang

  get: (key) ->
    @_data[key] || key

  set: (key, value) ->
    @_data[key] = value

  addLang: (fileName) ->
    fileUtils = cc.FileUtils.getInstance()
    filePath = cpz.CommonPath + fileName

    switch @_lang
      when cc.LANGUAGE_FRENCH then filePath += '-fr'
      when cc.LANGUAGE_GERMAN then filePath += '-de'
      when cc.LANGUAGE_ENGLISH then filePath += '-en'
      else filePath += '-en'

    fullPath = fileUtils.fullPathForFilename filePath + '.plist'
    dict = fileUtils.getDataFromPlistFile fullPath

    for key, value of dict
      @set key, value if value

    @
)

cc.CCLang.s_sharedLang = null

cc.CCLang.getInstance = ->
  unless @s_sharedLang
    @s_sharedLang = new cc.CCLang()
  @s_sharedLang
