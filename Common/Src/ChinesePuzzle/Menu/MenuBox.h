/**
 *  MenuBox.h
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

#ifndef __MENU_BOX_H__
#define __MENU_BOX_H__

#import "cocos2d.h"
#include "DecoratedBox.h"
#include "MenuContainer.h"

class CC_DLL MenuBox : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
protected:
	//display
	DecoratedBox* bg; //background
	cocos2d::CCMenuItemImage* validBtn; //valid button
	cocos2d::CCLabelTTF* titleLabel; //title
	
	cocos2d::tCCMenuState m_eState;
	cocos2d::CCMenuItem* itemForTouch(cocos2d::CCTouch* touch);
	cocos2d::CCMenuItem* m_pSelectedItem;
public:
	MenuBox();
	virtual ~MenuBox();
	
	virtual bool init();
	virtual bool initWithContentSize(const cocos2d::CCSize& size);
	virtual bool initWithResolution(const char* resolution);
	virtual bool initWithResolutionAndContentSize(const char* resolution, const cocos2d::CCSize& size);
	
	virtual void setTitle(const char* title);
	virtual const char* getTitle(void);
	
	virtual void setContentSize(const cocos2d::CCSize& size);
	
	virtual void layout();
	
	virtual void setOkTarget(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector);
	
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	
	CC_PROPERTY(cocos2d::CCArray*, items, Items);
};

#endif // __MENU_BOX_H__
