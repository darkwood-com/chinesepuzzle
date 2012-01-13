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

class GameSceneCommon;
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
class CC_DLL Game : public cocos2d::CCLayer
{
protected:
	std::vector<CardPlay*> deck; //deck cards
	std::vector<CardBoard*> boardCards; //board cards
	Card* board[8][14]; //board game that reference to the deck cards
	
	GameControl* gc;
	GameLayout* gl;

    //input touches/mouse
    cocos2d::CCPoint lastTouchLocation;
	CardPlay* dragCard;
	GridCoord dragCardCoord;
	Card* touchLastCard; //visible hint last touched card, for semi-auto move
	CardBoard* hintCard; //card play hint on over card board
    CardBoard* switchBoardCard; //board card used for switch
	
	void makeMoveEnd(); //move end
	void hintMove(); //hint move
	
public:
	Game();
	virtual ~Game();
	LAYER_NODE_FUNC_PARAM(Game, GameSceneCommon*, gs);
	
	virtual bool init(GameSceneCommon* gs);
	
	void newGame();
	void draw();
	void step(cocos2d::ccTime dt);
	void layout();
	
	Card* getCard(GridCoord coord);
	CheckMove checkMoveCoord(GridCoord from, GridCoord to); //check move for coord from - to board
	CheckMove checkMoveCard(Card* from, Card* to); //check move for card from - to board
	CheckMove makeMoveCoord(GridCoord from, GridCoord to); //make move for coord from - to board
	CheckMove makeMoveCard(Card* from, Card* to); //make move for card from - to board
	int lockLine(int i); //update lock for a given grid line, return number of locked cards
	
	//input touches/mouse
	virtual void registerWithTouchDispatcher();
	
	void tapDownAt(cocos2d::CCPoint location);
	void tapMoveAt(cocos2d::CCPoint location);
	void tapUpAt(cocos2d::CCPoint location);
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	
	CC_SYNTHESIZE_READONLY(GameSceneCommon*, gs, GameScene);
};

#endif // __GAME_H__
