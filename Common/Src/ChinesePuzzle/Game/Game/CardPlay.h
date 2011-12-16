/**
 *  CardPlay.h
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

#ifndef __CARDPLAY_H__
#define __CARDPLAY_H__

#include "Card.h"

typedef enum {
	CardPlayColorSpade,
	CardPlayColorClub,
	CardPlayColorHeart,
	CardPlayColorDiamond
} CardPlayColor;

typedef enum {
	CardPlayRankAce,
	CardPlayRankTwo,
	CardPlayRankThree,
	CardPlayRankFour,
	CardPlayRankFive,
	CardPlayRankSix,
	CardPlayRankSeven,
	CardPlayRankEight,
	CardPlayRankNine,
	CardPlayRankTen,
	CardPlayRankJack,
	CardPlayRankQueen,
	CardPlayRankKing
} CardPlayRank;

class CardPlay;
class CC_DLL CardPlayFlipAction : public cocos2d::CCFiniteTimeAction
{
protected:
	CardPlay* cardPlay;
	
public:
	static CardPlayFlipAction* actionWithCardPlay(CardPlay* cardPlay);
	virtual bool initWithCardPlay(CardPlay* cardPlay);
	virtual void update(cocos2d::ccTime time);
	virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
};

class CC_DLL CardPlay : public Card
{
protected:
	CardPlayColor color;
	CardPlayRank rank;
	bool isLocked; //flag that tels if the CardPlay is well placed
	
	bool isFaceUp;
	cocos2d::CCTexture2D* faceTexture;
	cocos2d::CCTexture2D* backTexture;
	
public:
	CardPlay();
	virtual ~CardPlay();
	
	static CardPlay* cardPlayWithColorAndRank(CardPlayColor color, CardPlayRank rank);
	virtual bool initWithColorAndRank(CardPlayColor color, CardPlayRank rank);
	
	CardPlayColor getCardPlayColor();
	CardPlayRank getCardPlayRank();
	bool getIsLocked();
	void setIsLocked(bool isLocked);

	virtual bool isNextToCardPlay(CardPlay* CardPlay);
	
	virtual bool getIsFaceUp();
	virtual void setIsFaceUp(bool isFaceUp);
	
	virtual CardType getType() { return CardTypePlay; }
};

#endif // __CARDPLAY_H__
