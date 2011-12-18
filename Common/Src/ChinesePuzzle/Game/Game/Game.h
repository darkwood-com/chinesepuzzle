/**
 *  Game.h
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

#ifndef __GAME_H__
#define __GAME_H__

#include "Card.h"
#include "GameControl.h"
#include "GameLayout.h"
#include "GameConfig.h"

class GameScene;
class CardPlay;
class CardBoard;

typedef enum {
	CheckMoveFrom,
	CheckMoveTo,
	CheckMoveToBefore,
	CheckMoveKo,
	CheckMoveOk,
} CheckMove;

// Game Layer
class Game : public cocos2d::CCLayer
{
protected:
	GameScene* gs; //scene parent
	
	std::vector<CardPlay*> deck; //deck cards
	Card* board[8][14]; //board game that reference to the deck cards
	
	GameControl* gc;
	GameLayout* gl;

    //input touches/mouse
    cocos2d::CCPoint lastTouchLocation;
	CardPlay* dragCard;
	GridCoord dragCardCoord;
	CardBoard* hintCard;
    CardBoard* switchBoardCard; //board card used for switch
	
public:
	Game();
	virtual ~Game();
	LAYER_NODE_FUNC_PARAM(Game, GameScene*, gs);
	
	virtual bool init(GameScene* gs);
	
	void newGame();
	void menu();
	void draw();
	void step(cocos2d::ccTime dt);
	
	Card* getCard(GridCoord coord);
	CheckMove checkMove(GridCoord from, GridCoord to); //check move for card from - to board coord
	int lockLine(int i); //update lock for a given grid line, return number of locked cards
	void hintTouch(cocos2d::CCPoint location); //hint with dragged/touched card
	
	//input touches/mouse
	virtual void registerWithTouchDispatcher();
	
	void tapDownAt(cocos2d::CCPoint location);
	void tapMoveAt(cocos2d::CCPoint location);
	void tapUpAt(cocos2d::CCPoint location);
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	
	CC_SYNTHESIZE_READONLY(GameConfig*, conf, Conf);
};

#endif // __GAME_H__
