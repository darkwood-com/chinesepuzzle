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

#include <cmath>
#include <algorithm>

using namespace cocos2d;

MenuLayout::MenuLayout(Menu* menu) :
menu(menu),
isLayout(false)
{
}

MenuLayout::~MenuLayout()
{
}

void MenuLayout::layout()
{
	if(isLayout) return;
	
	bg = CCSprite::spriteWithFile((std::string("Data/themes/classic/480x320/bg.png")).c_str());
	bg->setAnchorPoint(ccp(0,0));
	menu->addChild(bg);
	
	MenuBox* mBox = new MenuBox();
	if(mBox->initWithContentSize(CCSizeMake(200, 200)))
	{
		mBox->setPosition(ccp(100, 50));
		CCString* mBoxTitle = new CCString("Options");
		mBox->setTitle(mBoxTitle);
		mBoxTitle->release();
		
		
		CCArray* items = CCArray::array();
		
		MenuItem* item = NULL;
		for(int i = 0; i < 13; ++i)
		{
			item = new MenuItem();
			item->init();
			item->setContentSize(CCSizeMake(10, 10));
			items->addObject(item);
			item->release();
		}
		
		mBox->setMargin(CCSizeMake(50, 50));
		mBox->setItems(items);
		mBox->setGridSize(ccg(4, 2));
		mBox->setPage(0);
		mBox->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
		
		menu->pushNav(mBox);
	}
	
	isLayout = true;
}