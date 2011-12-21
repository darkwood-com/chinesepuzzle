/**
 *  GameControlSprite.h
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

#ifndef __GAME_CONTROL_SPRITE_H__
#define __GAME_CONTROL_SPRITE_H__

#include "GameControl.h"

typedef std::set<Card*> CardSpriteSet;

class GameControlSprite : public GameControl
{
protected:
	CardSpriteSet cards;
	
public:
	GameControlSprite();
	virtual ~GameControlSprite();
	
	virtual void step(cocos2d::ccTime dt);
	virtual void draw();
	
	virtual void addCard(Card* card);
	virtual void removeCard(Card* card);
	virtual void updateCard(Card* card);
	virtual Card* checkPoint(cocos2d::CCPoint p);
	virtual Card* checkPointCard(Card* c);
	virtual Card* checkRect(cocos2d::CCRect r, CardType filter);
	virtual Card* checkRectCard(Card* c, CardType filter);
};

#endif // __GAME_CONTROL_SPRITE_H__
