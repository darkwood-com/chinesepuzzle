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

#include "cocos2d.h"
#include "DecoratedBox.h"

class GameConfigCommon;

class CC_DLL MenuBox : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
protected:
	//display
	DecoratedBox* bg; //background
	cocos2d::CCMenuItemSprite* validBtn; //valid button
	cocos2d::CCLabelBMFont* titleLabel; //title
	
	cocos2d::tCCMenuState m_eState;
	cocos2d::CCMenuItem* itemForTouch(cocos2d::CCTouch* touch);
	cocos2d::CCMenuItem* m_pSelectedItem;
	
	std::string m_sLayoutFontFile;
public:
	MenuBox();
	virtual ~MenuBox();
	
	virtual bool initWithConf(GameConfigCommon* conf);
	virtual bool initWithConfAndContentSize(GameConfigCommon* conf, const cocos2d::CCSize& size);
	
	virtual void setTitle(const char* title, const std::string& fontFile);
	virtual const char* getTitle(void);
	CC_SYNTHESIZE(cocos2d::CCPoint, titlePosition, TitlePosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, validPosition, ValidPosition);
	
	virtual void setContentSize(const cocos2d::CCSize& size);
	
	virtual void layout(bool anim = true);
	
	virtual void setOkTarget(cocos2d::CCObject *rec, cocos2d::SEL_MenuHandler selector);
	
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	
	CC_PROPERTY(cocos2d::CCArray*, items, Items);
	virtual void addItem(CCNode* pChild, int zOrder, int tag);
	virtual void removeItemByTag(int tag, bool cleanup);
};

#endif // __MENU_BOX_H__
