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
items(NULL),
validBtn(NULL),
titleLabel(NULL)
{
	
}

MenuBox::~MenuBox()
{
	CC_SAFE_RELEASE(items);
	CC_SAFE_RELEASE(validBtn);
	CC_SAFE_RELEASE(titleLabel);
}

bool MenuBox::init()
{
	return initWithResolution("480x320");
}

bool MenuBox::initWithContentSize(const CCSize& size)
{
	return initWithResolutionAndContentSize("480x320", size);
}

bool MenuBox::initWithResolution(const char* resolution)
{
	std::string path = std::string(resolution) + std::string("/ui/");
	
	this->items = CCArray::array();
	this->items->retain();
	
	m_eState = kCCMenuStateWaiting;
	m_pSelectedItem = NULL;
	
	bg = new DecoratedBox();
	bg->initWithFile((path + std::string("menuContainer.png")).c_str(), this->getContentSize());
	bg->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(bg);
	
	validBtn = new CCMenuItemImage();
	validBtn->initFromNormalImage((path + std::string("menuItemOk.png")).c_str(), NULL, NULL, NULL, NULL);
	validBtn->setAnchorPoint(ccp(0.5f, 0.5f));
	validBtn->setScale(0.75f);
	this->addChild(validBtn);
	
	return true;
}

bool MenuBox::initWithResolutionAndContentSize(const char* resolution, const cocos2d::CCSize& size)
{
	if (this->initWithResolution(resolution))
	{
		this->setContentSize(size);
		
		return true;
	}
	
	return false;
}

void MenuBox::setTitle(const char* title)
{
	if(titleLabel) titleLabel->setString(title);
	else
	{
		titleLabel = new CCLabelBMFont();
		titleLabel->initWithString(title, "fonts/arial32.fnt");
		titleLabel->setAnchorPoint(ccp(0.0f, 1.0f));
		this->addChild(titleLabel);
	}
	
	this->layout();
}

const char* MenuBox::getTitle()
{
	return (titleLabel) ? titleLabel->getString() : NULL;
}

void MenuBox::setItems(CCArray* items)
{
	if(this->items && this->items->count() > 0)
	{
        CCObject* child;
        CCARRAY_FOREACH(this->items, child)
        {
            CCNode* pChild = (CCNode*) child;
			this->removeChild(pChild, true);
        }
	}
	
	CC_SAFE_RELEASE(this->items);
	this->items = CCArray::arrayWithArray(items);
	this->items->retain();
	
	if(this->items->count() > 0)
	{
        CCObject* child;
        CCARRAY_FOREACH(this->items, child)
        {
            CCNode* pChild = (CCNode*) child;
			this->addChild(pChild);
		}
	}
}

CCArray* MenuBox::getItems()
{
	return this->items;
}

void MenuBox::setContentSize(const cocos2d::CCSize& size)
{
	CCNode::setContentSize(size);

	this->layout();
}

void MenuBox::layout()
{
	CCSize size = this->getContentSize();
	
	if(titleLabel) titleLabel->setPosition(ccp(40, size.height - 30));
	if(validBtn) validBtn->setPosition(ccp(size.width - 20, size.height - 20));
	if(bg)
	{
		bg->setPosition(ccp(size.width / 2, size.height / 2));
		bg->setContentSize(CCSizeMake(size.width, size.height));
	}
}

void MenuBox::setOkTarget(SelectorProtocol *rec, SEL_MenuHandler selector)
{
	validBtn->setTarget(rec, selector);
}

bool MenuBox::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (m_eState != kCCMenuStateWaiting || ! m_bIsVisible)
	{
		return false;
	}
	
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->getIsVisible() == false)
		{
			return false;
		}
	}
	
	m_pSelectedItem = this->itemForTouch(pTouch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
	}
	
	return true;
}

void MenuBox::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_eState == kCCMenuStateTrackingTouch)
	{
		CCMenuItem* currentItem = this->itemForTouch(pTouch);
		if (currentItem != m_pSelectedItem) 
		{
			if (m_pSelectedItem)
			{
				m_pSelectedItem->unselected();
			}
			m_pSelectedItem = currentItem;
			if (m_pSelectedItem)
			{
				m_pSelectedItem->selected();
			}
		}
	}
}

void MenuBox::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_eState == kCCMenuStateTrackingTouch)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem->activate();
		}
		m_eState = kCCMenuStateWaiting;
	}
}

void MenuBox::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_eState == kCCMenuStateTrackingTouch)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_eState = kCCMenuStateWaiting;
	}
}

CCMenuItem* MenuBox::itemForTouch(CCTouch *touch)
{
	CCPoint touchLocation = touch->locationInView(touch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	
	CCArray* menuItems = CCArray::arrayWithArray(this->getItems());
	menuItems->addObject(validBtn);
	if (menuItems && menuItems->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(menuItems, pObject)
		{
			CCNode* pChild = (CCNode*) pObject;
			if (pChild && pChild->getIsVisible() && ((CCMenuItem*)pChild)->getIsEnabled())
			{
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = ((CCMenuItem*)pChild)->rect();
				r.origin = CCPointZero;
				
				if (CCRect::CCRectContainsPoint(r, local))
				{
					return (CCMenuItem*)pChild;
				}
			}
		}
		
	}
	
	return NULL;
}