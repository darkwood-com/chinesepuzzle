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

CardPlay* CardPlay::cardBoardWithResolutionAndThemeAndColorAndRank(const char* resolution, const char* theme, CardPlayColor color, CardPlayRank rank)
{
	CardPlay* cardPlay = new CardPlay();
	if (cardPlay && cardPlay->initWithResolutionAndThemeAndColorAndRank(resolution, theme, color, rank))
	{
        cardPlay->autorelease();
        return cardPlay;
    }
    CC_SAFE_DELETE(cardPlay);
	return NULL;
}

bool CardPlay::initWithColorAndRank(CardPlayColor color, CardPlayRank rank)
{
	return initWithResolutionAndThemeAndColorAndRank("480x320", "classic", color, rank);
}

bool CardPlay::initWithResolutionAndThemeAndColorAndRank(const char* resolution, const char* theme, CardPlayColor color, CardPlayRank rank)
{
	if(!CCSprite::init())
	{
		return false;
	}
	
	this->isFaceUp = false;
	this->color = color;
	this->rank = rank;
	
	this->setTextureResolutionAndTheme(resolution, theme);
	
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
		
		this->setTexture(isFaceUp ? faceTexture : backTexture);
		
		CCRect rect = CCRectZero;
		rect.size = this->getTexture()->getContentSize();
		this->setTextureRect(rect);
	}
}

void CardPlay::setTextureResolutionAndTheme(const char* resolution, const char* theme)
{
	std::string path = std::string(resolution) + std::string("/themes/") + std::string(theme) + std::string("/");
	
	//patch
	std::string pathA = path + std::string("card_") + matchColor(color) + matchRank(rank) + std::string(".png");
	faceTexture = CCTextureCache::sharedTextureCache()->addImage((path + std::string("card_") + matchColor(color) + matchRank(rank) + std::string(".png")).c_str());
	backTexture = CCTextureCache::sharedTextureCache()->addImage((path + std::string("cardplaybg.png")).c_str());
	
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
