/**
 *  MenuBoxContainer.h
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

#ifndef __MENU_BOX_CONTAINER_H__
#define __MENU_BOX_CONTAINER_H__

#include "MenuBox.h"
#include "MenuContainer.h"

class CC_DLL MenuBoxContainer : public MenuBox
{
protected:
	//display
	MenuContainer* container; //container
public:
	MenuBoxContainer();
	virtual ~MenuBoxContainer();
	
	virtual bool initWithResolution(const char* resolution);
	
	virtual void setItems(cocos2d::CCArray* items);
	virtual cocos2d::CCArray* getItems();
	
	CC_PROPERTY(cocos2d::ccGridSize, gridSize, GridSize);
	CC_PROPERTY(cocos2d::CCSize, margin, Margin);
	
	CC_PROPERTY(int, page, Page);
	
	/** Calibration property. Minimum moving touch length that is enough
	 * to cancel menu items and start scrolling a layer. 
	 */
	CC_PROPERTY(cocos2d::CGFloat, m_fMinimumTouchLengthToSlide, MinimumTouchLengthToSlide)
	
	/** Calibration property. Minimum moving touch length that is enough to change
	 * the page, without snapping back to the previous selected page.
	 */
	CC_PROPERTY(cocos2d::CGFloat, m_fMinimumTouchLengthToChangePage, MinimumTouchLengthToChangePage)
	
public:
	virtual void layout();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif // __MENU_BOX_CONTAINER_H__
