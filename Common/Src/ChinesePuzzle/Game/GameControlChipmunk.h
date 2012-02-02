/**
 *  GameControlChipmunk.h
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

#ifndef __GAME_CONTROL_CHIPMUNK_H__
#define __GAME_CONTROL_CHIPMUNK_H__

#include "GameControl.h"

struct cpSpace;
struct cpShape;

typedef std::map<cocos2d::CCNode*, cpShape*> NodeCpMap;

class CC_DLL GameControlChipmunk : public GameControl
{
protected:
	cpSpace* space;
	NodeCpMap nodes;
	
public:
	GameControlChipmunk();
	virtual ~GameControlChipmunk();
	
	virtual void step(cocos2d::ccTime dt);
	virtual void draw();
	
	virtual void addNode(cocos2d::CCNode* node);
	virtual void removeNode(cocos2d::CCNode* node);
	virtual void updateNode(cocos2d::CCNode* node);
	virtual cocos2d::CCNode* checkPoint(cocos2d::CCPoint p);
	virtual cocos2d::CCNode* checkRect(cocos2d::CCRect r, Filter filter);
};

#endif // __GAME_CONTROL_CHIPMUNK_H__
