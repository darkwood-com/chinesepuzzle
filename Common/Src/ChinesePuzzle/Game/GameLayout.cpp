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

#include <map>
#include <cmath>
#include <algorithm>

using namespace cocos2d;

template <class T> T* GameLayout::layoutRes(const char* key)
{
	static std::map<std::string, void*>* datas = NULL;
	
	if(!datas)
	{
		datas = new std::map<std::string, void*>();
		
		std::string sRes;
		
		/*
		 tmp : calc gridPosition : 
		 - x : ( width  - (cs.x + ss.x ) * 14 ) / 2
		 - y : ( height - (cs.y + ss.y ) * 8  ) / 2
		 
		 CCSize* cs = (CCSize*)(*datas)[sRes + "gridCardSize"];
		 CCSize* ss = (CCSize*)(*datas)[sRes + "gridSpaceSize"];
		 CCSize* gp = new CCSize(( 1730 - (cs->width  + ss->width  ) * 14 ) / 2,
								 ( 1080 - (cs->height + ss->height ) * 8  ) / 2);
		 CCLog("%f, %f", gp->width, gp->height);
		 */
		
		sRes = "480x320";
		(*datas)[sRes + "gridCardSize"] = new CCSize(26,36);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(4, 4);
		(*datas)[sRes + "gridPosition"] = new CCSize(4, 0);
		(*datas)[sRes + "newBtn.png"] = new CCPoint(450,290);
		(*datas)[sRes + "retryBtn.png"] = new CCPoint(450,170);
		(*datas)[sRes + "undoBtn.png"] = new CCPoint(450,240);
		(*datas)[sRes + "hintBtn.png"] = new CCPoint(450,190);
		(*datas)[sRes + "soundBtn.png"] = new CCPoint(450,220);
		(*datas)[sRes + "themeBtn.png"] = new CCPoint(450,140);
		
		sRes = "1024x768";
		(*datas)[sRes + "gridCardSize"] = new CCSize(56,78);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(10, 10);
		(*datas)[sRes + "gridPosition"] = new CCSize(10, 32);
		(*datas)[sRes + "newBtn.png"] = new CCPoint(977,714);
		(*datas)[sRes + "retryBtn.png"] = new CCPoint(977,582);
		(*datas)[sRes + "undoBtn.png"] = new CCPoint(977,450);
		(*datas)[sRes + "hintBtn.png"] = new CCPoint(977,318);
		(*datas)[sRes + "soundBtn.png"] = new CCPoint(977,186);
		(*datas)[sRes + "themeBtn.png"] = new CCPoint(977,56);
		
		sRes = "1680x1050";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(99, 55);
		(*datas)[sRes + "newBtn.png"] = new CCPoint(1590,960);
		(*datas)[sRes + "retryBtn.png"] = new CCPoint(1590,786);
		(*datas)[sRes + "undoBtn.png"] = new CCPoint(1590,612);
		(*datas)[sRes + "hintBtn.png"] = new CCPoint(1590,438);
		(*datas)[sRes + "soundBtn.png"] = new CCPoint(1590,264);
		(*datas)[sRes + "themeBtn.png"] = new CCPoint(1590,90);
		
		sRes = "1920x1080";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(214, 60);
		(*datas)[sRes + "newBtn.png"] = new CCPoint(1825,985);
		(*datas)[sRes + "retryBtn.png"] = new CCPoint(1825,807);
		(*datas)[sRes + "undoBtn.png"] = new CCPoint(1825,629);
		(*datas)[sRes + "hintBtn.png"] = new CCPoint(1825,451);
		(*datas)[sRes + "soundBtn.png"] = new CCPoint(1825,273);
		(*datas)[sRes + "themeBtn.png"] = new CCPoint(1825,95);
		
		sRes = "1920x1200";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(214, 120);
		(*datas)[sRes + "newBtn.png"] = new CCPoint(1825,1105);
		(*datas)[sRes + "retryBtn.png"] = new CCPoint(1825,903);
		(*datas)[sRes + "undoBtn.png"] = new CCPoint(1825,701);
		(*datas)[sRes + "hintBtn.png"] = new CCPoint(1825,499);
		(*datas)[sRes + "soundBtn.png"] = new CCPoint(1825,297);
		(*datas)[sRes + "themeBtn.png"] = new CCPoint(1825,95);
	}
	
	string sRes = game->getGameScene()->getConf()->getResolution();
	return reinterpret_cast<T*>((*datas)[sRes + key]);
}

void GameLayout::actionBtn(cocos2d::CCNode* btn)
{
	if(btn == newBtn)
	{
		game->getGameScene()->menuWithLayout(MenuLayout::TypeNewGame);
	}
	else if(btn == retryBtn)
	{
		game->getGameScene()->menuWithLayout(MenuLayout::TypeRetryGame);
	}
	else if(btn == undoBtn)
	{
		game->undoMove();
		game->getGameScene()->getConf()->save();
	}
	else if(btn == hintBtn)
	{
		game->getGameScene()->menuWithLayout(MenuLayout::TypeHint);
	}
	else if(btn == soundBtn)
	{
		GameConfig* gc = game->getGameScene()->getConf();
		
		CCTexture2D* pTexture = NULL;
		CCRect rect = CCRectZero;
		
		if(gc->getIsSoundOn()) {
			pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("soundOffBtn.png").c_str());
		} else {
			pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("soundOnBtn.png").c_str());
		}
		rect.size = pTexture->getContentSize();
		soundBtn->setTexture(pTexture);
		soundBtn->setTextureRect(rect);
		
		gc->setIsSoundOn(!gc->getIsSoundOn());
		gc->save();
	}
	else if(btn == themeBtn)
	{
		game->getGameScene()->menuWithLayout(MenuLayout::TypeTheme);
	}
}

