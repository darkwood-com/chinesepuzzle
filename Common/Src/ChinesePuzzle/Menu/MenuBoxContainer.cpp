/**
 *  MenuBoxContainer.cpp
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


#include "MenuBoxContainer.h"

using namespace cocos2d;

MenuBoxContainer::MenuBoxContainer() :
container(NULL)
{
	
}

MenuBoxContainer::~MenuBoxContainer()
{
	CC_SAFE_RELEASE(container);
}

bool MenuBoxContainer::init()
{
	if(!MenuBox::init())
	{
		return false;
	}
	
	container = new MenuContainer();
	container->init();
	container->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(container);
	
	this->margin = CCSizeMake(0, 0);
	
	return true;
}

void MenuBoxContainer::setItems(CCArray* items)
{
	container->setItems(items);
}

CCArray* MenuBoxContainer::getItems()
{
	return container->getItems();
}

void MenuBoxContainer::setGridSize(ccGridSize gridSize)
{
	container->setGridSize(gridSize);
}

ccGridSize MenuBoxContainer::getGridSize()
{
	return container->getGridSize();
}

void MenuBoxContainer::setMargin(cocos2d::CCSize margin)
{
	this->margin = margin;
	
	this->layout();
}

CCSize MenuBoxContainer::getMargin()
{
	return this->margin;
}

void MenuBoxContainer::setPage(int page)
{
	container->setPage(page);
}

int MenuBoxContainer::getPage()
{
	return container->getPage();
}

void MenuBoxContainer::setMinimumTouchLengthToSlide(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToSlide(length);
}

CGFloat MenuBoxContainer::getMinimumTouchLengthToSlide()
{
	return container->getMinimumTouchLengthToSlide();
}

void MenuBoxContainer::setMinimumTouchLengthToChangePage(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToChangePage(length);
}

CGFloat MenuBoxContainer::getMinimumTouchLengthToChangePage()
{
	return container->getMinimumTouchLengthToChangePage();
}

void MenuBoxContainer::layout()
{
	MenuBox::layout();
	
	CCSize size = this->getContentSize();
	
	container->setPosition(ccp(size.width / 2, size.height / 2));
	container->setContentSize(CCSizeMake(size.width - 2 * margin.width, size.height - 2 * margin.height));
}

bool MenuBoxContainer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if(!MenuBox::ccTouchBegan(pTouch, pEvent))
	{
		return false;
	}
	
	return container->ccTouchBegan(pTouch, pEvent);
}

void MenuBoxContainer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchMoved(pTouch, pEvent);
	
	container->ccTouchMoved(pTouch, pEvent);
}

void MenuBoxContainer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchEnded(pTouch, pEvent);
	
	container->ccTouchEnded(pTouch, pEvent);
}

void MenuBoxContainer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchCancelled(pTouch, pEvent);
	
	container->ccTouchCancelled(pTouch, pEvent);
}