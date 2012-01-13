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
	cocos2d::CCTexture2D* emptyTexture;
	cocos2d::CCTexture2D* yesTexture;
	cocos2d::CCTexture2D* noTexture;
	
public:
	CardBoard();
	virtual ~CardBoard();
	
	static CardBoard* cardBoard();
	static CardBoard* cardBoardWithResolutionAndTheme(const char* resolution, const char* theme);
	virtual bool initCardBoard();
	virtual bool initCardBoardWithResolutionAndTheme(const char* resolution, const char* theme);
	
	CC_PROPERTY(CardBoardState, state, State);
	void setState(CardBoardState state, bool force);
	
	virtual CardType getType() { return CardTypeBoard; }
	virtual void setTextureResolutionAndTheme(const char* resolution, const char* theme);
};

#endif // __CARDBOARD_H__
