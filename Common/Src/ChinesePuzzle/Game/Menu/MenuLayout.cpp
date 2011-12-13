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
mBoxDefault(NULL),
mBoxTheme(NULL),
miTheme(NULL)
{
	
}

MenuLayout::~MenuLayout()
{
	CC_SAFE_RELEASE(themes);
	
	CC_SAFE_RELEASE(mBoxDefault);
	CC_SAFE_RELEASE(mBoxTheme);
	CC_SAFE_RELEASE(miTheme);
}

bool MenuLayout::init()
{
	themes = new CCMutableDictionary<std::string, cocos2d::CCMenuItemImage*>();
	themes->setObject(CCMenuItemImage::itemFromNormalImage(std::string("Data/ui/480x320/menuItemTheme.png").c_str(), NULL, NULL, this, menu_selector(MenuLayout::layout)), "default");
	
	return true;
}

void MenuLayout::layout(CCObject* node)
{
	if(node == NULL)
	{
		if(!menu->getChildByTag(kMenuTagBg))
		{
			CCSprite* bg = CCSprite::spriteWithFile((std::string("Data/themes/classic/480x320/bg.png")).c_str());
			bg->setAnchorPoint(ccp(0,0));
			menu->addChild(bg, 0, kMenuTagBg);
		}
		
		if(!mBoxDefault)
		{
			mBoxDefault = new MenuBox();
			mBoxDefault->initWithContentSize(CCSizeMake(200, 200));
			mBoxDefault->setPosition(ccp(100, 50));
			mBoxDefault->setMargin(CCSizeMake(50, 50));
			mBoxDefault->setGridSize(ccg(4, 1));
			mBoxDefault->setPage(0);
			mBoxDefault->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
			
			CCString* mBoxTitle = new CCString("Options");
			mBoxDefault->setTitle(mBoxTitle);
			mBoxTitle->release();
			
			CCArray* items = CCArray::array();
			
			miTheme = new CCMenuItemImage();
			miTheme->initFromNormalImage(std::string("Data/ui/480x320/menuItemTheme.png").c_str(), NULL, NULL, this, menu_selector(MenuLayout::layout));
			items->addObject(miTheme);
			miTheme->release();
			
			mBoxDefault->setItems(items);
		}
		
		menu->pushNav(mBoxDefault);
	}
	else if(node == miTheme)
	{
		if(!mBoxTheme)
		{
			mBoxTheme = new MenuBox();
			mBoxTheme->initWithContentSize(CCSizeMake(200, 200));
			mBoxTheme->setPosition(ccp(100, 50));
			mBoxTheme->setMargin(CCSizeMake(50, 50));
			mBoxTheme->setGridSize(ccg(2, 2));
			mBoxTheme->setPage(0);
			mBoxTheme->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
			
			CCString* mBoxTitle = new CCString("Themes");
			mBoxTheme->setTitle(mBoxTitle);
			mBoxTitle->release();
			
			CCArray* items = CCArray::array();
			
			std::vector<std::string> sTheme = themes->allKeys();
			for(std::vector<std::string>::iterator it = sTheme.begin(); it != sTheme.end(); ++it)
			{
				CCMenuItemImage* mItem = themes->objectForKey(*it);
				items->addObject(mItem);
			}
			
			mBoxTheme->setItems(items);
		}
		
		menu->pushNav(mBoxTheme);
	}
}