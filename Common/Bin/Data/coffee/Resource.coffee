###
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
###

res = [
  #image

  #plist
  cpz.CommonPath + 'lang-de.plist',
  cpz.CommonPath + 'lang-en.plist',
  cpz.CommonPath + 'lang-fr.plist',

  #fnt
  cpz.GameConfigCommon.getFontPath('arial16.fnt'),
  cpz.GameConfigCommon.getFontPath('arial32.fnt'),

  #tmx

  #bgm

  #effect

  #audio
  #cpz.CommonPath + 'sound/bgm1.mp3',
  #cpz.CommonPath + 'sound/bgm2.mp3',
  #cpz.CommonPath + 'sound/bgm3.mp3',
  #cpz.CommonPath + 'sound/card_move.mp3',
  #cpz.CommonPath + 'sound/card_undo.mp3',
  #cpz.CommonPath + 'sound/menu_pop.mp3',
  #cpz.CommonPath + 'sound/menu_push.mp3',
  #cpz.CommonPath + 'sound/menu_select.mp3',
  #cpz.CommonPath + 'sound/shuffle.mp3',
]

#for resolution in cpz.GameConfigCommon.getResolutions()
#  for theme in cpz.GameConfigCommon.getThemes()
#    res.push cpz.GameConfigCommon.getResolutionPath('themes/' + theme + '.plist', resolution)
#    res.push cpz.GameConfigCommon.getResolutionPath('themes/' + theme + '.png', resolution)

cpz.Resources = []
for r in res
  cpz.Resources.push
    src: r
