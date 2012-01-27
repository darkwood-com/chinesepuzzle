/**
 *  MenuLabelContainer.h
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

#ifndef __MENU_LABEL_CONTAINER_H__
#define __MENU_LABEL_CONTAINER_H__

#include "MenuBox.h"
#include "MenuLabel.h"

class CC_DLL MenuLabelContainer : public MenuBox
{
protected:
	//display
	MenuLabel* container; //container
public:
	MenuLabelContainer();
	virtual ~MenuLabelContainer();
	
	virtual bool initWithResolutionAndContentSizeAndFntFile(const char* resolution, const cocos2d::CCSize& size, const char *fntFile);
	
	virtual void setString(const char *str);
	virtual const char* getString(void);
	virtual void setWidth(float width);
	virtual float getWidth();
	virtual void setAlign(cocos2d::CCLabelBMFontMultilineAlignment align);
	virtual cocos2d::CCLabelBMFontMultilineAlignment getAlign();
	
	CC_PROPERTY(cocos2d::CCSize, margin, Margin);
	
public:
	virtual void layout(bool anim = true);
	
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif // __MENU_LABEL_CONTAINER_H__
