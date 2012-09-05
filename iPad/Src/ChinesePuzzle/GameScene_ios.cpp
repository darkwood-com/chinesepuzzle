/**
 *  GameScene_ios.cpp
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

#include "GameScene_ios.h"
#include "Game.h"
#include "GameScene.h"

using namespace cocos2d;

GameScene::GameScene()
{
	m_bIsRelativeAnchorPoint = true;
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
	
	this->layout();
	this->ccReshape();
	
	return true;
}

void GameScene::layout(bool anim)
{
	GameSceneCommon::layout(anim);
	
	CCSize confsize = conf->getResolutionSize();
	CCPoint confcenter = ccpMult(ccp(confsize.width, confsize.height), 0.5);
	
	this->setContentSize(confsize);
}

void GameScene::ccReshape()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCPoint wincenter = ccpMult(ccp(winsize.width, winsize.height), 0.5);

	this->setPosition(wincenter);
}
