/**
 *  MenuContainer.cpp
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


#include "MenuContainer.h"
#include <math.h>

using namespace cocos2d;

MenuContainerSwipeTo* MenuContainerSwipeTo::actionWithDuration(ccTime duration, const CGFloat& swipe)
{
	MenuContainerSwipeTo *pMenuContainerSwipeTo = new MenuContainerSwipeTo();
	pMenuContainerSwipeTo->initWithDuration(duration, swipe);
	pMenuContainerSwipeTo->autorelease();
	
	return pMenuContainerSwipeTo;
}

bool MenuContainerSwipeTo::initWithDuration(ccTime duration, const CGFloat& swipe)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		m_endSwipe = swipe;
		return true;
	}
	
	return false;
}

CCObject* MenuContainerSwipeTo::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	MenuContainerSwipeTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (MenuContainerSwipeTo*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new MenuContainerSwipeTo();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCActionInterval::copyWithZone(pZone);
	
	pCopy->initWithDuration(m_fDuration, m_endSwipe);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void MenuContainerSwipeTo::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_startSwipe = ((MenuContainer*) m_pTarget)->getSwipe();
	m_delta = m_endSwipe - m_startSwipe;
}

void MenuContainerSwipeTo::update(ccTime time)
{
	if (m_pTarget)
	{
		((MenuContainer*) m_pTarget)->setSwipe(m_startSwipe + m_delta * time);
	}
}

enum 
{
	kCCScrollLayerStateIdle,
	kCCScrollLayerStateSliding,
}; 

MenuContainer::MenuContainer() :
items(NULL),
gridSize(ccg(0, 0)),
page(0),
m_pDelegate(NULL),
m_fStartSwipe(0),
m_fOffsetSwipe(0),
m_pScrollTouch(NULL),
m_iState(kCCScrollLayerStateIdle)
{
	
}

MenuContainer::~MenuContainer()
{
	CC_SAFE_RELEASE(items);
	m_pDelegate = NULL;
}

bool MenuContainer::init()
{
	items = CCArray::array();
	
	// Set default minimum touch length to scroll.
	m_fMinimumTouchLengthToSlide = 10.0f;
	m_fMinimumTouchLengthToChangePage = 100.0f;
	
	this->layout();
	
	return true;
}

bool MenuContainer::initWithContentSize(const CCSize& size)
{
	if (this->init())
	{
		this->setContentSize(size);
		
		// Set default minimum touch length to scroll.
		m_fMinimumTouchLengthToChangePage = size.width / 8;
		
		return true;
	}
	
	return false;
}


void MenuContainer::resetGrid()
{
	for(ItemGrid::iterator it = itemsGrid.begin(); it != itemsGrid.end(); ++it)
	{
		this->removeChild((*it).second, true);
	}
	itemsGrid.clear();
	
	int a = gridSize.x * gridSize.y;
	for(int k = a * (page - 1); k < a * (page + 2); ++k)
	{
		if(k >= 0 && k < items->count())
		{
			MenuItem* item = (MenuItem*) items->objectAtIndex(k);
			item->setAnchorPoint(ccp(0.5f, 0.5f));
			this->addChild(item);
			
			int p = k / a;
			ccGridCoord coord = ccgc(p * gridSize.x + k % gridSize.x,
									 gridSize.y - 1 - (k - p * a) / gridSize.x);
			itemsGrid[coord] = item;
		}
	}
	
	this->layout();
}

void MenuContainer::setItems(CCArray* items)
{
	CC_SAFE_RETAIN(items);
	CC_SAFE_RELEASE(this->items);
	this->items = items;
	
	this->resetGrid();
}

CCArray* MenuContainer::getItems()
{
	return this->items;
}

void MenuContainer::setGridSize(ccGridSize gridSize)
{
	this->gridSize = gridSize;
	
	this->resetGrid();
}

ccGridSize MenuContainer::getGridSize()
{
	return this->gridSize;
}

void MenuContainer::setSwipe(CGFloat swipe)
{
	this->m_fOffsetSwipe = swipe;
	
	this->layout();
}

CGFloat MenuContainer::getSwipe()
{
	return this->m_fOffsetSwipe;
}

void MenuContainer::setPage(int page)
{
	if(page >= 0 && page < this->getMaxPage())
	{
		this->page = page;
		
		this->setSwipe(0);
		this->resetGrid();
	}
}

int MenuContainer::getPage()
{
	return this->page;
}

void MenuContainer::swipeToPage(int page)
{
	if(page >= 0 && page < this->getMaxPage())
	{
		runAction(CCSequence::actionOneTwo(
			MenuContainerSwipeTo::actionWithDuration(0.3f, (this->page - page) * this->getContentSize().width),
			CCCallFunc::actionWithTarget(this, callfunc_selector(MenuContainer::swipeToPageEnded))
		));
	}
}

int MenuContainer::getMaxPage()
{
	return (int) ceil((float) this->items->count() / (this->gridSize.x * this->gridSize.y));
}

void MenuContainer::swipeToPageEnded()
{
	this->setPage(this->getPage() - (int) round(this->getSwipe() / this->getContentSize().width));
	
	if (m_pDelegate)
		m_pDelegate->scrollLayerScrolledToPageNumber(this, this->page);
}

void MenuContainer::setContentSize(const cocos2d::CCSize& size)
{
	CCNode::setContentSize(size);
	
	this->layout();
}

void MenuContainer::layout()
{
	CCSize size = this->getContentSize();
	
	if(gridSize.x > 0 && gridSize.y > 0)
	{
		CCSize pad = CCSizeMake(size.width / gridSize.x, size.height / gridSize.y);
		CCPoint origin = ccp(size.width / (2 * gridSize.x) - page * size.width, size.height / (2 * gridSize.y));

		for(ItemGrid::iterator it = itemsGrid.begin(); it != itemsGrid.end(); ++it)
		{
			it->second->setPosition(ccpAdd(origin, ccp(it->first.x * pad.width + m_fOffsetSwipe, it->first.y * pad.height)));
		}
	}
}

void MenuContainer::draw(void)
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

void MenuContainer::visit(void)
{
	CCNode::visit();
	
	/*
	glEnable(GL_SCISSOR_TEST);
	
	CCRect rect = this->boundingBox();
	rect.origin = this->convertToWorldSpace(rect.origin);
	glScissor(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	
	CCNode::visit();
	
	glDisable(GL_SCISSOR_TEST);
	 */
}

