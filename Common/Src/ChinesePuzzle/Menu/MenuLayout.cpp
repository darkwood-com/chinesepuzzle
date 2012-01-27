/**
 *  MenuLayout.cpp
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

#include "MenuLayout.h"
#include "Menu.h"
#include "MenuGridContainer.h"
#include "MenuLabelContainer.h"
#include "GameScene.h"

using namespace cocos2d;

typedef enum  
{
	kMenuTagBg,
} kMenuTag;

template <class T> T* MenuLayout::layoutRes(const char* key)
{
	static std::map<std::string, void*>* datas = NULL;
	
	if(!datas)
	{
		datas = new std::map<std::string, void*>();
		
		std::string sRes;
		
		sRes = "480x320";
		(*datas)[sRes + "menuMask.png"] = new CCPoint(0,0);
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(200,200);
		
		sRes = "1920x1200";
		(*datas)[sRes + "menuMask.png"] = new CCPoint(0,0);
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
	}
	
	string sRes = menu->getGameScene()->getConf()->getResolution();
	return reinterpret_cast<T*>((*datas)[sRes + key]);
}

MenuLayout::MenuLayout(Menu* menu) :
menu(menu),
themes(NULL),
mBox(NULL),
miTheme(NULL)
{
}

MenuLayout::~MenuLayout()
{
	CC_SAFE_RELEASE(themes);
	CC_SAFE_RELEASE(mBox);
	CC_SAFE_RELEASE(miTheme);
}

bool MenuLayout::initWithType(Type type)
{
	this->type = type;
	
	return true;
}

void MenuLayout::layout()
{
	GameConfig* conf = menu->getGameScene()->getConf();
	CCPoint center = ccpMult(ccp(conf->getResolutionSize().width, conf->getResolutionSize().height), 0.5);
	
	if(!menu->getChildByTag(kMenuTagBg))
	{
		CCSprite* bg = CCSprite::spriteWithFile(conf->getUiPath("menuMask.png").c_str());
		bg->setAnchorPoint(*this->layoutRes<CCPoint>("menuMask.png"));
		menu->addChild(bg, 0, kMenuTagBg);
	}
	
	switch (this->type)
	{
		case TypeNewGame:
			if(!mBox)
			{
				MenuBox* mb = new MenuBox();
				mb->initWithResolutionAndContentSize(conf->getResolution().c_str(), *this->layoutRes<CCSize>("menuNewBoxSize"));
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("New game");
				
				CCArray* items = CCArray::array();
				
				CCLabelBMFont* itemTitle = CCLabelBMFont::labelWithString("Do you want start a new game?", conf->getFontPath("arial32.fnt").c_str());
				itemTitle->setAnchorPoint(ccp(0.5f, 0.5f));
				itemTitle->setPosition(*this->layoutRes<CCPoint>("menuNewTitle"));
				items->addObject(itemTitle);
				
				CCMenuItemImage* itemYes = CCMenuItemImage::itemFromNormalImage(conf->getUiPath("menuItemYes.png").c_str(), NULL, menu->getGameScene(), menu_selector(GameSceneCommon::newGame));
				itemYes->setAnchorPoint(ccp(0.5f, 0.5f));
				itemYes->setPosition(*this->layoutRes<CCPoint>("menuNewYes"));
				items->addObject(itemYes);
				
				CCMenuItemImage* itemNo = CCMenuItemImage::itemFromNormalImage(conf->getUiPath("menuItemNo.png").c_str(), NULL, menu, menu_selector(Menu::okMenu));
				itemNo->setAnchorPoint(ccp(0.5f, 0.5f));
				itemNo->setPosition(*this->layoutRes<CCPoint>("menuNewNo"));
				items->addObject(itemNo);
				
				mb->setItems(items);
				mb->layout();
				
				mBox =  mb;
			}
			
			menu->pushNav(mBox);
			break;
		case TypeRetryGame:
			if(!mBox)
			{
				MenuBox* mb = new MenuBox();
				mb->initWithResolutionAndContentSize(conf->getResolution().c_str(), *this->layoutRes<CCSize>("menuRetryBoxSize"));
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("Retry game");
				
				CCArray* items = CCArray::array();
				
				CCLabelBMFont* itemTitle = CCLabelBMFont::labelWithString("Do you want retry the game?", conf->getFontPath("arial32.fnt").c_str());
				itemTitle->setAnchorPoint(ccp(0.5f, 0.5f));
				itemTitle->setPosition(*this->layoutRes<CCPoint>("menuRetryTitle"));
				items->addObject(itemTitle);
				
				CCMenuItemImage* itemYes = CCMenuItemImage::itemFromNormalImage(conf->getUiPath("menuItemYes.png").c_str(), NULL, menu->getGameScene(), menu_selector(GameSceneCommon::retryGame));
				itemYes->setAnchorPoint(ccp(0.5f, 0.5f));
				itemYes->setPosition(*this->layoutRes<CCPoint>("menuRetryYes"));
				items->addObject(itemYes);
				
				CCMenuItemImage* itemNo = CCMenuItemImage::itemFromNormalImage(conf->getUiPath("menuItemNo.png").c_str(), NULL, menu, menu_selector(Menu::okMenu));
				itemNo->setAnchorPoint(ccp(0.5f, 0.5f));
				itemNo->setPosition(*this->layoutRes<CCPoint>("menuRetryNo"));
				items->addObject(itemNo);
				
				mb->setItems(items);
				mb->layout();
				
				mBox =  mb;
			}
			
			menu->pushNav(mBox);
			break;
		case TypeHint:
			if(!mBox)
			{
				MenuLabelContainer* mb = new MenuLabelContainer();
				mb->initWithResolutionAndContentSizeAndFntFile(conf->getResolution().c_str(), *this->layoutRes<CCSize>("menuHintBoxSize"), conf->getFontPath("arial32.fnt").c_str());
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setMargin(CCSizeMake(50, 50));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("Hint");
				mb->setString("Chinese Puzzle is a two-deck solitaire card game in which your memory and familiarity with the rules are tested to the limit. The game laid out in a tableau of eight rows. The goal is to move cards around in vacant spaces, so that all rows end up in a same family-colored and sorted order from Ace to King. Ace cards can only be moved at the first column, then you can fill the vacant space by drag and dropping one of the two card from same family color and next rank to the left card. Not clear? Just make some moves and play the game, but be careful with Kings!");
				mb->layout();
				
				mBox =  mb;
			}
			
			menu->pushNav(mBox);
			break;
		case TypeTheme:
			if(!themes)
			{
				themes = new CCMutableDictionary<std::string, cocos2d::CCMenuItemImage*>();
				themes->setObject(CCMenuItemImage::itemFromNormalImage(conf->getUiPath("menuItemThemeClassic.png").c_str(), NULL), "classic");
			}
			
			if(!mBox)
			{
				MenuGridContainer* mb = new MenuGridContainer();
				mb->initWithResolutionAndContentSize(conf->getResolution().c_str(), *this->layoutRes<CCSize>("menuThemeBoxSize"));
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setMargin(CCSizeMake(50, 50));
				mb->setGridSize(ccg(2, 2));
				mb->setPage(0);
				mb->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("Themes");
				
				CCArray* items = CCArray::array();
				
				std::vector<std::string> sTheme = themes->allKeys();
				for(std::vector<std::string>::iterator it = sTheme.begin(); it != sTheme.end(); ++it)
				{
					CCMenuItemImage* mItem = themes->objectForKey(*it);
					items->addObject(mItem);
				}
				
				mb->setItems(items);
				mb->layout();
				
				mBox =  mb;
			}
			
			menu->pushNav(mBox);
			break;
		case TypeNone:
			if(!mBox)
			{
				MenuBox* mb = new MenuBox();
				mb->initWithResolutionAndContentSize(conf->getResolution().c_str(), *this->layoutRes<CCSize>("menuNoneBoxSize"));
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("None");
				
				CCArray* items = CCArray::array();
				
				CCMenuItemFont* item = new CCMenuItemFont();
				item->initFromString("Exit menu", menu, menu_selector(Menu::okMenu));
				item->setAnchorPoint(ccp(0.5f, 0.5f));
				item->setPosition(ccp(0, 0));
				items->addObject(item);
				item->release();
				
				mb->setItems(items);
				mb->layout();
				
				mBox =  mb;
			}
			
			menu->pushNav(mBox);
		break;
	}
}