/**
 *  GameControlSprite.cpp
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

#include "GameControlSprite.h"
#include "Card.h"
#include "Game.h"

using namespace cocos2d;

GameControlSprite::GameControlSprite()
{
}

GameControlSprite::~GameControlSprite()
{
}

void GameControlSprite::step(ccTime dt)
{
	
}

void GameControlSprite::draw()
{
	
}

void GameControlSprite::addCard(Card* card)
{
	cards.insert(card);
}

void GameControlSprite::removeCard(Card* card)
{
	cards.erase(card);
}

void GameControlSprite::updateCard(Card* card)
{
	
}

Card* GameControlSprite::checkPoint(cocos2d::CCPoint p)
{
	for(CardSpriteSet::const_iterator it = cards.begin(); it != cards.end(); ++it)
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

Card* GameControlSprite::checkPointCard(Card* c)
{
	for(CardSpriteSet::const_iterator it = cards.begin(); it != cards.end(); ++it)
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

Card* GameControlSprite::checkRect(cocos2d::CCRect r, CardType filter)
{
	Card* cRes = NULL;
	float minDist = -1;
	
	for(CardSpriteSet::const_iterator it = cards.begin(); it != cards.end(); ++it)
	{
		if((*it)->getType() != filter) continue;
		
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

Card* GameControlSprite::checkRectCard(Card* c, CardType filter)
{
	Card* cRes = NULL;
	float minDist = -1;
	
	for(CardSpriteSet::const_iterator it = cards.begin(); it != cards.end(); ++it)
	{
		if((*it) == c || (*it)->getType() != filter) continue;
		
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
