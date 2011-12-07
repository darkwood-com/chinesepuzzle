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

Card* GameControlSprite::getCard(CCPoint p)
{
	for(CardSpriteSet::const_iterator it = cards.begin(); it != cards.end(); ++it)
	{
		CCPoint local = (*it)->convertToNodeSpace(p);
		CCRect r = (*it)->getTextureRect();
		r.origin = CCPointZero;
		
		if (CCRect::CCRectContainsPoint(r, local))
		{
			return (*it);
		}
	}
	
	return NULL;
}
