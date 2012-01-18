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

#include <algorithm>

using namespace cocos2d;

Game::Game() : 
gs(NULL),
gc(NULL),
gl(NULL),
dragCard(NULL),
hintCard(NULL),
switchBoardCard(NULL),
touchLastCard(NULL)
{
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 14; ++j)
		{
			board[i][j] = NULL;
		}
	}
}

Game::~Game()
{
	CC_SAFE_RELEASE(gc);
	CC_SAFE_RELEASE(gl);
}

bool Game::init(GameSceneCommon* gs)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	this->gs = gs;
	//this->gc = new GameControlChipmunk();
	this->gc = new GameControlSprite();
	this->gl = new GameLayout(this);
	this->setIsTouchEnabled(true);
	
	this->layout();
	
	this->schedule(schedule_selector(Game::step));
	
	return true;
}

void Game::newGame()
{
	bool isFirstGame = (deck.size() == 0);
	if(isFirstGame)
	{
		GameConfig* conf = gs->getConf();
		
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
					CardPlay* card = CardPlay::cardBoardWithResolutionAndThemeAndColorAndRank(conf->getResolution().c_str(),
																							  conf->getTheme().c_str(),
																							  *color,
																							  *rank);
					this->addChild(card, GameZOrderCard);
					gc->addCard(card);
					deck.push_back(card);
				}
			}
		}
		
		switchBoardCard = CardBoard::cardBoardWithResolutionAndTheme(conf->getResolution().c_str(), conf->getTheme().c_str());
		switchBoardCard->setIsVisible(false);
		this->addChild(switchBoardCard, GameZOrderBoard);
		
		for (int l = 0; l < 8; ++l)
		{
			CardBoard* card = CardBoard::cardBoardWithResolutionAndTheme(conf->getResolution().c_str(), conf->getTheme().c_str());
			this->addChild(card, GameZOrderCard);
			gc->addCard(card);
			boardCards.push_back(card);
		}
		
		touchLastCard = new Card();
		touchLastCard->initWithFile(gs->getConf()->getThemePath("cardtouched.png").c_str());
		touchLastCard->setIsVisible(false);
		this->addChild(touchLastCard, GameZOrderHintCard);
		touchLastCard->release();
	}
	
	//assign random cards into the board
	int k = 0, l = 0;
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
				CardBoard* card = boardCards[l++];
				
				board[i][j] = card;
				
				//card position
				CCPoint coordPos = gl->getPositionInBoardPoint(coord);
				card->setPosition(coordPos);
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
	
	moves.clear();
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

void Game::layout()
{
	gl->layout();

	GameConfig* conf = gs->getConf();
	
	if(touchLastCard)
	{
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(conf->getThemePath("cardtouched.png").c_str());
		if (pTexture)
		{
			CCRect rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			touchLastCard->setTexture(pTexture);
			touchLastCard->setTextureRect(rect);
		}
	}
	
	if(switchBoardCard)
	{
		switchBoardCard->setTextureResolutionAndTheme(conf->getResolution().c_str(), conf->getTheme().c_str());
	}
	
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 14; ++j)
		{
			GridCoord coord;
			coord.i = i;
			coord.j = j;
			
			Card* card = board[i][j];
			if(card)
			{
				card->setTextureResolutionAndTheme(conf->getResolution().c_str(), conf->getTheme().c_str());
				card->setPosition(gl->getPositionInBoardPoint(coord));
			}
		}
	}
}

Card* Game::getCard(GridCoord coord)
{
	return (0 <= coord.i && coord.i < 8 && 0 <= coord.j && coord.j < 14) ? board[coord.i][coord.j] : NULL;
}

CheckMove Game::checkMoveCoord(const MoveCoord& move)
{
	Card* cFromCard = this->getCard(move.from);
	if(cFromCard == NULL || cFromCard->getType() != CardTypePlay) return CheckMoveFrom;
	CardPlay* cFrom = (CardPlay*) cFromCard;
	
	Card* cToCard = this->getCard(move.to);
	if(cToCard == NULL || cToCard->getType() != CardTypeBoard) return CheckMoveTo;
	
	GridCoord toBefore = move.to; toBefore.j--;
	if(toBefore.j == -1)
	{
		if(cFrom->getRank() == CardPlayRankAce) return CheckMoveOk;
		else return CheckMoveKo;
	}
	else
	{
		Card* cToBeforeCard = this->getCard(toBefore);
		if(cToBeforeCard == NULL || cToBeforeCard->getType() != CardTypePlay) return CheckMoveToBefore;
		CardPlay* cToBefore = (CardPlay*) cToBeforeCard;
		
		if(cFrom->isNextToCardPlay(cToBefore)) return CheckMoveOk;
		else return CheckMoveKo;
	}
}

