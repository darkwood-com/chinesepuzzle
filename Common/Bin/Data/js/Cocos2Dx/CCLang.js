/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cpz.CCLang = cc.Class.extend({
  init: function() {
    return true;
  }
});

cpz.CCLang.s_sharedLang = null;

cpz.CCLang.getInstance = function() {
  if (!this.s_sharedLang) {
    this.s_sharedLang = new cpz.CCLang();
    this.s_sharedLang.init();
  }
  return this.s_sharedLang;
};
