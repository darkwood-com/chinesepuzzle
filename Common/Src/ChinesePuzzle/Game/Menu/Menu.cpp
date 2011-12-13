/**
 *  Menu.cpp
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

#include "Menu.h"

using namespace cocos2d;

Menu::Menu() :
nav(ccArrayNew(1))
{
	ml = new MenuLayout(this);
}

Menu::~Menu()
{
	CC_SAFE_DELETE(ml);
	
	ccArrayFree(nav);
}

bool Menu::init(GameScene* gs)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	this->gs = gs;
	this->setIsTouchEnabled(true);
	
	ml->layout();
	
	this->schedule(schedule_selector(Menu::step));
	
	return true;
}

void Menu::draw()
{
	CCLayer::draw();
}

void Menu::step(ccTime dt)
{
	
}

void Menu::pushNav(MenuBox* mBox)
{
	ccArrayAppendObjectWithResize(nav, mBox);
	this->addChild(mBox);
}

MenuBox* Menu::popNav()
{
	if(nav->num > 0)
	{
		MenuBox* mBox = NULL;
		ccArrayRemoveObject(nav, mBox);
		this->removeChild(mBox, true);
		return mBox;
	}
	
	return NULL;
}

//actions
void Menu::actionTheme(CCObject* data)
{
	
}


//input touches/mouse
void Menu::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
}

bool Menu::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	//last menu menu touch management
	if(nav->num > 0)
	{
		MenuBox* mc = (MenuBox*) nav->arr[nav->num-1];
		mc->ccTouchBegan(pTouch, pEvent);
	}
	
	return true;
}

void Menu::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	//last menu menu touch management
	if(nav->num > 0)
	{
		MenuBox* mc = (MenuBox*) nav->arr[nav->num-1];
		mc->ccTouchMoved(pTouch, pEvent);
	}
}

void Menu::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	//last menu menu touch management
	if(nav->num > 0)
	{
		MenuBox* mc = (MenuBox*) nav->arr[nav->num-1];
		mc->ccTouchEnded(pTouch, pEvent);
	}
}

void Menu::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	//last menu menu touch management
	if(nav->num > 0)
	{
		MenuBox* mc = (MenuBox*) nav->arr[nav->num-1];
		mc->ccTouchCancelled(pTouch, pEvent);
	}
}
