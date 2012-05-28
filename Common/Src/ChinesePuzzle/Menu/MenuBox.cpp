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


#include "cpMacro.h"
#include "MenuBox.h"
#include "GameConfig.h"

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

bool MenuBox::initWithConf(GameConfigCommon* conf)
{
	this->items = CCArray::array();
	this->items->retain();
	
	m_eState = kCCMenuStateWaiting;
	m_pSelectedItem = NULL;
	
	CCSpriteBatchNode* spriteNodeBg = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
	conf->getNodeUiPath("menuContainer", spriteNodeBg);
	CCSprite* spriteBg = copyFirstSpriteBatchNode(spriteNodeBg);
	
	bg = new DecoratedBox();
	bg->initWithTexture(spriteBg->getTexture(), spriteBg->getTextureRect(), this->getContentSize());
	bg->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(bg);
	
	CCSpriteBatchNode* spriteNodeValidBtn = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
	conf->getNodeUiPath("menuItemOk", spriteNodeValidBtn);
	CCSprite* spriteValidBtn = copyFirstSpriteBatchNode(spriteNodeValidBtn);
	
	validBtn = new CCMenuItemSprite();
	validBtn->initFromNormalSprite(spriteValidBtn, NULL, NULL, NULL, NULL);
	validBtn->setAnchorPoint(ccp(0.5f, 0.5f));
	validBtn->setScale(0.75f);
	this->addChild(validBtn);
	
	return true;
}

bool MenuBox::initWithConfAndContentSize(GameConfigCommon* conf, const cocos2d::CCSize& size)
{
	if (this->initWithConf(conf))
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

void MenuBox::layout(bool anim)
{
	CCSize size = this->getContentSize();
	
	if(titleLabel) titleLabel->setPosition(ccp(30, size.height - 30));
	if(validBtn) validBtn->setPosition(ccp(size.width - 10, size.height - 10));
	if(bg)
	{
		bg->setPosition(ccp(size.width / 2, size.height / 2));
		bg->setContentSize(CCSizeMake(size.width, size.height));
	}
}

void MenuBox::setOkTarget(cocos2d::CCObject *rec, SEL_MenuHandler selector)
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
	CCPoint touchLocation = touch->locationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	
	CCArray* menuItems = CCArray::arrayWithArray(this->getItems());
	menuItems->addObject(validBtn);
	if (menuItems && menuItems->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(menuItems, pObject)
		{
			CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
			if (pChild && pChild->getIsVisible() && pChild->getIsEnabled())
			{
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = pChild->rect();
				r.origin = CCPointZero;
				
				if (CCRect::CCRectContainsPoint(r, local))
				{
					return pChild;
				}
			}
		}
		
	}
	
	return NULL;
}