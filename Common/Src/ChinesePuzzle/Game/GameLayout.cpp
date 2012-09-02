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
		
		sRes = "480x320";
		(*datas)[sRes + "gridCardSize"] = new CCSize(26,36);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(4, 4);
		(*datas)[sRes + "gridPosition"] = new CCSize(4, 0);
		(*datas)[sRes + "newBtn"] = new CCPoint(451,290);
		(*datas)[sRes + "retryBtn"] = new CCPoint(451,238);
		(*datas)[sRes + "undoBtn"] = new CCPoint(451,186);
		(*datas)[sRes + "hintBtn"] = new CCPoint(451,134);
		(*datas)[sRes + "soundBtn"] = new CCPoint(451,82);
		(*datas)[sRes + "themeBtn"] = new CCPoint(451,30);
		
		sRes = "960x640";
		(*datas)[sRes + "gridCardSize"] = new CCSize(52,72);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(8, 8);
		(*datas)[sRes + "gridPosition"] = new CCSize(8, 0);
		(*datas)[sRes + "newBtn"] = new CCPoint(902,580);
		(*datas)[sRes + "retryBtn"] = new CCPoint(902,476);
		(*datas)[sRes + "undoBtn"] = new CCPoint(902,372);
		(*datas)[sRes + "hintBtn"] = new CCPoint(902,268);
		(*datas)[sRes + "soundBtn"] = new CCPoint(902,164);
		(*datas)[sRes + "themeBtn"] = new CCPoint(902,60);
		
		sRes = "1024x768";
		(*datas)[sRes + "gridCardSize"] = new CCSize(56,78);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(10, 10);
		(*datas)[sRes + "gridPosition"] = new CCSize(10, 32);
		(*datas)[sRes + "newBtn"] = new CCPoint(977,714);
		(*datas)[sRes + "retryBtn"] = new CCPoint(977,582);
		(*datas)[sRes + "undoBtn"] = new CCPoint(977,450);
		(*datas)[sRes + "hintBtn"] = new CCPoint(977,318);
		(*datas)[sRes + "soundBtn"] = new CCPoint(977,186);
		(*datas)[sRes + "themeBtn"] = new CCPoint(977,56);
		
		sRes = "1280x800";
		(*datas)[sRes + "gridCardSize"] = new CCSize(56,78);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(10, 10);
		(*datas)[sRes + "gridPosition"] = new CCSize(118, 48);
		(*datas)[sRes + "newBtn"] = new CCPoint(1220,740);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1220,604);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1220,468);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1220,332);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1220,196);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1220,60);
		
		sRes = "1280x1024";
		(*datas)[sRes + "gridCardSize"] = new CCSize(66,92);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(12, 12);
		(*datas)[sRes + "gridPosition"] = new CCSize(24, 96);
		(*datas)[sRes + "newBtn"] = new CCPoint(1210,952);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1210,776);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1210,600);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1210,424);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1210,248);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1210,72);
		
		sRes = "1366x768";
		(*datas)[sRes + "gridCardSize"] = new CCSize(56,78);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(10, 10);
		(*datas)[sRes + "gridPosition"] = new CCSize(158, 32);
		(*datas)[sRes + "newBtn"] = new CCPoint(1303,714);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1303,582);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1303,450);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1303,318);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1303,186);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1303,56);
		
		sRes = "1440x900";
		(*datas)[sRes + "gridCardSize"] = new CCSize(66,92);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(12, 12);
		(*datas)[sRes + "gridPosition"] = new CCSize(104, 34);
		(*datas)[sRes + "newBtn"] = new CCPoint(1370,830);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1370,678);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1370,526);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1370,374);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1370,222);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1370,70);
		
		sRes = "1680x1050";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(99, 45);
		(*datas)[sRes + "newBtn"] = new CCPoint(1590,960);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1590,786);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1590,612);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1590,438);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1590,264);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1590,90);
		
		sRes = "1920x1080";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(214, 60);
		(*datas)[sRes + "newBtn"] = new CCPoint(1825,985);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1825,807);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1825,629);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1825,451);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1825,273);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1825,95);
		
		sRes = "1920x1200";
		(*datas)[sRes + "gridCardSize"] = new CCSize(73,100);
		(*datas)[sRes + "gridSpaceSize"] = new CCSize(20, 20);
		(*datas)[sRes + "gridPosition"] = new CCSize(214, 120);
		(*datas)[sRes + "newBtn"] = new CCPoint(1825,1105);
		(*datas)[sRes + "retryBtn"] = new CCPoint(1825,903);
		(*datas)[sRes + "undoBtn"] = new CCPoint(1825,701);
		(*datas)[sRes + "hintBtn"] = new CCPoint(1825,499);
		(*datas)[sRes + "soundBtn"] = new CCPoint(1825,297);
		(*datas)[sRes + "themeBtn"] = new CCPoint(1825,95);
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
		GameConfigCommon* conf = game->getGameScene()->getConf();
		conf->setIsSoundOn(!conf->getIsSoundOn());
		conf->save();
		
		bool isSoundOn = conf->getIsSoundOn();
		game->getGameScene()->playBackgroundMusic(isSoundOn);
		if(isSoundOn)
		{
			conf->getNodeThemePath("soundOnBtn", soundBtn);
		}
		else
		{
			conf->getNodeThemePath("soundOffBtn", soundBtn);
		}
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
	GameConfigCommon* conf = game->getGameScene()->getConf();
	
	gridCardSize = *this->layoutRes<CCSize>("gridCardSize");
	gridSpaceSize = *this->layoutRes<CCSize>("gridSpaceSize");
	gridPosition = *this->layoutRes<CCPoint>("gridPosition");
	
	if(!bg)
	{
		bg = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(bg, GameZOrderBG);
	}
	conf->getNodeThemePath("bg", bg);
	bg->setPosition(ccp(0, 0));
	bg->setAnchorPoint(ccp(0, 0));
	
	if(!newBtn)
	{
		newBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(newBtn, GameZOrderUI);
		activesBtn->addObject(newBtn);
	}
	conf->getNodeThemePath("newBtn", newBtn);
	newBtn->setPosition(*this->layoutRes<CCPoint>("newBtn"));
	newBtn->setScale(0.75f);
	
	if(!retryBtn)
	{
		retryBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(retryBtn, GameZOrderUI);
		activesBtn->addObject(retryBtn);
	}
	conf->getNodeThemePath("retryBtn", retryBtn);
	retryBtn->setPosition(*this->layoutRes<CCPoint>("retryBtn"));
	retryBtn->setScale(0.75f);
	
	if(!undoBtn)
	{
		undoBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(undoBtn, GameZOrderUI);
		activesBtn->addObject(undoBtn);
	}
	conf->getNodeThemePath("undoBtn", undoBtn);
	undoBtn->setPosition(*this->layoutRes<CCPoint>("undoBtn"));
	undoBtn->setScale(0.75f);
	
	if(!hintBtn)
	{
		hintBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(hintBtn, GameZOrderUI);
		activesBtn->addObject(hintBtn);
	}
	conf->getNodeThemePath("hintBtn", hintBtn);
	hintBtn->setPosition(*this->layoutRes<CCPoint>("hintBtn"));
	hintBtn->setScale(0.75f);
	
	if(!soundBtn)
	{
		soundBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(soundBtn, GameZOrderUI);
		activesBtn->addObject(soundBtn);
	}
	if(conf->getIsSoundOn()) {
		conf->getNodeThemePath("soundOnBtn", soundBtn);
	} else {
		conf->getNodeThemePath("soundOffBtn", soundBtn);
	}
	soundBtn->setPosition(*this->layoutRes<CCPoint>("soundBtn"));
	soundBtn->setScale(0.75f);
	
	if(!themeBtn)
	{
		themeBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		game->addChild(themeBtn, GameZOrderUI);
		activesBtn->addObject(themeBtn);
	}
	conf->getNodeThemePath("themeBtn", themeBtn);
	themeBtn->setPosition(*this->layoutRes<CCPoint>("themeBtn"));
	themeBtn->setScale(0.75f);
}

bool GameLayout::tapDownAt(CCPoint location)
{
	CCObject* pObject;
	CCARRAY_FOREACH(activesBtn, pObject)
	{
		CCSprite* btn = (CCSprite*) pObject;
		CCPoint local = btn->convertToNodeSpace(location);
		CCRect r = btn->boundingBox();
		r.origin = CCPointZero;
		r.size = CCSizeMake(r.size.width * 2.0f, r.size.height * 2.0f);
		
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
