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
#include "GameScene.h"

using namespace cocos2d;

Menu::Menu() :
gs(NULL),
nav(ccArrayNew(1))
{
}

Menu::~Menu()
{
	CC_SAFE_RELEASE(ml);
	
	ccArrayFree(nav);
}

bool Menu::init(MenuInit init)
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	this->gs = init.gs;
	this->setIsTouchEnabled(true);

	this->ml = new MenuLayout(this);
	this->ml->initWithType(init.layout);
	this->layout();
	
	this->schedule(schedule_selector(Menu::step));
	
	return true;
}

void Menu::step(ccTime dt)
{
	
}

void Menu::draw()
{
	CCLayer::draw();
}

void Menu::layout(bool anim)
{
	ml->layout(anim);
}

void Menu::pushNav(MenuBox* mBox)
{
	if(nav->num > 0)
	{
		this->removeChild((MenuBox*) nav->arr[nav->num-1], true);
	}
	ccArrayAppendObjectWithResize(nav, mBox);
	this->addChild(mBox);
}

MenuBox* Menu::popNav()
{
	if(nav->num > 0)
	{
		MenuBox* mBox = (MenuBox*) nav->arr[nav->num-1];
		ccArrayRemoveObject(nav, mBox);
		this->removeChild(mBox, true);
		
		if(nav->num > 0)
		{
			this->addChild((MenuBox*) nav->arr[nav->num-1]);
		}
		return mBox;
	}
	
	return NULL;
}

void Menu::okMenu(cocos2d::CCObject* item)
{
	this->popNav();
	
	if(nav->num == 0)
	{
		gs->game();
	}
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
