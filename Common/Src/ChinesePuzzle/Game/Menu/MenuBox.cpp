/**
 *  MenuBox.cpp
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


#include "MenuBox.h"

using namespace cocos2d;

MenuBox::MenuBox() :
title(NULL),
items(NULL),
validBtn(NULL),
titleLabel(NULL),
container(NULL)
{
	
}

MenuBox::~MenuBox()
{
	CC_SAFE_RELEASE(title);
	CC_SAFE_RELEASE(items);
	CC_SAFE_RELEASE(validBtn);
	CC_SAFE_RELEASE(titleLabel);
	CC_SAFE_RELEASE(container);
}

bool MenuBox::init()
{
	bg = new DecoratedBox();
	bg->initWithFile("Data/menuContainer.png", this->getContentSize());
	bg->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(bg);
	
	CCLabelTTF* pValidBtn = new CCLabelTTF();
	pValidBtn->initWithString("Ok", "Arial", 12);
	pValidBtn->setAnchorPoint(ccp(1.0f, 0.5f));
	this->addChild(pValidBtn);
	validBtn = pValidBtn;
	
	container = new MenuContainer();
	container->init();
	container->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(container);
	
	this->margin = CCSizeMake(0, 0);
	
	this->layout();
	
	return true;
}

bool MenuBox::initWithContentSize(const CCSize& size)
{
	if (this->init())
	{
		this->setContentSize(size);
		
		return true;
	}
	
	return false;
}

void MenuBox::setTitle(CCString* title)
{
	CC_SAFE_RETAIN(title);
	CC_SAFE_RELEASE(this->title);
	this->title = title;
	
	if(titleLabel) titleLabel->setString(title->toStdString().c_str());
	else
	{
		titleLabel = new CCLabelTTF();
		titleLabel->initWithString(title->toStdString().c_str(), "Arial", 12);
		titleLabel->setAnchorPoint(ccp(0.0f, 1.0f));
		this->addChild(titleLabel);
	}
	
	this->layout();
}

CCString* MenuBox::getTitle()
{
	return this->title;
}

void MenuBox::setItems(CCArray* items)
{
	container->setItems(items);
}

CCArray* MenuBox::getItems()
{
	return container->getItems();
}

void MenuBox::setGridSize(ccGridSize gridSize)
{
	container->setGridSize(gridSize);
}

ccGridSize MenuBox::getGridSize()
{
	return container->getGridSize();
}

void MenuBox::setMargin(cocos2d::CCSize margin)
{
	this->margin = margin;
	
	this->layout();
}

CCSize MenuBox::getMargin()
{
	return this->margin;
}

void MenuBox::setPage(int page)
{
	container->setPage(page);
}

int MenuBox::getPage()
{
	return container->getPage();
}

void MenuBox::setMinimumTouchLengthToSlide(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToSlide(length);
}

CGFloat MenuBox::getMinimumTouchLengthToSlide()
{
	return container->getMinimumTouchLengthToSlide();
}

void MenuBox::setMinimumTouchLengthToChangePage(cocos2d::CGFloat length)
{
	container->setMinimumTouchLengthToChangePage(length);
}

CGFloat MenuBox::getMinimumTouchLengthToChangePage()
{
	return container->getMinimumTouchLengthToChangePage();
}

void MenuBox::setContentSize(const cocos2d::CCSize& size)
{
	CCNode::setContentSize(size);

	this->layout();
}

void MenuBox::layout()
{
	CCSize size = this->getContentSize();
	
	if(titleLabel) titleLabel->setPosition(ccp(20, size.height - 10));
	if(validBtn) validBtn->setPosition(ccp(size.width - 10, size.height));
	if(bg)
	{
		bg->setPosition(ccp(size.width / 2, size.height / 2));
		bg->setContentSize(CCSizeMake(size.width, size.height));
	}
	
	container->setPosition(ccp(size.width / 2, size.height / 2));
	container->setContentSize(CCSizeMake(size.width - 2 * margin.width, size.height - 2 * margin.height));
}

void MenuBox::draw(void)
{
	CCNode::draw();
	
	CCSize size = this->getContentSize();
	
	CCPoint vertices[] = {
		CCPoint(0, 0),
		CCPoint(size.width, 0),
		CCPoint(size.width, size.height),
		CCPoint(0, size.height),
	};
	
	ccDrawPoly(vertices, 4, true);
}

bool MenuBox::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	return container->ccTouchBegan(pTouch, pEvent);
}

void MenuBox::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	container->ccTouchMoved(pTouch, pEvent);
}

void MenuBox::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	container->ccTouchEnded(pTouch, pEvent);
}

void MenuBox::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	container->ccTouchCancelled(pTouch, pEvent);
}