CheckMove Game::checkMoveCard(Card* from, Card* to)
{
	MoveCoord move;
	move.from = gl->getPositionInGridCoord(from->getPosition());
	move.to = gl->getPositionInGridCoord(to->getPosition());
	return this->checkMoveCoord(move);
}

CheckMove Game::makeMoveCoord(const MoveCoord& move)
{
	CheckMove check = this->checkMoveCoord(move);
	
	Card* cFrom = this->getCard(move.from);
	if(check == CheckMoveOk)
	{
		//drop is valid : apply changes and switch
		Card* cSwitch = this->getCard(move.to);
		board[move.to.i][move.to.j] = board[move.from.i][move.from.j];
		board[move.from.i][move.from.j] = cSwitch;
		cFrom->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.5, gl->getPositionInBoardPoint(move.to)),
												CCCallFunc::actionWithTarget(this, callfunc_selector(Game::makeMoveEnd)),
												NULL));
		if(cSwitch)
		{
			cSwitch->setPosition(gl->getPositionInBoardPoint(move.from));
			if(cSwitch->getType() == CardTypeBoard)
			{
				((CardBoard*) cSwitch)->setState(CardBoardEmpty);
			}
		}
		switchBoardCard->setPosition(gl->getPositionInBoardPoint(move.to));
		
		//check and set lock for line cards
		this->lockLine(move.to.i);
		
		moves.push_back(move);
	}
	else if(cFrom)
	{
		//drop is invalid : undo changes
		cFrom->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.5, gl->getPositionInBoardPoint(move.from)),
											 CCCallFunc::actionWithTarget(this, callfunc_selector(Game::makeMoveEnd)),
											 NULL));
	}
	else
	{
		this->makeMoveEnd();
	}
	
	return check;
}

CheckMove Game::makeMoveCard(Card* from, Card* to)
{
	MoveCoord move;
	move.from = gl->getPositionInGridCoord(from->getPosition());
	move.to = gl->getPositionInGridCoord(to->getPosition());
	return this->makeMoveCoord(move);
}

void Game::makeMoveEnd()
{
	switchBoardCard->setIsVisible(false);
	
	if(dragCard)
	{
		this->reorderChild(dragCard, GameZOrderCard);
		dragCard = NULL;
		this->hintMove();
	}
}

void Game::hintMove()
{
	if(this->dragCard)
	{
		//check drop
		Card* cToCard = gc->checkRectCard(dragCard, CardTypeBoard);
		if(cToCard != NULL && cToCard->getType() == CardTypeBoard)
		{
			CardBoard* cTo = (CardBoard*) cToCard;
			if(hintCard && hintCard != cTo)
			{
				hintCard->setState(CardBoardEmpty);
			}
			hintCard = cTo;
			
			GridCoord coord = gl->getPositionInGridCoord(cToCard->getPosition());
			MoveCoord move = {dragCardCoord, coord};
			if(this->checkMoveCoord(move) == CheckMoveOk)
			{
				hintCard->setState(CardBoardYes);
			}
			else
			{
				hintCard->setState(CardBoardNo);
			}
		}
		else if(hintCard)
		{
			hintCard->setState(CardBoardEmpty);
			hintCard = NULL;
		}
	}
	else if(hintCard)
	{
		hintCard->setState(CardBoardEmpty);
		hintCard = NULL;
	}
}

