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
	
	switch (this->type) {
		case TypeTheme:
			if(!themes)
			{
				themes = new CCMutableDictionary<std::string, cocos2d::CCMenuItemImage*>();
				themes->setObject(CCMenuItemImage::itemFromNormalImage(std::string("Data/ui/480x320/menuItemTheme.png").c_str(), NULL), "default");
			}
			
			if(!mBox)
			{
				mBox = new MenuBox();
				mBox->initWithContentSize(CCSizeMake(200, 200));
				mBox->setPosition(ccp(100, 50));
				mBox->setMargin(CCSizeMake(50, 50));
				mBox->setGridSize(ccg(2, 2));
				mBox->setPage(0);
				mBox->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
				mBox->setOkTarget(menu, menu_selector(Menu::okMenu));
				
				CCString* mBoxTitle = new CCString("Themes");
				mBox->setTitle(mBoxTitle);
				mBoxTitle->release();
				
				CCArray* items = CCArray::array();
				
				std::vector<std::string> sTheme = themes->allKeys();
				for(std::vector<std::string>::iterator it = sTheme.begin(); it != sTheme.end(); ++it)
				{
					CCMenuItemImage* mItem = themes->objectForKey(*it);
					items->addObject(mItem);
				}
				
				mBox->setItems(items);
			}
			
			menu->pushNav(mBox);
		break;
		case TypeNewGame:
			if(!mBox)
			{
				mBox = new MenuBox();
				mBox->initWithContentSize(CCSizeMake(200, 200));
				mBox->setPosition(ccp(100, 50));
				mBox->setMargin(CCSizeMake(50, 50));
				mBox->setGridSize(ccg(1, 1));
				mBox->setPage(0);
				mBox->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
				mBox->setOkTarget(menu, menu_selector(Menu::okMenu));
				
				CCString* mBoxTitle = new CCString("None");
				mBox->setTitle(mBoxTitle);
				mBoxTitle->release();
				
				CCArray* items = CCArray::array();
				
				CCMenuItemFont* item = new CCMenuItemFont();
				item->initFromString("exit menu", menu, menu_selector(Menu::okMenu));
				item->setAnchorPoint(ccp(0.5f, 0.5f));
				item->setPosition(ccp(240, 160));
				items->addObject(item);
				item->release();
				
				mBox->setItems(items);
			}
			
			menu->pushNav(mBox);
		break;
		case TypeNone:
			if(!mBox)
			{
				mBox = new MenuBox();
				mBox->initWithContentSize(CCSizeMake(200, 200));
				mBox->setPosition(ccp(100, 50));
				mBox->setMargin(CCSizeMake(50, 50));
				mBox->setGridSize(ccg(1, 1));
				mBox->setPage(0);
				mBox->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
				mBox->setOkTarget(menu, menu_selector(Menu::okMenu));
				
				CCString* mBoxTitle = new CCString("None");
				mBox->setTitle(mBoxTitle);
				mBoxTitle->release();
				
				CCArray* items = CCArray::array();
				
				CCMenuItemFont* item = new CCMenuItemFont();
				item->initFromString("exit menu", menu, menu_selector(Menu::okMenu));
				item->setAnchorPoint(ccp(0.5f, 0.5f));
				item->setPosition(ccp(240, 160));
				items->addObject(item);
				item->release();
				
				mBox->setItems(items);
			}
			
			menu->pushNav(mBox);
		break;
	}
	
}