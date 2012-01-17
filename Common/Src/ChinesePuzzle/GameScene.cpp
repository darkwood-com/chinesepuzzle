/**
 *  GameScene.cpp
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


#include "GameScene.h"

using namespace cocos2d;

GameSceneCommon::GameSceneCommon() :
conf(NULL)
{
	
}

GameSceneCommon::~GameSceneCommon()
{
	CC_SAFE_RELEASE(conf);
	CC_SAFE_RELEASE(pGame);
	CC_SAFE_RELEASE(pMenu);
}

bool GameSceneCommon::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	
	this->conf = new GameConfig();
	this->conf->init();
	
	pGame = NULL;
	pMenu = NULL;
	
	this->game();
	this->newGame(); //start a new game!!
	
	return true;
}

Game* GameSceneCommon::game()
{
	if(pMenu)
	{
		//remove menu when getting the game
		this->removeChild(pMenu, true);
		CC_SAFE_RELEASE_NULL(pMenu);
	}
	
	if (pGame == NULL)
	{
		pGame = Game::node(this);
		pGame->retain();
	}
	
	if(pGame->getParent() == NULL)
	{
		this->addChild(pGame, GameSceneZOrderGame);
	}
	
	return pGame;
}

Menu* GameSceneCommon::menu()
{
	return this->menuWithLayout(MenuLayout::TypeNone);
}

Menu* GameSceneCommon::menuWithLayout(MenuLayout::Type ml)
{
	if (pMenu == NULL)
	{
		MenuInit mi;
		mi.gs = this;
		mi.layout = ml;
		
		pMenu = Menu::node(mi);
		pMenu->retain();
	}
	
	if(pMenu->getParent() == NULL)
	{
		this->addChild(pMenu, GameSceneZOrderMenu);
	}
	
	return pMenu;
}

void GameSceneCommon::newGame()
{
	Game* aGame = this->game();
	aGame->newGame();
}

void GameSceneCommon::setResolution(const std::string& resolution)
{
	conf->setResolution(resolution);
	this->setContentSize(conf->getResolutionSize());
	
	this->game()->layout();
}

void GameSceneCommon::setTheme(const std::string& theme)
{
	
}
