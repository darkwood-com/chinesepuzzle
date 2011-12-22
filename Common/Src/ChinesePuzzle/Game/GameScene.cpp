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

GameScene::GameScene()
{
	
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(pGame);
	CC_SAFE_RELEASE(pMenu);
}

bool GameScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	
	pGame = NULL;
	pMenu = NULL;
	
	this->game();
	
	return true;
}

Game* GameScene::game()
{
	if(pMenu)
	{
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
		this->addChild(pGame);
	}
	
	return pGame;
}

Menu* GameScene::menu()
{
	return this->menuWithLayout(MenuLayout::TypeNone);
}

Menu* GameScene::menuWithLayout(MenuLayout::Type ml)
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
		this->addChild(pMenu);
	}
	
	return pMenu;
}

void GameScene::newGame()
{
	Game* aGame = this->game();
	aGame->newGame();
}
