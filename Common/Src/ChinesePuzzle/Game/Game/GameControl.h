/**
 *  GameControl.h
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

#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include "cocos2d.h"
#include "CardDelegate.h"
#include "Card.h"

// GameControl
class GameControl : public cocos2d::CCObject, public CardDelegate
{
public:
	GameControl();
	virtual ~GameControl();
	
	virtual void step(cocos2d::ccTime dt);
	virtual void draw();
	
	virtual void addCard(Card* card); //add controls for this card
	virtual void removeCard(Card* card); //remove controls for this card
	virtual void updateCard(Card* card); //update card controls
	virtual Card* checkPoint(cocos2d::CCPoint p); //retrive a card from a location
	virtual Card* checkPointCard(Card* c); //retrive a card from a card
	virtual Card* checkRect(cocos2d::CCRect r, CardType filter); //retrive a card from a location
	virtual Card* checkRectCard(Card* c, CardType filter); //retrive a card from a card
};

#endif // __GAME_CONTROL_H__
