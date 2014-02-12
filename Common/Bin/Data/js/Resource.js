/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

var r, res, _i, _len;

res = [cpz.CommonPath + 'lang-de.plist', cpz.CommonPath + 'lang-en.plist', cpz.CommonPath + 'lang-fr.plist', cpz.GameConfigCommon.getFontPath('arial16.fnt'), cpz.GameConfigCommon.getFontPath('arial32.fnt'), cpz.GameConfigCommon.getRootPath('bgPattern.png')];

cpz.Resources = [];

for (_i = 0, _len = res.length; _i < _len; _i++) {
  r = res[_i];
  cpz.Resources.push({
    src: r
  });
}
