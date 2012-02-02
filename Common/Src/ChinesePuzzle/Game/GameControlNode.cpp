/**
 *  GameControlNode.cpp
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

#include "GameControlNode.h"
#include "CCNode.h"
#include "Game.h"

using namespace cocos2d;

GameControlNode::GameControlNode()
{
}

GameControlNode::~GameControlNode()
{
}

void GameControlNode::step(ccTime dt)
{
	
}

void GameControlNode::draw()
{
	
}

void GameControlNode::addNode(CCNode* node)
{
	nodes.insert(node);
}

void GameControlNode::removeNode(CCNode* node)
{
	nodes.erase(node);
}

void GameControlNode::updateNode(CCNode* node)
{
	
}

CCNode* GameControlNode::checkPoint(cocos2d::CCPoint p)
{
	for(NodeNodeSet::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		CCRect rIt = (*it)->boundingBox();
		rIt.origin = (*it)->convertToWorldSpace(CCPointZero);
		
		if (CCRect::CCRectContainsPoint(rIt, p))
		{
			return (*it);
		}
	}
	
	return NULL;
}

CCNode* GameControlNode::checkPointNode(CCNode* c)
{
	for(NodeNodeSet::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if((*it) == c) continue;
		
		CCPoint p = c->getPosition();
		CCRect rIt = (*it)->boundingBox();
		
		if (CCRect::CCRectContainsPoint(rIt, p))
		{
			return (*it);
		}
	}
	
	return NULL;
}

CCNode* GameControlNode::checkRect(cocos2d::CCRect r, Filter filter)
{
	CCNode* cRes = NULL;
	float minDist = -1;
	
	for(NodeNodeSet::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if(!filter(*it)) continue;
		
		CCRect rIt = (*it)->boundingBox();
		rIt.origin = (*it)->convertToWorldSpace(CCPointZero);
		
		if (CCRect::CCRectIntersectsRect(rIt, r))
		{
			CCPoint vect = ccpAdd(r.origin, ccpNeg(rIt.origin));
			float dist = vect.x * vect.x + vect.y * vect.y;
			if(minDist == -1 || dist < minDist)
			{
				minDist = dist;
				cRes = (*it);
			}
		}
	}
	
	return cRes;
}

CCNode* GameControlNode::checkRectNode(CCNode* c, Filter filter)
{
	CCNode* cRes = NULL;
	float minDist = -1;
	
	for(NodeNodeSet::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if(!filter(*it)) continue;
		
		CCRect r = c->boundingBox();
		CCRect rIt = (*it)->boundingBox();
		
		if (CCRect::CCRectIntersectsRect(rIt, r))
		{
			CCPoint vect = ccpAdd(r.origin, ccpNeg(rIt.origin));
			float dist = vect.x * vect.x + vect.y * vect.y;
			if(minDist == -1 || dist < minDist)
			{
				minDist = dist;
				cRes = (*it);
			}
		}
	}
	
	return cRes;
}
