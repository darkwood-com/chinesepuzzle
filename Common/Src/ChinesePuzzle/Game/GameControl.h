/**
 *  GameControl.h
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

#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include "cocos2d.h"
#include "CCNode.h"

// GameControl
class CC_DLL GameControl : public cocos2d::CCObject
{
public:
	typedef bool (*Filter)(cocos2d::CCNode*);

	GameControl();
	virtual ~GameControl();
	
	virtual void step(cocos2d::ccTime dt);
	virtual void draw();
	
	virtual void addNode(cocos2d::CCNode* node); //add controls for this node
	virtual void removeNode(cocos2d::CCNode* node); //remove controls for this node
	virtual void updateNode(cocos2d::CCNode* node); //update node controls
	virtual cocos2d::CCNode* checkPoint(cocos2d::CCPoint p); //retrive a node from a location
	virtual cocos2d::CCNode* checkPointNode(cocos2d::CCNode* c); //retrive a node from a node
	virtual cocos2d::CCNode* checkRect(cocos2d::CCRect r, Filter filter); //retrive a node from a location
	virtual cocos2d::CCNode* checkRectNode(cocos2d::CCNode* c, Filter filter); //retrive a node from a node
};

#endif // __GAME_CONTROL_H__
