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

#ifndef __GAME_SCENE_COMMON_H__
#define __GAME_SCENE_COMMON_H__

#include "cocos2d.h"

#include "GameConfig.h"
#include "Game.h"
#include "Menu.h"

typedef enum {
	GameSceneZOrderBG = 0,
	GameSceneZOrderGame = 1,
	GameSceneZOrderMenu = 2,
} GameSceneZOrder;

class CC_DLL GameSceneCommon : public cocos2d::CCScene
{
public:
	GameSceneCommon();
	virtual ~GameSceneCommon();
	SCENE_NODE_FUNC(GameSceneCommon);
	
	virtual bool init();
	
	Game* game();
	Menu* menu();
	Menu* menuWithLayout(MenuLayout::Type ml);
	
	void newGame();
	void retryGame();
	void setResolution(const std::string& resolution);
	void setTheme(const std::string& theme);
	
	virtual void layout(bool anim = true);
	
	CC_SYNTHESIZE_READONLY(GameConfig*, conf, Conf);
	CC_SYNTHESIZE_READONLY(Game*, pGame, Game);
	CC_SYNTHESIZE_READONLY(Menu*, pMenu, Menu);
};

#endif // __GAME_SCENE_COMMON_H__
