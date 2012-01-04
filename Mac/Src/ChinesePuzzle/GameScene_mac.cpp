/**
 *  GameScene_mac.cpp
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

#include "GameScene_mac.h"
#include "Game.h"
#include "GameScene.h"

using namespace cocos2d;

GameScene::GameScene() :
bgPattern(NULL)
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	if (!GameSceneCommon::init())
	{
		return false;
	}
	
	ccTexParams texParams = {GL_LINEAR,GL_LINEAR,GL_REPEAT ,GL_REPEAT};
	bgPattern = CCSprite::spriteWithFile(conf->getRootPath("bgPattern.png").c_str());
	bgPattern->getTexture()->setTexParameters(&texParams);
	bgPattern->setAnchorPoint(ccp(0,0));
	this->addChild(bgPattern, GameZOrderBG);
	
	ccReshape();
	
	return true;
}

void GameScene::ccReshape()
{
	CCRect rect;
	rect.size = CCDirector::sharedDirector()->getWinSize();
	
	//this->setPosition(CCPointMake(50, 50));
	
	CCLog("toto reshape scene");
	
	bgPattern->setTextureRect(rect);
}
