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


#include "CardPlay.h"

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
	
	return true;
}

void CardPlayFlipAction::update(ccTime time)
{
	cardPlay->setIsFaceUp(!cardPlay->getIsFaceUp());
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


CardPlay::CardPlay() : isLocked(false)
{
}

CardPlay::~CardPlay()
{
}

CardPlay* CardPlay::cardPlayWithColorAndRank(CardPlayColor color, CardPlayRank rank)
{
	CardPlay* cardPlay = new CardPlay();
	if (cardPlay && cardPlay->initWithColorAndRank(color, rank))
	{
        cardPlay->autorelease();
        return cardPlay;
    }
    CC_SAFE_DELETE(cardPlay);
	return NULL;
}

bool CardPlay::initWithColorAndRank(CardPlayColor color, CardPlayRank rank)
{
	//patch
	std::string CardPlayname;
	switch (color)
	{
		case CardPlayColorSpade:	CardPlayname += "S"; break;
		case CardPlayColorClub:		CardPlayname += "C"; break;
		case CardPlayColorHeart:	CardPlayname += "H"; break;
		case CardPlayColorDiamond:	CardPlayname += "D"; break;
	}
	
	switch (rank)
	{
		case CardPlayRankAce:	CardPlayname += "A"; break;
		case CardPlayRankTwo:	CardPlayname += "2"; break;
		case CardPlayRankThree:	CardPlayname += "3"; break;
		case CardPlayRankFour:	CardPlayname += "4"; break;
		case CardPlayRankFive:	CardPlayname += "5"; break;
		case CardPlayRankSix:	CardPlayname += "6"; break;
		case CardPlayRankSeven: CardPlayname += "7"; break;
		case CardPlayRankEight: CardPlayname += "8"; break;
		case CardPlayRankNine:	CardPlayname += "9"; break;
		case CardPlayRankTen:	CardPlayname += "10"; break;
		case CardPlayRankJack:	CardPlayname += "J"; break;
		case CardPlayRankQueen: CardPlayname += "Q"; break;
		case CardPlayRankKing:	CardPlayname += "K"; break;
	}
	
	faceTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("480x320/themes/classic/") + CardPlayname + std::string(".png")).c_str());
	backTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("480x320/themes/classic/cardplaybg.png")).c_str());
	
	if(!CCSprite::initWithTexture(backTexture))
	{
		return false;
	}
	
	this->isFaceUp = false;
	this->color = color;
	this->rank = rank;
		
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
	if(this->isFaceUp != isFaceUp)
	{
		this->isFaceUp = isFaceUp;
		
		this->setTexture(isFaceUp ? faceTexture : backTexture);
	}
}
