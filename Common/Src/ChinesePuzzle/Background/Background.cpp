/**
 *  Background.cpp
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

#include "Background.h"
#include "GameScene.h"

using namespace cocos2d;

Background::Background() : 
gs(NULL),
bgPattern(NULL)
{
	m_bIsRelativeAnchorPoint = true;
}

Background::~Background()
{
}

bool Background::init(GameSceneCommon* gs)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	ccTexParams texParams = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	bgPattern = CCSprite::spriteWithFile(gs->getConf()->getRootPath("bgPattern.png").c_str());
	bgPattern->getTexture()->setTexParameters(&texParams);
	bgPattern->setAnchorPoint(ccp(0,0));
	this->addChild(bgPattern, GameZOrderBG);
	
	this->gs = gs;
	this->setContentSize(this->gs->getConf()->getResolutionSize());
	
	return true;
}

void Background::setContentSize(const CCSize& size)
{
	CCLayer::setContentSize(size);
	
	CCRect rect;
	rect.size = size;
	
	bgPattern->setTextureRect(rect);
}