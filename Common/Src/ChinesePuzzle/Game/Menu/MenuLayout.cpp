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
#include "MenuBoxContainer.h"
#include "GameScene.h"

using namespace cocos2d;

typedef enum  
{
	kMenuTagBg,
} kMenuTag;

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
	if(!menu->getChildByTag(kMenuTagBg))
	{
		CCSprite* bg = CCSprite::spriteWithFile((std::string("Data/ui/480x320/menuMask.png")).c_str());
		bg->setAnchorPoint(ccp(0,0));
		menu->addChild(bg, 0, kMenuTagBg);
	}
	
	switch (this->type)
	{
		case TypeTheme:
			if(!themes)
			{
				themes = new CCMutableDictionary<std::string, cocos2d::CCMenuItemImage*>();
				themes->setObject(CCMenuItemImage::itemFromNormalImage(std::string("Data/ui/480x320/menuItemTheme.png").c_str(), NULL), "default");
			}
			
			if(!mBox)
			{
				MenuBoxContainer* mb = new MenuBoxContainer();
				mb->initWithContentSize(CCSizeMake(200, 200));
				mb->setPosition(ccp(100, 50));
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
		case TypeNewGame:
			if(!mBox)
			{
				MenuBox* mb = new MenuBox();
				mb->initWithContentSize(CCSizeMake(200, 200));
				mb->setPosition(ccp(100, 50));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("None");
				
				CCArray* items = CCArray::array();
				
				CCMenuItemFont* itemTitle = CCMenuItemFont::itemFromString("Do you want start\na new game?");
				itemTitle->setAnchorPoint(ccp(0.5f, 0.5f));
				itemTitle->setPosition(ccp(100, 100));
				items->addObject(itemTitle);
				
				CCMenuItemImage* itemYes = CCMenuItemImage::itemFromNormalImage("Data/ui/480x320/menuItemYes.png", NULL, menu->getGameScene(), menu_selector(GameScene::newGame));
				itemYes->setAnchorPoint(ccp(0.5f, 0.5f));
				itemYes->setPosition(ccp(150, 50));
				items->addObject(itemYes);
				
				CCMenuItemImage* itemNo = CCMenuItemImage::itemFromNormalImage("Data/ui/480x320/menuItemNo.png", NULL, menu, menu_selector(Menu::okMenu));
				itemNo->setAnchorPoint(ccp(0.5f, 0.5f));
				itemNo->setPosition(ccp(50, 50));
				items->addObject(itemNo);
				
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
				mb->initWithContentSize(CCSizeMake(200, 200));
				mb->setPosition(ccp(100, 50));
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