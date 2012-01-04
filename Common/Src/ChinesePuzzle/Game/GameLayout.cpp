/**
 *  GameLayout.cpp
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

#include "GameLayout.h"
#include "Game.h"
#include "GameScene.h"

#include <cmath>
#include <algorithm>

using namespace cocos2d;

GameLayout::GameLayout(Game* game) :
game(game),
bg(NULL),
newBtn(NULL),
undoBtn(NULL),
hintBtn(NULL),
themeBtn(NULL),
gridCardSize(26,36),
gridSpaceSize(4, 4),
gridPosition(4, 0)
{
	activesBtn = CCArray::array();
	activesBtn->retain();
}

GameLayout::~GameLayout()
{
	activesBtn->release();
}

void GameLayout::layout()
{
	GameConfig* gc = game->getGameScene()->getConf();
	
	if(!bg)
	{
		bg = CCSprite::spriteWithFile(gc->getThemePath("bg.png").c_str());
		bg->setAnchorPoint(ccp(0,0));
		game->addChild(bg, GameZOrderBG);
	}
	
	if(!newBtn)
	{
		newBtn = CCSprite::spriteWithFile(gc->getThemePath("newBtn.png").c_str());
		newBtn->setPosition(ccp(450,290));
		newBtn->setScale(0.75f);
		game->addChild(newBtn, GameZOrderUI);
		activesBtn->addObject(newBtn);
	}
	
	if(!undoBtn)
	{
		undoBtn = CCSprite::spriteWithFile(gc->getThemePath("undoBtn.png").c_str());
		undoBtn->setPosition(ccp(450,240));
		undoBtn->setScale(0.75f);
		game->addChild(undoBtn, GameZOrderUI);
		activesBtn->addObject(undoBtn);
	}
	
	if(!hintBtn)
	{
		hintBtn = CCSprite::spriteWithFile(gc->getThemePath("hintBtn.png").c_str());
		hintBtn->setPosition(ccp(450,190));
		hintBtn->setScale(0.75f);
		game->addChild(hintBtn, GameZOrderUI);
		activesBtn->addObject(hintBtn);
	}
	
	if(!themeBtn)
	{
		themeBtn = CCSprite::spriteWithFile(gc->getThemePath("themeBtn.png").c_str());
		themeBtn->setPosition(ccp(450,140));
		themeBtn->setScale(0.75f);
		game->addChild(themeBtn, GameZOrderUI);
		activesBtn->addObject(themeBtn);
	}
}

bool GameLayout::tapDownAt(CCPoint location)
{
	CCObject* pObject;
	CCARRAY_FOREACH(activesBtn, pObject)
	{
		CCSprite* btn = (CCSprite*) pObject;
		CCPoint local = btn->convertToNodeSpace(location);
		CCRect r = btn->getTextureRect();
		r.origin = CCPointZero;
		
		if (CCRect::CCRectContainsPoint(r, local))
		{
			btn->runAction(CCSequence::actions(CCEaseIn::actionWithAction(CCScaleTo::actionWithDuration(0.1f, 1.0f), 2.0f),
											   CCEaseOut::actionWithAction(CCScaleTo::actionWithDuration(0.1f, 0.75f), 2.0f),
											   NULL));
			if(btn == newBtn)
			{
				game->getGameScene()->menuWithLayout(MenuLayout::TypeNewGame);
			}
			else if(btn == undoBtn)
			{
				
			}
			else if(btn == hintBtn)
			{
				
			}
			else if(btn == themeBtn)
			{
				game->getGameScene()->menuWithLayout(MenuLayout::TypeTheme);
			}
			
			return true;
		}
	}
	
	return false;
}

bool GameLayout::tapMoveAt(CCPoint location)
{
	return false;
}

bool GameLayout::tapUpAt(CCPoint location)
{
	return false;
}

CCPoint GameLayout::getPositionInBoardPoint(GridCoord coord)
{
	return ccp(gridPosition.x + (0.5f + coord.j) * (gridCardSize.width + gridSpaceSize.width),
			   gridPosition.y + (0.5f + coord.i) * (gridCardSize.height + gridSpaceSize.height));
}

GridCoord GameLayout::getPositionInGridCoord(CCPoint point)
{
	GridCoord coord;
	
	coord.i = std::floor((point.y - gridPosition.y - 0.5) / (gridCardSize.height + gridSpaceSize.height));
	coord.j = std::floor((point.x - gridPosition.x - 0.5) / (gridCardSize.width + gridSpaceSize.width));
	
	return coord;
}
