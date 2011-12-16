/**
 *  Game.cpp
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

#include "Game.h"
#include "GameControlChipmunk.h"
#include "GameControlSprite.h"
#include "GameScene.h"
#include "CardPlay.h"
#include "CardBoard.h"

using namespace cocos2d;

Game::Game() : 
gc(NULL),
gl(NULL),
conf(NULL),
dragCard(NULL)
{
}

Game::~Game()
{
	CC_SAFE_RELEASE(gc);
	CC_SAFE_RELEASE(gl);
	CC_SAFE_RELEASE(conf);
}

bool Game::init(GameScene* gs)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	//this->gc = new GameControlChipmunk();
	this->gc = new GameControlSprite();
	this->gl = new GameLayout(this);
	this->conf = new GameConfig();
	this->conf->init();
	this->gs = gs;
	this->setIsTouchEnabled(true);
	
	gl->layout();
	this->newGame();
	
	this->schedule(schedule_selector(Game::step));
	
	return true;
}

void Game::newGame()
{
	bool isFirstGame = (deck.size() == 0);
	if(isFirstGame)
	{
		//create deck
		std::vector<CardPlayColor> colors;
		colors.push_back(CardPlayColorSpade);
		colors.push_back(CardPlayColorClub);
		colors.push_back(CardPlayColorHeart);
		colors.push_back(CardPlayColorDiamond);
		
		std::vector<CardPlayRank> ranks;
		ranks.push_back(CardPlayRankAce);
		ranks.push_back(CardPlayRankTwo);
		ranks.push_back(CardPlayRankThree);
		ranks.push_back(CardPlayRankFour);
		ranks.push_back(CardPlayRankFive);
		ranks.push_back(CardPlayRankSix);
		ranks.push_back(CardPlayRankSeven);
		ranks.push_back(CardPlayRankEight);
		ranks.push_back(CardPlayRankNine);
		ranks.push_back(CardPlayRankTen);
		ranks.push_back(CardPlayRankJack);
		ranks.push_back(CardPlayRankQueen);
		ranks.push_back(CardPlayRankKing);
		
		for (int k = 0; k < 2; ++k)
		{
			for(std::vector<CardPlayColor>::const_iterator color = colors.begin(); color != colors.end(); ++color)
			{
				for(std::vector<CardPlayRank>::const_iterator rank = ranks.begin(); rank != ranks.end(); ++rank)
				{
					CardPlay* card = CardPlay::cardPlayWithColorAndRank(*color, *rank);
					deck.push_back(card);
				}
			}
		}
	}
	
	//assign random cards into the board
	int k = 0;
	std::random_shuffle(deck.begin(), deck.end());
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 14; ++j)
		{
			GridCoord coord;
			coord.i = i;
			coord.j = j;
			
			if(j == 0)
			{
				CardBoard* card = CardBoard::cardBoard();
				
				board[i][j] = card;
				
				//card position
				CCPoint coordPos = gl->getPositionInBoardPoint(coord);
				card->setPosition(coordPos);
				if(isFirstGame)
				{
					this->addChild(card, GameZOrderCard);
				}
			}
			else
			{
				CardPlay* card = deck[k++];
				card->setIsLocked(false);
				
				board[i][j] = card;
				
				//card position
				CCPoint coordPos = gl->getPositionInBoardPoint(coord);
				if(isFirstGame)
				{
					card->setPosition(coordPos);
					this->addChild(card, GameZOrderCard);
					gc->addCard(card);
				}
				
				//card animation
				CCArray* actions = CCArray::array();
				actions->addObject(CCDelayTime::actionWithDuration(0.05 * (7 - coord.i + coord.j - 1)));
				if(!CCPoint::CCPointEqualToPoint(card->getPosition(), coordPos))
				{
					actions->addObject(CCMoveTo::actionWithDuration(1.0f, coordPos));
				}
				if(!card->getIsFaceUp())
				{
					actions->addObject(CCOrbitCamera::actionWithDuration(0.1f, 1, 0, 0, 90, 0, 0));
					actions->addObject(CardPlayFlipAction::actionWithCardPlay(card));
					actions->addObject(CCOrbitCamera::actionWithDuration(0.1f, 1, 0, 270, 90, 0, 0));
				}
				card->runAction(CCSequence::actionsWithArray(actions));
			}
		}
	}
}

void Game::menu()
{
	//show menu
	gs->menu();
}

void Game::draw()
{
	CCLayer::draw();
	
	//debug game control draw
	gc->draw();
}

void Game::step(ccTime dt)
{
	//update game step
	gc->step(dt);
}

//input touches/mouse
void Game::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
}

void Game::tapDownAt(CCPoint location)
{
	if(gl->tapDownAt(location)) return;
	
	Card* tapCard = gc->getCard(location);
	if(tapCard && tapCard->getType() == CardTypePlay && !((CardPlay*)tapCard)->getIsLocked())
	{
		dragCardCoord = gl->getPositionInGridCoord(tapCard->getPosition());
		dragCard = (CardPlay*) tapCard;
		this->reorderChild(dragCard, GameZOrderMoveCard);
	}
	
    lastTouchLocation = location;
}

void Game::tapMoveAt(CCPoint location)
{
	if(gl->tapMoveAt(location)) return;
	
	CCPoint movePos = ccpAdd(location, ccpNeg(lastTouchLocation));
	
    if(dragCard)
    {
        dragCard->setPosition(ccpAdd(dragCard->getPosition(), movePos));
    }
    
    lastTouchLocation = location;
}

void Game::tapUpAt(CCPoint location)
{
	if(gl->tapUpAt(location)) return;
	
    if(dragCard)
    {
		//check drop
		GridCoord coord = gl->getPositionInGridCoord(location);
		
		/*
		if((0 <= coord.i && coord.i < 8 && 0 <= coord.j && coord.j < 14 && board[coord.i][coord.j] && board[coord.i][coord.j]->getType() == CardTypeBoard) && 
		   ((coord.j == 0 && dragCard->getCardRank() == CardRankAce) || (coord.j > 0 && board[coord.i][coord.j - 1] != NULL && dragCard->isNextToCard(board[coord.i][coord.j - 1]))))
		{
			//drop is valid : apply changes
			board[coord.i][coord.j] = board[dragCardCoord.i][dragCardCoord.j]; board[dragCardCoord.i][dragCardCoord.j] = NULL;
			dragCard->runAction(CCMoveTo::actionWithDuration(0.5, gl->getPositionInBoardPoint(coord)));
			
			//check and set lock for line cards
			for (int k = 0; k < 13; ++k)
			{
				if(k == 0 && board[coord.i][k]) board[coord.i][k]->setIsLocked(true);
				else if(board[coord.i][k - 1] && board[coord.i][k] && 
						board[coord.i][k - 1]->getIsLocked() && 
						board[coord.i][k]->isNextToCard(board[coord.i][k - 1])) board[coord.i][k]->setIsLocked(true);
			}
		}
		else
		{
			//drop is invalid : undo changes
			dragCard->runAction(CCMoveTo::actionWithDuration(0.5, gl->getPositionInBoardPoint(dragCardCoord)));
		}
		 */
		 
		this->reorderChild(dragCard, GameZOrderCard);
    }
    
    dragCard = NULL;
    lastTouchLocation = location;
}

bool Game::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint location = pTouch->locationInView(pTouch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	this->tapDownAt(location);
	return true;
}

void Game::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint location = pTouch->locationInView(pTouch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	this->tapMoveAt(location);
}

void Game::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint location = pTouch->locationInView(pTouch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	this->tapUpAt(location);
}

void Game::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint location = pTouch->locationInView(pTouch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	this->tapUpAt(location);
}