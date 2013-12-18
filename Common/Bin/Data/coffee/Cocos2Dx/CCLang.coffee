###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

cpz.CCLang = cc.Class.extend(
  init: ->
    true
)

cpz.CCLang.s_sharedLang = null

cpz.CCLang.getInstance = ->
  unless @s_sharedLang
    @s_sharedLang = new cpz.CCLang()
    @s_sharedLang.init()
  @s_sharedLang
