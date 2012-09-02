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
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

typedef enum {
	BGMusicThemeNone,
	BGMusicTheme1,
	BGMusicTheme2,
	BGMusicTheme3,
} BGMusicTheme;

GameSceneCommon::GameSceneCommon() :
conf(NULL),
bgMusicTheme(BGMusicThemeNone)
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
	this->conf->load();
	
	playBackgroundMusic(this->conf->getIsSoundOn());
	
	pGame = NULL;
	pMenu = NULL;
	
	this->game();
	
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
	
	playSound("shuffle");
}

void GameSceneCommon::retryGame()
{
	Game* aGame = this->game();
	aGame->retryGame();
	
	playSound("shuffle");
}

void GameSceneCommon::setResolution(const std::string& resolution)
{
	conf->setResolution(resolution);
	this->setContentSize(conf->getResolutionSize());
	
	this->layout(false);
	conf->save();
}

void GameSceneCommon::setTheme(const std::string& theme)
{
	conf->setTheme(theme);
	this->layout();
	
	conf->save();
}

void GameSceneCommon::playSound(const char* soundName)
{
	SimpleAudioEngine* audio = SimpleAudioEngine::sharedEngine();
	
	if(conf->getIsSoundOn())
	{
		std::string soundPath = "sound/";
		audio->playEffect((soundPath + soundName + ".caf").c_str());
	}
}

void GameSceneCommon::playBackgroundMusic(bool play)
{
	SimpleAudioEngine* audio = SimpleAudioEngine::sharedEngine();
	
	if(play && conf->getIsSoundOn())
	{
		audio->setBackgroundMusicVolume(0.5f);
		switch(bgMusicTheme)
		{
			case BGMusicThemeNone:
			case BGMusicTheme3: audio->playBackgroundMusic("sound/bgm1.caf", true); bgMusicTheme = BGMusicTheme1; break;
			case BGMusicTheme1: audio->playBackgroundMusic("sound/bgm2.caf", true); bgMusicTheme = BGMusicTheme2; break;
			case BGMusicTheme2: audio->playBackgroundMusic("sound/bgm3.caf", true); bgMusicTheme = BGMusicTheme3; break;
		}
	}
	else if(bgMusicTheme != BGMusicThemeNone)
	{
		audio->stopBackgroundMusic();
	}
}

void GameSceneCommon::layout(bool anim)
{
	if(pGame) pGame->layout(anim);
	if(pMenu) pMenu->layout(anim);
}
