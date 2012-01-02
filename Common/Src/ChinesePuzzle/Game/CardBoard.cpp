/**
 *  CardBoard.cpp
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


#include "CardBoard.h"

using namespace cocos2d;

CardBoard::CardBoard()
{
}

CardBoard::~CardBoard()
{
}

CardBoard* CardBoard::cardBoard()
{
	CardBoard* cardBoard = new CardBoard();
	if (cardBoard && cardBoard->initCardBoard())
	{
        cardBoard->autorelease();
        return cardBoard;
    }
    CC_SAFE_DELETE(cardBoard);
	return NULL;
}

CardBoard* CardBoard::cardBoardWithResolutionAndTheme(const char* resolution, const char* theme)
{
	CardBoard* cardBoard = new CardBoard();
	if (cardBoard && cardBoard->initCardBoardWithResolutionAndTheme(resolution, theme))
	{
        cardBoard->autorelease();
        return cardBoard;
    }
    CC_SAFE_DELETE(cardBoard);
	return NULL;
}


bool CardBoard::initCardBoard()
{
	return initCardBoardWithResolutionAndTheme("480x320", "classic");
}

bool CardBoard::initCardBoardWithResolutionAndTheme(const char* resolution, const char* theme)
{
	std::string path = std::string(resolution) + std::string("/themes/") + std::string(theme) + std::string("/");
	
	emptyTexture = CCTextureCache::sharedTextureCache()->addImage((path + std::string("cardboardempty.png")).c_str());
	yesTexture = CCTextureCache::sharedTextureCache()->addImage((path + std::string("cardboardyes.png")).c_str());
	noTexture = CCTextureCache::sharedTextureCache()->addImage((path + std::string("cardboardno.png")).c_str());
	
	if(!CCSprite::initWithTexture(emptyTexture))
	{
		return false;
	}
	
	return true;
}

CardBoardState CardBoard::getState()
{
	return this->state;
}

void CardBoard::setState(CardBoardState state)
{
	if(this->state != state)
	{
		switch (state)
		{
			case CardBoardEmpty: this->setTexture(emptyTexture); break;
			case CardBoardYes: this->setTexture(yesTexture); break;
			case CardBoardNo: this->setTexture(noTexture); break;
		}
		
		this->state = state;
	}
}