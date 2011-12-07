/**
 *  Card.h
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

#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
#include "CardDelegate.h"


typedef enum {
	CardColorSpade,
	CardColorClub,
	CardColorHeart,
	CardColorDiamond
} CardColor;

typedef enum {
	CardRankAce,
	CardRankTwo,
	CardRankThree,
	CardRankFour,
	CardRankFive,
	CardRankSix,
	CardRankSeven,
	CardRankEight,
	CardRankNine,
	CardRankTen,
	CardRankJack,
	CardRankQueen,
	CardRankKing
} CardRank;

class Card;
class CC_DLL CardFlipAction : public cocos2d::CCFiniteTimeAction
{
protected:
	Card* card;

public:
	static CardFlipAction* actionWithCard(Card* card);
	virtual bool initWithCard(Card* card);
	virtual void update(cocos2d::ccTime time);
	virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
};

class CC_DLL Card : public cocos2d::CCSprite
{
protected:
	CardColor color;
	CardRank rank;
	bool isLocked; //flag that tels if the card is well placed
	
	bool isFaceUp;
	cocos2d::CCTexture2D* faceTexture;
	cocos2d::CCTexture2D* backTexture;
	
	std::set<CardDelegate*> cardDelegates;
	
public:
	Card();
	virtual ~Card();
	
	static Card* cardWithColorAndRank(CardColor color, CardRank rank);
	virtual bool initWithColorAndRank(CardColor color, CardRank rank);
	virtual void setPosition(const cocos2d::CCPoint& pos);
	
	virtual void addCardDelegate(CardDelegate* delegate);
	virtual void removeCardDelegate(CardDelegate* delegate);
	
	CardColor getCardColor();
	CardRank getCardRank();
	bool getIsLocked();
	void setIsLocked(bool isLocked);

	virtual bool isNextToCard(Card* card);
	
	virtual bool getIsFaceUp();
	virtual void setIsFaceUp(bool isFaceUp);
};

#endif // __CARD_H__
