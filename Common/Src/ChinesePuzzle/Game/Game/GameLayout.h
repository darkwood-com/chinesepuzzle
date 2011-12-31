/**
 *  GameLayout.h
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

#ifndef __GAME_LAYOUT_H__
#define __GAME_LAYOUT_H__

#import "cocos2d.h"

class Game;

struct GridCoord {
	int i;
	int j;
};

typedef enum {
	GameZOrderBG = 0,
	GameZOrderUI = 1,
	GameZOrderBoard = 2,
	GameZOrderCard = 3,
	GameZOrderMoveCard = 4,
	GameZOrderHintCard = 5,
} GameZOrder;

// GameLayout Layer
class CC_DLL GameLayout : public cocos2d::CCObject
{
protected:
	Game* game;
	cocos2d::CCArray* activesBtn;
	bool isLayout;
	
	cocos2d::CCSprite* bg;
	
	//button layout
	cocos2d::CCSprite* newBtn;
	cocos2d::CCSprite* hintBtn;
	cocos2d::CCSprite* undoBtn;
	cocos2d::CCSprite* themeBtn;
	
	//card grid layout stuff
	cocos2d::CCSize gridCardSize;
	cocos2d::CCSize gridSpaceSize;
	cocos2d::CCPoint gridPosition;
	
public:
	GameLayout(Game* game);
	virtual ~GameLayout();
	
	void layout();
	
	bool tapDownAt(cocos2d::CCPoint location);
	bool tapMoveAt(cocos2d::CCPoint location);
	bool tapUpAt(cocos2d::CCPoint location);
	
	cocos2d::CCPoint getPositionInBoardPoint(GridCoord coord);
	GridCoord getPositionInGridCoord(cocos2d::CCPoint point);
};

#endif // __GAME_LAYOUT_H__
