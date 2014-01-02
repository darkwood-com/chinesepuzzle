/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

 http://www.cocos2d-x.org


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

// boot code needed for cocos2d + JS bindings.
// Not needed by cocos2d-html5

require("jsb.js");

var cpz = cpz || {};
cpz.CommonPath = '';
cpz.PlatformPath = '';
cpz.CommonSrcPath = cpz.CommonPath + 'js/';
cpz.PlatformSrcPath = cpz.PlatformPath + 'mac/';

var appFiles = [
    cpz.CommonSrcPath + 'Background/Background.js',
    cpz.CommonSrcPath + 'Cocos2Dx/CCLang.js',
    cpz.CommonSrcPath + 'Game/Card.js',
    cpz.CommonSrcPath + 'Game/CardBoard.js',
    cpz.CommonSrcPath + 'Game/CardPlay.js',
    cpz.CommonSrcPath + 'Game/Game.js',
    cpz.CommonSrcPath + 'Game/GameControl.js',
    cpz.CommonSrcPath + 'Game/GameControlChipmunk.js',
    cpz.CommonSrcPath + 'Game/GameControlNode.js',
    cpz.CommonSrcPath + 'Game/GameLayout.js',
    cpz.CommonSrcPath + 'Menu/Menu.js',
    cpz.CommonSrcPath + 'Menu/MenuBox.js',
    cpz.CommonSrcPath + 'Menu/MenuGrid.js',
    cpz.CommonSrcPath + 'Menu/MenuGridContainer.js',
    cpz.CommonSrcPath + 'Menu/MenuLabel.js',
    cpz.CommonSrcPath + 'Menu/MenuLabelContainer.js',
    cpz.CommonSrcPath + 'Menu/MenuLayout.js',
    cpz.CommonSrcPath + 'GameConfig.js',
    cpz.CommonSrcPath + 'GameScene.js',
    cpz.CommonSrcPath + 'GameStruct.js',
    cpz.CommonSrcPath + 'Resource.js',

    cpz.PlatformSrcPath + 'Cocos2Dx/CCFileUtils.js',
    cpz.PlatformSrcPath + 'GameConfig.js',
    cpz.PlatformSrcPath + 'GameScene.js'
];

cc.dumpConfig();

for( var i=0; i < appFiles.length; i++) {
    require( appFiles[i] );
}

var director = cc.Director.getInstance();
director.setDisplayStats(true);
director.setAnimationInterval(1.0 / 60);

var scene = cpz.GameScene.create();

director.runWithScene(scene);

