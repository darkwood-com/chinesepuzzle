/**
 *  CardPlay.cpp
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
#include "CardPlay.h"
#include "GameConfig.h"

using namespace cocos2d;

CardPlayFlipAction* CardPlayFlipAction::actionWithCardPlay(CardPlay* cardPlay)
{
	CardPlayFlipAction* action = new CardPlayFlipAction();
	if(action && action->initWithCardPlay(cardPlay))
	{
		action->autorelease();
		return action;
	}
	CC_SAFE_DELETE(action);
	return NULL;
}

bool CardPlayFlipAction::initWithCardPlay(CardPlay* cardPlay)
{
	this->cardPlay = cardPlay;
	this->isFaceUp = cardPlay->getIsFaceUp();
	
	return true;
}

void CardPlayFlipAction::update(ccTime time)
{
	cardPlay->setIsFaceUp(!this->isFaceUp);
}

CCObject* CardPlayFlipAction::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CardPlayFlipAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CardPlayFlipAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CardPlayFlipAction();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCFiniteTimeAction::copyWithZone(pZone);
	
	pCopy->initWithCardPlay(cardPlay);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

CardPlay::CardPlay() :
faceSprite(NULL),
backSprite(NULL),
isLocked(false)
{
}

CardPlay::~CardPlay()
{
	CC_SAFE_RELEASE(faceSprite);
	CC_SAFE_RELEASE(backSprite);
}

CardPlay* CardPlay::cardBoardWithConfAndColorAndRank(GameConfigCommon* conf, CardPlayColor color, CardPlayRank rank)
{
	CardPlay* cardPlay = new CardPlay();
	if (cardPlay && cardPlay->initWithConfAndColorAndRank(conf, color, rank))
	{
        cardPlay->autorelease();
        return cardPlay;
    }
    CC_SAFE_DELETE(cardPlay);
	return NULL;
}

bool CardPlay::initWithConfAndColorAndRank(GameConfigCommon* conf, CardPlayColor color, CardPlayRank rank)
{
	if(!CCSpriteBatchNode::initWithTexture(ccTextureNull, 4))
	{
		return false;
	}
	
	this->isFaceUp = false;
	this->color = color;
	this->rank = rank;
	
	this->setConf(conf);
	
	return true;
}

bool CardPlay::isNextToCardPlay(CardPlay* cardPlay)
{
	return cardPlay != NULL && this->color == cardPlay->color && this->rank == cardPlay->rank + 1;
}

bool CardPlay::getIsFaceUp()
{
	return this->isFaceUp;
}

void CardPlay::setIsFaceUp(bool isFaceUp)
{
	this->setIsFaceUp(isFaceUp, false);
}

void CardPlay::setIsFaceUp(bool isFaceUp, bool force)
{
	if(this->isFaceUp != isFaceUp || force)
	{
		this->isFaceUp = isFaceUp;
		
		copySpriteBatchNode(isFaceUp ? faceSprite : backSprite, this);
	}
}

void CardPlay::setConf(GameConfigCommon* conf)
{
	if(faceSprite == NULL)
	{
		faceSprite = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		faceSprite->retain();
	}
	
	if(backSprite == NULL)
	{
		backSprite = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		backSprite->retain();
	}
	
	conf->getNodeThemePath((std::string("card_") + matchColor(color) + matchRank(rank)).c_str(), faceSprite);
	conf->getNodeThemePath("cardplaybg", backSprite);
	
	this->setIsFaceUp(this->getIsFaceUp(), true);
}

std::string CardPlay::matchColor(CardPlayColor color)
{
	switch (color)
	{
		case CardPlayColorSpade:	return "S"; break;
		case CardPlayColorClub:		return "C"; break;
		case CardPlayColorHeart:	return "H"; break;
		case CardPlayColorDiamond:	return "D"; break;
	}
}

CardPlayColor CardPlay::matchColor(std::string color)
{
	if(color == "S") return CardPlayColorSpade;
	else if(color == "C") return CardPlayColorClub;
	else if(color == "H") return CardPlayColorHeart;
	else if(color == "D") return CardPlayColorDiamond;
	
	return CardPlayColorSpade;
}

std::string CardPlay::matchRank(CardPlayRank rank)
{
	switch (rank)
	{
		case CardPlayRankAce:	return "A"; break;
		case CardPlayRankTwo:	return "2"; break;
		case CardPlayRankThree:	return "3"; break;
		case CardPlayRankFour:	return "4"; break;
		case CardPlayRankFive:	return "5"; break;
		case CardPlayRankSix:	return "6"; break;
		case CardPlayRankSeven: return "7"; break;
		case CardPlayRankEight: return "8"; break;
		case CardPlayRankNine:	return "9"; break;
		case CardPlayRankTen:	return "10"; break;
		case CardPlayRankJack:	return "J"; break;
		case CardPlayRankQueen: return "Q"; break;
		case CardPlayRankKing:	return "K"; break;
	}
}

CardPlayRank CardPlay::matchRank(std::string rank)
{
	if(rank == "A") return CardPlayRankAce;
	else if(rank == "2") return CardPlayRankTwo;
	else if(rank == "3") return CardPlayRankThree;
	else if(rank == "4") return CardPlayRankFour;
	else if(rank == "5") return CardPlayRankFive;
	else if(rank == "6") return CardPlayRankSix;
	else if(rank == "7") return CardPlayRankSeven;
	else if(rank == "8") return CardPlayRankEight;
	else if(rank == "9") return CardPlayRankNine;
	else if(rank == "10") return CardPlayRankTen;
	else if(rank == "J") return CardPlayRankJack;
	else if(rank == "Q") return CardPlayRankQueen;
	else if(rank == "K") return CardPlayRankKing;
	
	return CardPlayRankAce;
}
