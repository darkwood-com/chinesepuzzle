/**
 *  MenuGridContainer.cpp
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


#include "MenuGridContainer.h"

using namespace cocos2d;

MenuGridContainer::MenuGridContainer() :
container(NULL)
{
	
}

MenuGridContainer::~MenuGridContainer()
{
	CC_SAFE_RELEASE(container);
}

bool MenuGridContainer::initWithResolution(const char* resolution)
{
	if(!MenuBox::initWithResolution(resolution))
	{
		return false;
	}
	
	container = new MenuGrid();
	container->init();
	container->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(container);
	
	this->margin = CCSizeMake(0, 0);
	
	return true;
}

void MenuGridContainer::setItems(CCArray* items)
{
	container->setItems(items);
}

CCArray* MenuGridContainer::getItems()
{
	return container->getItems();
}

void MenuGridContainer::setGridSize(ccGridSize gridSize)
{
	container->setGridSize(gridSize);
}

ccGridSize MenuGridContainer::getGridSize()
{
	return container->getGridSize();
}

void MenuGridContainer::setMargin(cocos2d::CCSize margin)
{
	this->margin = margin;
	
	this->layout();
}

CCSize MenuGridContainer::getMargin()
{
	return this->margin;
}

void MenuGridContainer::setPage(int page)
{
	container->setPage(page);
}

int MenuGridContainer::getPage()
{
	return container->getPage();
}

void MenuGridContainer::setMinimumTouchLengthToSlide(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToSlide(length);
}

CGFloat MenuGridContainer::getMinimumTouchLengthToSlide()
{
	return container->getMinimumTouchLengthToSlide();
}

void MenuGridContainer::setMinimumTouchLengthToChangePage(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToChangePage(length);
}

CGFloat MenuGridContainer::getMinimumTouchLengthToChangePage()
{
	return container->getMinimumTouchLengthToChangePage();
}

void MenuGridContainer::layout()
{
	MenuBox::layout();
	
	CCSize size = this->getContentSize();
	
	if(container)
	{
		container->setPosition(ccp(size.width / 2, size.height / 2));
		container->setContentSize(CCSizeMake(size.width - 2 * margin.width, size.height - 2 * margin.height));
	}
}

bool MenuGridContainer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if(!MenuBox::ccTouchBegan(pTouch, pEvent))
	{
		return false;
	}
	
	return container->ccTouchBegan(pTouch, pEvent);
}

void MenuGridContainer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchMoved(pTouch, pEvent);
	
	container->ccTouchMoved(pTouch, pEvent);
}

void MenuGridContainer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchEnded(pTouch, pEvent);
	
	container->ccTouchEnded(pTouch, pEvent);
}

void MenuGridContainer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchCancelled(pTouch, pEvent);
	
	container->ccTouchCancelled(pTouch, pEvent);
}