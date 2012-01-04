/**
 *  Background.h
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

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"

class GameSceneCommon;

// Background Layer
class CC_DLL Background : public cocos2d::CCLayer
{
protected:
	cocos2d::CCSprite* bgPattern;

public:
	Background();
	virtual ~Background();
	LAYER_NODE_FUNC_PARAM(Background, GameSceneCommon*, gs);
	
	virtual bool init(GameSceneCommon* gs);

	virtual void setContentSize(const cocos2d::CCSize& size);

	CC_SYNTHESIZE_READONLY(GameSceneCommon*, gs, BackgroundScene);
};

#endif // __Background_H__
