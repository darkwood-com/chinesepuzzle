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


#include "cpMacro.h"
#include "CardBoard.h"
#include "GameConfig.h"

using namespace cocos2d;

CardBoard::CardBoard() :
emptySprite(NULL),
yesSprite(NULL),
noSprite(NULL),
state(CardBoardEmpty)
{
}

CardBoard::~CardBoard()
{
	CC_SAFE_RELEASE(emptySprite);
	CC_SAFE_RELEASE(yesSprite);
	CC_SAFE_RELEASE(noSprite);
}

CardBoard* CardBoard::cardBoardWithConf(GameConfigCommon* conf)
{
	CardBoard* cardBoard = new CardBoard();
	if (cardBoard && cardBoard->initCardBoardWithConf(conf))
	{
        cardBoard->autorelease();
        return cardBoard;
    }
    CC_SAFE_DELETE(cardBoard);
	return NULL;
}

bool CardBoard::initCardBoardWithConf(GameConfigCommon* conf)
{
	if(!CCSpriteBatchNode::initWithTexture(ccTextureNull, 1))
	{
		return false;
	}
	
	this->setConf(conf);
	
	return true;
}

CardBoardState CardBoard::getState()
{
	return this->state;
}

void CardBoard::setState(CardBoardState state)
{
	this->setState(state, false);
}

void CardBoard::setState(CardBoardState state, bool force)
{
	if(this->state != state || force)
	{
		switch (state)
		{
			case CardBoardEmpty: copySpriteBatchNode(emptySprite, this); break;
			case CardBoardYes: copySpriteBatchNode(yesSprite, this); break;
			case CardBoardNo: copySpriteBatchNode(noSprite, this); break;
		}
		
		this->state = state;
	}
}

void CardBoard::setConf(GameConfigCommon* conf)
{
	if(emptySprite == NULL)
	{
		emptySprite = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		emptySprite->retain();
	}
	if(yesSprite == NULL)
	{
		yesSprite = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		yesSprite->retain();
	}
	if(noSprite == NULL)
	{
		noSprite = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		noSprite->retain();
	}
	conf->getNodeThemePath("cardboardempty", emptySprite);
	conf->getNodeThemePath("cardboardyes", yesSprite);
	conf->getNodeThemePath("cardboardno", noSprite);
	
	this->setState(this->getState(), true);
}
