/**
 *  GameScene.h
 *  ChinesePuzzle
 *
 *  Created by Mathieu LEDRU on 01/11/11.
 *
 *  GPL License:
 *  Copyright (c) 2011, Mathieu LEDRU
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Game.h"
#include "Menu.h"

class GameScene : public cocos2d::CCScene
{
public:
	GameScene();
	virtual ~GameScene();
	SCENE_NODE_FUNC(GameScene);
	
	virtual bool init();
	
	Game* game();
	Menu* menu();
	Menu* menuWithLayout(MenuLayout::Type ml);
	
	void newGame();
	
	CC_SYNTHESIZE_READONLY(Game*, pGame, Game);
	CC_SYNTHESIZE_READONLY(Menu*, pMenu, Menu);
};

#endif // __GAME_SCENE_H__
