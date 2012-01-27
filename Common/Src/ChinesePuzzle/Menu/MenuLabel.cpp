/**
 *  MenuLabel.cpp
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


#include "MenuLabel.h"
#include <math.h>

using namespace cocos2d;

enum 
{
	kCCScrollLayerStateIdle,
	kCCScrollLayerStateSliding,
}; 

MenuLabel::MenuLabel() :
label(NULL),
m_fStartSwipe(0),
m_fOffsetSwipe(0),
m_fOffsetScroll(0),
m_pScrollTouch(NULL),
m_iState(kCCScrollLayerStateIdle)
{
	
}

MenuLabel::~MenuLabel()
{
	CC_SAFE_RELEASE(label);
}

bool MenuLabel::initWithContentSizeAndFntFile(const cocos2d::CCSize& size, const char *fntFile)
{
	this->setContentSize(size);
	
	label = new CCLabelBMFontMultiline();
	label->initWithString("", fntFile, 0, CCLabelBMFontMultilineLeftAlignment);
	label->setAnchorPoint(ccp(0.5f, 1.0f));
	this->addChild(label);
	
	return true;
}

void MenuLabel::setString(const char *str)
{
	label->setString(str);
}

const char* MenuLabel::getString(void)
{
	return label->getString();
}

void MenuLabel::setWidth(float width)
{
	label->setWidth(width);
}

float MenuLabel::getWidth()
{
	return label->getWidth();
}

void MenuLabel::setAlign(CCLabelBMFontMultilineAlignment align)
{
	label->setAlign(align);
}

CCLabelBMFontMultilineAlignment MenuLabel::getAlign()
{
	return label->getAlign();
}

void MenuLabel::setSwipe(CGFloat swipe)
{
	this->m_fOffsetSwipe = swipe;
	
	this->layout();
}

CGFloat MenuLabel::getSwipe()
{
	return this->m_fOffsetSwipe;
}

void MenuLabel::setContentSize(const cocos2d::CCSize& size)
{
	CCNode::setContentSize(size);
	
	this->layout();
}

void MenuLabel::layout(bool anim)
{
	CCSize size = this->getContentSize();
	
	if(label)
	{
		label->setWidth(size.width);
		label->setPosition(ccpAdd(ccp(size.width / 2, size.height), ccp(0, m_fOffsetScroll + m_fOffsetSwipe)));
	}
}

void MenuLabel::visit(void)
{
	glEnable(GL_SCISSOR_TEST);
	
	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0, 0, size.width, size.height);
	rect.origin = this->convertToWorldSpace(rect.origin);
	CCDirector::sharedDirector()->getOpenGLView()->setScissorInPoints(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	
	CCNode::visit();
	
	glDisable(GL_SCISSOR_TEST);
}

bool MenuLabel::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (!m_pScrollTouch)
		m_pScrollTouch = pTouch;
	else
		return false;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	m_fStartSwipe = touchPoint.y;
	m_iState = kCCScrollLayerStateIdle;
	
	return true;
}

void MenuLabel::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_pScrollTouch != pTouch)
		return;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	// If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
	// Of course only if we not already in sliding mode
	if ((m_iState != kCCScrollLayerStateSliding))
	{
		m_iState = kCCScrollLayerStateSliding;
		
		// Avoid jerk after state change.
		m_fStartSwipe = touchPoint.y;
	}
	
	if (m_iState == kCCScrollLayerStateSliding)
	{
		this->setSwipe(touchPoint.y - m_fStartSwipe);
	}
}

void MenuLabel::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_pScrollTouch != pTouch)
		return;
	
	m_pScrollTouch = NULL;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	this->setScroll(this->getScroll() + touchPoint.y - m_fStartSwipe);
	this->setSwipe(0);
}

void MenuLabel::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	if (m_pScrollTouch == pTouch)
	{
		m_pScrollTouch = NULL;
	}
}