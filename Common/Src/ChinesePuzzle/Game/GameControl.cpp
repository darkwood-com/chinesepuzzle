/**
 *  GameControl.cpp
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

#include "GameControl.h"
#include "Game.h"

using namespace cocos2d;

GameControl::GameControl()
{
	
}

GameControl::~GameControl()
{
	
}

void GameControl::step(ccTime dt)
{
	
}

void GameControl::draw()
{
	
}

void GameControl::addNode(CCNode* node)
{
	
}

void GameControl::removeNode(CCNode* node)
{
	
}

void GameControl::updateNode(CCNode* node)
{
	
}

CCNode* GameControl::checkPoint(cocos2d::CCPoint p)
{
	return NULL;
}

CCNode* GameControl::checkPointNode(CCNode* c)
{
	return this->checkPoint(c->getPosition());
}

CCNode* GameControl::checkRect(cocos2d::CCRect r, Filter filter)
{
	return NULL;
}

CCNode* GameControl::checkRectNode(CCNode* c, Filter filter)
{
	CCRect rect;
	rect.origin = c->getPosition();
	rect.size = c->getContentSize();
	
	return this->checkRect(rect, filter);
}