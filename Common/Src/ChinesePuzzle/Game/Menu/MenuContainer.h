/**
 *  MenuContainer.h
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

#ifndef __MENU_CONTAINER_H__
#define __MENU_CONTAINER_H__

#import "cocos2d.h"
#include "DecoratedBox.h"

namespace   cocos2d
{
	struct ccGridCoord : public ccGridSize
	{
		bool operator<( const ccGridCoord & g ) const
		{
			return x < g.x || (x == g.x && y < g.y);
		}
	};

	static inline ccGridCoord
	ccgc(const int x, const int y)
	{
		ccGridCoord v;
		v.x = x;
		v.y = y;
		return v;
	}
	typedef std::map<ccGridCoord, CCMenuItem*> ItemGrid;
}

class MenuContainer;

class CC_DLL MenuContainerSwipeTo : public cocos2d::CCActionInterval
{
public:
	/** initializes the action */
	bool initWithDuration(cocos2d::ccTime duration, const cocos2d::CGFloat& swipe);
	
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
	virtual void startWithTarget(cocos2d::CCNode *pTarget);
	virtual void update(cocos2d::ccTime time);
	
public:
	/** creates the action */
	static MenuContainerSwipeTo* actionWithDuration(cocos2d::ccTime duration, const cocos2d::CGFloat& swipe);
	
protected:
	cocos2d::CGFloat m_endSwipe;
	cocos2d::CGFloat m_startSwipe;
	cocos2d::CGFloat m_delta;
};

class MenuContainerDelegate
{
public:
	/** Called when scroll layer begins scrolling.
	 * Usefull to cancel CCTouchDispatcher standardDelegates.
	 */
	virtual void scrollLayerScrollingStarted(MenuContainer* sender) {}
	
	/** Called at the end of moveToPage:
	 * Doesn't get called in selectPage:
	 */
	virtual void scrollLayerScrolledToPageNumber(MenuContainer* sender, int page) {}
};

class CC_DLL MenuContainer : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
protected:
	//display
	cocos2d::ItemGrid itemsGrid; //items (=3x gridSize)
	
	void resetGrid();
	
	// The x coord of initial point the user starts their swipe.
	cocos2d::CGFloat m_fStartSwipe;
	
	// Internal state of scroll (scrolling or idle).
	int m_iState;
	// Holds the touch that started the scroll
	cocos2d::CCTouch* m_pScrollTouch;
	
	void swipeToPageEnded();
	int getMaxPage();
	
public:
	MenuContainer();
	virtual ~MenuContainer();
	
	bool init();
	bool initWithContentSize(const cocos2d::CCSize& size);
	
	CC_PROPERTY(cocos2d::CCArray*, items, Items)
	CC_PROPERTY(cocos2d::ccGridSize, gridSize, GridSize)
	CC_PROPERTY(cocos2d::CGFloat, m_fOffsetSwipe, Swipe)
	virtual void setContentSize(const cocos2d::CCSize& size);
	
	void layout();
	virtual void visit(void);

	CC_PROPERTY(int, page, Page)
	
	/* Moves scrollLayer to page with given number & invokes delegate
	 * method scrollLayer:scrolledToPageNumber: at the end of CCMoveTo action. 
	 * Does nothing if number >= totalScreens or < 0.
	 */
	void swipeToPage(int pageNumber);
	
	CC_SYNTHESIZE(MenuContainerDelegate*, m_pDelegate, Delegate)
	
	/** Calibration property. Minimum moving touch length that is enough
	 * to cancel menu items and start scrolling a layer. 
	 */
	CC_SYNTHESIZE(cocos2d::CGFloat, m_fMinimumTouchLengthToSlide, MinimumTouchLengthToSlide)
	
	/** Calibration property. Minimum moving touch length that is enough to change
	 * the page, without snapping back to the previous selected page.
	 */
	CC_SYNTHESIZE(cocos2d::CGFloat, m_fMinimumTouchLengthToChangePage, MinimumTouchLengthToChangePage)

public:
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif // __MENU_CONTAINER_H__
