/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

var r, res, resolution, theme, _i, _j, _k, _len, _len1, _len2, _ref, _ref1;

res = [cpz.CommonPath + 'lang-de.plist', cpz.CommonPath + 'lang-en.plist', cpz.CommonPath + 'lang-fr.plist'];

_ref = cpz.GameConfigCommon.getResolutions();
for (_i = 0, _len = _ref.length; _i < _len; _i++) {
  resolution = _ref[_i];
  _ref1 = cpz.GameConfigCommon.getThemes();
  for (_j = 0, _len1 = _ref1.length; _j < _len1; _j++) {
    theme = _ref1[_j];
    res.push(cpz.GameConfigCommon.getResolutionPath('themes/' + theme + '.plist', resolution));
  }
}

cpz.Resources = [];

for (_k = 0, _len2 = res.length; _k < _len2; _k++) {
  r = res[_k];
  cpz.Resources.push({
    src: r
  });
}