bool MenuContainer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (!m_pScrollTouch)
		m_pScrollTouch = pTouch;
	else
		return false;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	m_fStartSwipe = touchPoint.x;
	m_iState = kCCScrollLayerStateIdle;
	
	return true;
}

void MenuContainer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_pScrollTouch != pTouch)
		return;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	// If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
	// Of course only if we not already in sliding mode
	if ((m_iState != kCCScrollLayerStateSliding) 
		&& (fabsf(touchPoint.x - m_fStartSwipe) >= m_fMinimumTouchLengthToSlide))
	{
		m_iState = kCCScrollLayerStateSliding;
		
		// Avoid jerk after state change.
		m_fStartSwipe = touchPoint.x;
		
		if (m_pDelegate)
			m_pDelegate->scrollLayerScrollingStarted(this);
	}
	
	if (m_iState == kCCScrollLayerStateSliding)
	{
		this->setSwipe(touchPoint.x - m_fStartSwipe);
	}
}

void MenuContainer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	if(m_pScrollTouch != pTouch)
		return;
	
	m_pScrollTouch = NULL;
	
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int selectedPage = this->getPage();
	int swipe = touchPoint.x - m_fStartSwipe;
	
	this->setSwipe(swipe);
	if (swipe > 0 && swipe >= m_fMinimumTouchLengthToChangePage)
	{
		selectedPage -= (int) ((this->getSwipe() - m_fMinimumTouchLengthToChangePage) / this->getContentSize().width) + 1;
	}
	else if(swipe < 0 && swipe <= -m_fMinimumTouchLengthToChangePage)
	{
		selectedPage += - (int) ((this->getSwipe() + m_fMinimumTouchLengthToChangePage) / this->getContentSize().width) + 1;
	}
	if(selectedPage < 0) selectedPage = 0;
	if(selectedPage >= this->getMaxPage()) selectedPage = this->getMaxPage() - 1;
	
	this->swipeToPage(selectedPage);
}

void MenuContainer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	// Do not cancel touch, if this method is called from cancelAndStoleTouch:
	if (m_bStealingTouchInProgress)
		return;
	
	if (m_pScrollTouch == pTouch)
	{
		m_pScrollTouch = NULL;
		this->setPage(page);
	}
}