void Game::undoMove()
{
	if(moves.size() == 0) return;
	MoveCoord move = moves.back();
	
	//drop is valid : apply changes and switch
	Card* cTo = this->getCard(move.to);
	Card* cSwitch = this->getCard(move.from);
	board[move.from.i][move.from.j] = board[move.to.i][move.to.j];
	board[move.to.i][move.to.j] = cSwitch;
	cTo->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.5, gl->getPositionInBoardPoint(move.from)),
									   CCCallFunc::actionWithTarget(this, callfunc_selector(Game::makeMoveEnd)),
									   NULL));
	if(cSwitch)
	{
		cSwitch->setPosition(gl->getPositionInBoardPoint(move.to));
		if(cSwitch->getType() == CardTypeBoard)
		{
			((CardBoard*) cSwitch)->setState(CardBoardEmpty);
		}
	}
	switchBoardCard->setPosition(gl->getPositionInBoardPoint(move.from));
	switchBoardCard->setIsVisible(true);
	
	//check and set lock for line cards
	this->lockLine(move.from.i);
	this->lockLine(move.to.i);
	
	moves.pop_back();
}

int Game::lockLine(int i)
{
	if(!(0 <= i && i < 8)) return 0;
	
	int nb = 0;
	
	for (int j = 0; j < 14; ++j)
	{
		Card* cCard = board[i][j];
		if(cCard == NULL || cCard->getType() != CardTypePlay) continue;
		CardPlay* c = (CardPlay*) cCard;
		
		Card* cCardBefore = (j == 0) ? NULL : board[i][j - 1];
		CardPlay* cBefore = NULL;
		if(cCardBefore != NULL && cCardBefore->getType() == CardTypePlay)
		{
			cBefore = (CardPlay*) cCardBefore;
		}
		
		if((j == 0 && c->getRank() == CardPlayRankAce) ||
		   (cBefore && cBefore->getIsLocked() && c->isNextToCardPlay(cBefore)))
		{
			c->setIsLocked(true);
			nb++;
		}
		else
		{
			c->setIsLocked(false);
		}
	}
	
	return nb;
}

//input touches/mouse
void Game::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
}

void Game::tapDownAt(CCPoint location)
{
	if(gl->tapDownAt(location)) return;
	
	if(!dragCard)
    {
		Card* tapCard = gc->checkPoint(location);
		if(tapCard)
		{
			if(touchLastCard->getIsVisible())
			{
				if(this->checkMoveCard(touchLastCard, tapCard) == CheckMoveOk)
				{
					switchBoardCard->setPosition(touchLastCard->getPosition());
					switchBoardCard->setIsVisible(true);
					this->makeMoveCard(touchLastCard, tapCard);
				}
			}
			else if(tapCard->getType() == CardTypePlay && !((CardPlay*)tapCard)->getIsLocked())
			{
				dragCardCoord = gl->getPositionInGridCoord(tapCard->getPosition());
				dragCard = (CardPlay*) tapCard;
				CCPoint dragCardPos = gl->getPositionInBoardPoint(dragCardCoord);
				
				switchBoardCard->setPosition(dragCardPos);
				switchBoardCard->setIsVisible(true);
				touchLastCard->setPosition(dragCardPos);
				
				this->reorderChild(dragCard, GameZOrderMoveCard);
			}
		}
		
		touchLastCard->setIsVisible(false);
	}
	
	this->hintMove();
    lastTouchLocation = location;
}

void Game::tapMoveAt(CCPoint location)
{
	if(gl->tapMoveAt(location)) return;
	
	touchLastCard->setIsVisible(false);

	CCPoint movePos = ccpAdd(location, ccpNeg(lastTouchLocation));
	if(dragCard)
    {
        dragCard->setPosition(ccpAdd(dragCard->getPosition(), movePos));
    }
    
	this->hintMove();
	lastTouchLocation = location;
}

void Game::tapUpAt(CCPoint location)
{
	if(gl->tapUpAt(location)) return;
	
    if(dragCard)
    {
		//check drop
		Card* cToCard = gc->checkRectCard(dragCard, CardTypeBoard);
		if(cToCard == NULL || cToCard->getType() != CardTypeBoard)
		{
			cToCard = dragCard;
		}
		GridCoord coord = gl->getPositionInGridCoord(cToCard->getPosition());
		MoveCoord move = {dragCardCoord, coord};
		CheckMove check = this->makeMoveCoord(move);
		if(check != CheckMoveOk && CCPoint::CCPointEqualToPoint(dragCard->getPosition(), touchLastCard->getPosition()))
		{
			touchLastCard->setIsVisible(true);
		}
    }
    
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