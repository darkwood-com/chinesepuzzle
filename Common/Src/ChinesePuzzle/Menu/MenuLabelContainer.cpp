/**
 *  MenuLabelContainer.cpp
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


#include "MenuLabelContainer.h"

using namespace cocos2d;

MenuLabelContainer::MenuLabelContainer() :
container(NULL)
{
	
}

MenuLabelContainer::~MenuLabelContainer()
{
	CC_SAFE_RELEASE(container);
}

bool MenuLabelContainer::initWithConfAndContentSizeAndFntFile(GameConfigCommon* conf, const cocos2d::CCSize& size, const char *fntFile)
{
	if(!MenuBox::initWithConfAndContentSize(conf, size))
	{
		return false;
	}
	
	container = new MenuLabel();
	container->initWithContentSizeAndFntFile(size, fntFile);
	container->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(container);
	
	this->margin = CCSizeMake(0, 0);
	
	return true;
}

void MenuLabelContainer::setString(const char *str)
{
	container->setString(str);
}

const char* MenuLabelContainer::getString(void)
{
	return container->getString();
}

void MenuLabelContainer::setWidth(float width)
{
	container->setWidth(width);
}

float MenuLabelContainer::getWidth()
{
	return container->getWidth();
}

void MenuLabelContainer::setAlignment(CCTextAlignment alignment)
{
	container->setAlignment(alignment);
}

void MenuLabelContainer::setMargin(cocos2d::CCSize margin)
{
	this->margin = margin;
	
	this->layout();
}

CCSize MenuLabelContainer::getMargin()
{
	return this->margin;
}

void MenuLabelContainer::layout(bool anim)
{
	MenuBox::layout(anim);
	
	CCSize size = this->getContentSize();
	
	if(container)
	{
		container->setPosition(ccp(size.width / 2, size.height / 2));
		container->setContentSize(CCSizeMake(size.width - 2 * margin.width, size.height - 2 * margin.height));
	}
}

bool MenuLabelContainer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if(!MenuBox::ccTouchBegan(pTouch, pEvent))
	{
		return false;
	}
	
	return container->ccTouchBegan(pTouch, pEvent);
}

void MenuLabelContainer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchMoved(pTouch, pEvent);
	
	container->ccTouchMoved(pTouch, pEvent);
}

void MenuLabelContainer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchEnded(pTouch, pEvent);
	
	container->ccTouchEnded(pTouch, pEvent);
}

void MenuLabelContainer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	MenuBox::ccTouchCancelled(pTouch, pEvent);
	
	container->ccTouchCancelled(pTouch, pEvent);
}