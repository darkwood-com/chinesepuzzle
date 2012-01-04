/**
 *  GameScene_mac.h
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

#import "GameScene.h"
#include "CCReshapeDelegate.h"

class Game;

class CC_DLL GameScene : public GameSceneCommon, public cocos2d::CCReshapeDelegate
{
protected:
	cocos2d::CCSprite* bgPattern;
	
public:
	GameScene();
	virtual ~GameScene();
	SCENE_NODE_FUNC(GameScene);
	
	virtual bool init();
	
	virtual void ccReshape();
};

#endif // __GAME_SCENE_H__
