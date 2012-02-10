/**
 *  CardBoard.h
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

#ifndef __CARDBOARD_H__
#define __CARDBOARD_H__

#include "Card.h"

typedef enum {
	CardBoardEmpty,
	CardBoardYes,
	CardBoardNo,
} CardBoardState;

class CC_DLL CardBoard : public Card
{
protected:
	cocos2d::CCSpriteBatchNode* emptySprite;
	cocos2d::CCSpriteBatchNode* yesSprite;
	cocos2d::CCSpriteBatchNode* noSprite;
	
public:
	CardBoard();
	virtual ~CardBoard();
	
	static CardBoard* cardBoardWithConf(GameConfigCommon* conf);
	virtual bool initCardBoardWithConf(GameConfigCommon* conf);
	
	CC_PROPERTY(CardBoardState, state, State);
	void setState(CardBoardState state, bool force);
	
	virtual void setConf(GameConfigCommon* conf);
};

#endif // __CARDBOARD_H__
