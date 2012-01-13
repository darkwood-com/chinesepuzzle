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

#import "cocos2d.h"
#include "CardDelegate.h"

typedef enum {
	CardTypeCard = 0x1,
	CardTypePlay = 0x2,
	CardTypeBoard = 0x4,
	CardTypeAll = 0x7,
} CardType;

class CC_DLL Card : public cocos2d::CCSprite
{
protected:
	std::set<CardDelegate*> cardDelegates;
	
public:
	Card();
	virtual ~Card();
	
	virtual void setPosition(const cocos2d::CCPoint& pos);
	
	virtual void addCardDelegate(CardDelegate* delegate);
	virtual void removeCardDelegate(CardDelegate* delegate);
	
	virtual CardType getType() { return CardTypeCard; }
	
	virtual void setTextureResolutionAndTheme(const char* resolution, const char* theme);
};

#endif // __CARD_H__
