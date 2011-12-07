/**
 *  Card.cpp
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


#include "Card.h"

using namespace cocos2d;

CardFlipAction* CardFlipAction::actionWithCard(Card* card)
{
	CardFlipAction* action = new CardFlipAction();
	if(action && action->initWithCard(card))
	{
		action->autorelease();
		return action;
	}
	CC_SAFE_DELETE(action);
	return NULL;
}

bool CardFlipAction::initWithCard(Card* card)
{
	this->card = card;
	
	return true;
}

void CardFlipAction::update(ccTime time)
{
	card->setIsFaceUp(!card->getIsFaceUp());
}

CCObject* CardFlipAction::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CardFlipAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CardFlipAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CardFlipAction();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCFiniteTimeAction::copyWithZone(pZone);
	
	pCopy->initWithCard(card);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}


Card::Card() : isLocked(false)
{
}

Card::~Card()
{
}

Card* Card::cardWithColorAndRank(CardColor color, CardRank rank)
{
	Card* card = new Card();
	if (card && card->initWithColorAndRank(color, rank))
	{
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
	return NULL;
}

bool Card::initWithColorAndRank(CardColor color, CardRank rank)
{
	//patch
	std::string cardname;
	switch (color)
	{
		case CardColorSpade:	cardname += "S"; break;
		case CardColorClub:		cardname += "C"; break;
		case CardColorHeart:	cardname += "H"; break;
		case CardColorDiamond:	cardname += "D"; break;
	}
	
	switch (rank)
	{
		case CardRankAce:	cardname += "A"; break;
		case CardRankTwo:	cardname += "2"; break;
		case CardRankThree:	cardname += "3"; break;
		case CardRankFour:	cardname += "4"; break;
		case CardRankFive:	cardname += "5"; break;
		case CardRankSix:	cardname += "6"; break;
		case CardRankSeven: cardname += "7"; break;
		case CardRankEight: cardname += "8"; break;
		case CardRankNine:	cardname += "9"; break;
		case CardRankTen:	cardname += "10"; break;
		case CardRankJack:	cardname += "J"; break;
		case CardRankQueen: cardname += "Q"; break;
		case CardRankKing:	cardname += "K"; break;
	}
	
	faceTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("Data/themes/classic/480x320/") + cardname + std::string(".png")).c_str());
	backTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("Data/themes/classic/480x320/bgcard.png")).c_str());
	
	if(!CCSprite::initWithTexture(backTexture))
	{
		return false;
	}
	
	this->isFaceUp = false;
	this->color = color;
	this->rank = rank;
		
	return true;
}

void Card::setPosition(const cocos2d::CCPoint& pos)
{
	CCSprite::setPosition(pos);
	
	for (std::set<CardDelegate*>::const_iterator it = cardDelegates.begin(); it != cardDelegates.end(); ++it)
	{
		(*it)->updateCard(this);
	}
}

CardColor Card::getCardColor()
{
	return this->color;
}

CardRank Card::getCardRank()
{
	return this->rank;
}

bool Card::getIsLocked()
{
	return this->isLocked;
}

void Card::setIsLocked(bool isLocked)
{
	if(this->isLocked != isLocked)
	{
		this->isLocked = isLocked;
	}
}

void Card::addCardDelegate(CardDelegate* delegate)
{
	cardDelegates.insert(delegate);
}

void Card::removeCardDelegate(CardDelegate* delegate)
{
	cardDelegates.erase(delegate);
}

bool Card::isNextToCard(Card* card)
{
	return card != NULL && this->color == card->color && this->rank == card->rank + 1;
}

bool Card::getIsFaceUp()
{
	return this->isFaceUp;
}

void Card::setIsFaceUp(bool isFaceUp)
{
	if(this->isFaceUp != isFaceUp)
	{
		this->isFaceUp = isFaceUp;
		
		this->setTexture(isFaceUp ? faceTexture : backTexture);
	}
}
