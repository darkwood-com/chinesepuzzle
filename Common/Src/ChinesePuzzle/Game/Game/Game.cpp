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
#include "Card.h"
#include "GameControl.h"
#include "GameControlChipmunk.h"
#include "GameControlSprite.h"
#include "GameLayout.h"
#include "GameScene.h"

using namespace cocos2d;

Game::Game() : 
dragCard(NULL),
gc(NULL),
gl(NULL),
conf(NULL)
{
}

Game::~Game()
{
	CC_SAFE_DELETE(gc);
	CC_SAFE_DELETE(gl);
}

bool Game::init(GameScene* gs)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
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
	bool isFirstGame = deck.size() == 0;
	if(isFirstGame)
	{
		//create deck
		std::vector<CardColor> colors;
		colors.push_back(CardColorSpade);
		colors.push_back(CardColorClub);
		colors.push_back(CardColorHeart);
		colors.push_back(CardColorDiamond);
		
		std::vector<CardRank> ranks;
		ranks.push_back(CardRankAce);
		ranks.push_back(CardRankTwo);
		ranks.push_back(CardRankThree);
		ranks.push_back(CardRankFour);
		ranks.push_back(CardRankFive);
		ranks.push_back(CardRankSix);
		ranks.push_back(CardRankSeven);
		ranks.push_back(CardRankEight);
		ranks.push_back(CardRankNine);
		ranks.push_back(CardRankTen);
		ranks.push_back(CardRankJack);
		ranks.push_back(CardRankQueen);
		ranks.push_back(CardRankKing);
		
		for (int k = 0; k < 2; ++k)
		{
			for(std::vector<CardColor>::const_iterator color = colors.begin(); color != colors.end(); ++color)
			{
				for(std::vector<CardRank>::const_iterator rank = ranks.begin(); rank != ranks.end(); ++rank)
				{
					Card* card = Card::cardWithColorAndRank(*color, *rank);
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
			board[i][j] = NULL;
			
			if(j != 0)
			{
				GridCoord coord;
				coord.i = i;
				coord.j = j;
				
				Card* card = deck[k++];
				
				board[i][j] = card;
				card->setIsLocked(false);
				
				//card position
				CCPoint coordPos = gl->getPositionInBoardPoint(coord);
				if(isFirstGame)
				{
					card->setPosition(coordPos);
					this->addChild(card);
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
					actions->addObject(CardFlipAction::actionWithCard(card));
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
	
	gc->draw();
}

void Game::step(ccTime dt)
{
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
	if(tapCard && !tapCard->getIsLocked())
	{
		dragCardCoord = gl->getPositionInGridCoord(tapCard->getPosition());
		dragCard = tapCard;
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
		if((0 <= coord.i && coord.i < 8 && 0 <= coord.j && coord.j < 14 && board[coord.i][coord.j] == NULL) && 
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