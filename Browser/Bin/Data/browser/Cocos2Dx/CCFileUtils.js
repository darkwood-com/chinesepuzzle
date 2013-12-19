/*
This file is part of the ChinesePuzzle package.

(c) Mathieu Ledru

For the full copyright and license information, please view the LICENSE
file that was distributed with this source code.
*/

cc.FileUtils.prototype.getDataFromPlistFile = function (fileName) {
    return this.dictionaryWithContentsOfFile(fileName);
};