GameLayout::GameLayout(Game* game) :
game(game),
bg(NULL),
newBtn(NULL),
retryBtn(NULL),
undoBtn(NULL),
hintBtn(NULL),
soundBtn(NULL),
themeBtn(NULL),
gridCardSize(CCSizeZero),
gridSpaceSize(CCSizeZero),
gridPosition(CCPointZero)
{
	activesBtn = CCArray::array();
	activesBtn->retain();
}

GameLayout::~GameLayout()
{
	activesBtn->release();
}

void GameLayout::layout(bool anim)
{
	GameConfig* gc = game->getGameScene()->getConf();
	
	gridCardSize = *this->layoutRes<CCSize>("gridCardSize");
	gridSpaceSize = *this->layoutRes<CCSize>("gridSpaceSize");
	gridPosition = *this->layoutRes<CCPoint>("gridPosition");
	
	CCTexture2D* pTexture = NULL;
	CCRect rect = CCRectZero;
	
	if(!bg)
	{
		bg = new CCSprite();
		bg->init();
		game->addChild(bg, GameZOrderBG);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("bg.png").c_str());
	rect.size = pTexture->getContentSize();
	bg->setTexture(pTexture);
	bg->setTextureRect(rect);
	bg->setPosition(ccp(0, 0));
	bg->setAnchorPoint(ccp(0, 0));
	
	if(!newBtn)
	{
		newBtn = new CCSprite();
		newBtn->init();
		game->addChild(newBtn, GameZOrderUI);
		activesBtn->addObject(newBtn);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("newBtn.png").c_str());
	rect.size = pTexture->getContentSize();
	newBtn->setTexture(pTexture);
	newBtn->setTextureRect(rect);
	newBtn->setPosition(*this->layoutRes<CCPoint>("newBtn.png"));
	newBtn->setScale(0.75f);
	
	if(!retryBtn)
	{
		retryBtn = new CCSprite();
		retryBtn->init();
		game->addChild(retryBtn, GameZOrderUI);
		activesBtn->addObject(retryBtn);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("retryBtn.png").c_str());
	rect.size = pTexture->getContentSize();
	retryBtn->setTexture(pTexture);
	retryBtn->setTextureRect(rect);
	retryBtn->setPosition(*this->layoutRes<CCPoint>("retryBtn.png"));
	retryBtn->setScale(0.75f);
	
	if(!undoBtn)
	{
		undoBtn = new CCSprite();
		undoBtn->init();
		game->addChild(undoBtn, GameZOrderUI);
		activesBtn->addObject(undoBtn);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("undoBtn.png").c_str());
	rect.size = pTexture->getContentSize();
	undoBtn->setTexture(pTexture);
	undoBtn->setTextureRect(rect);
	undoBtn->setPosition(*this->layoutRes<CCPoint>("undoBtn.png"));
	undoBtn->setScale(0.75f);
	
	if(!hintBtn)
	{
		hintBtn = new CCSprite();
		hintBtn->init();
		game->addChild(hintBtn, GameZOrderUI);
		activesBtn->addObject(hintBtn);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("hintBtn.png").c_str());
	rect.size = pTexture->getContentSize();
	hintBtn->setTexture(pTexture);
	hintBtn->setTextureRect(rect);
	hintBtn->setPosition(*this->layoutRes<CCPoint>("hintBtn.png"));
	hintBtn->setScale(0.75f);
	
	if(!soundBtn)
	{
		soundBtn = new CCSprite();
		soundBtn->init();
		game->addChild(soundBtn, GameZOrderUI);
		activesBtn->addObject(soundBtn);
	}
	if(gc->getIsSoundOn()) {
		pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("soundOnBtn.png").c_str());
	} else {
		pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("soundOffBtn.png").c_str());
	}
	rect.size = pTexture->getContentSize();
	soundBtn->setTexture(pTexture);
	soundBtn->setTextureRect(rect);
	soundBtn->setPosition(*this->layoutRes<CCPoint>("soundBtn.png"));
	soundBtn->setScale(0.75f);
	
	if(!themeBtn)
	{
		themeBtn = new CCSprite();
		themeBtn->init();
		game->addChild(themeBtn, GameZOrderUI);
		activesBtn->addObject(themeBtn);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(gc->getThemePath("themeBtn.png").c_str());
	rect.size = pTexture->getContentSize();
	themeBtn->setTexture(pTexture);
	themeBtn->setTextureRect(rect);
	themeBtn->setPosition(*this->layoutRes<CCPoint>("themeBtn.png"));
	themeBtn->setScale(0.75f);
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
											   CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameLayout::actionBtn)),
											   CCEaseOut::actionWithAction(CCScaleTo::actionWithDuration(0.1f, 0.75f), 2.0f),
											   NULL));
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
