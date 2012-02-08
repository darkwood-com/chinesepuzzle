/**
 *  MenuLabel.h
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

#ifndef __MENU_LABEL_H__
#define __MENU_LABEL_H__

#include "cocos2d.h"
#include "CCLabelBMFontMultiline.h"

class CC_DLL MenuLabel : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
protected:
	//display
	cocos2d::CCLabelBMFontMultiline* label; //text label
	
	void resetLabel();
	
	// The x coord of initial point the user starts their swipe.
	cocos2d::CGFloat m_fStartSwipe;
	
	// Internal state of scroll (scrolling or idle).
	int m_iState;
	// Holds the touch that started the scroll
	cocos2d::CCTouch* m_pScrollTouch;
	
public:
	MenuLabel();
	virtual ~MenuLabel();
	
	bool initWithContentSizeAndFntFile(const cocos2d::CCSize& size, const char *fntFile);
	
	virtual void setString(const char *str);
	virtual const char* getString(void);
	virtual void setWidth(float width);
	virtual float getWidth();
	virtual void setAlign(cocos2d::CCLabelBMFontMultilineAlignment align);
	virtual cocos2d::CCLabelBMFontMultilineAlignment getAlign();
	CC_PROPERTY(cocos2d::CGFloat, m_fOffsetSwipe, Swipe);
	CC_SYNTHESIZE(cocos2d::CGFloat, m_fOffsetScroll, Scroll);
	virtual void setContentSize(const cocos2d::CCSize& size);
	
	void layout(bool anim = true);
	virtual void visit(void);
	
public:
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif // __MENU_GRID_H__
