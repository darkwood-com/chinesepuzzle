/**
 *  Menu.h
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

#ifndef __MENU_H__
#define __MENU_H__

#import "cocos2d.h"
#include "MenuLayout.h"

class GameScene;

typedef struct
{
	GameScene* gs;
	MenuLayout::Type layout;
} MenuInit;

// Menu Layer
class Menu : public cocos2d::CCLayer
{
protected:
	cocos2d::ccArray* nav;
	
public:
	Menu();
	virtual ~Menu();
	LAYER_NODE_FUNC_PARAM(Menu, MenuInit, init);
	
	virtual bool init(MenuInit init);
	
	void step(cocos2d::ccTime dt);
	void draw();
	
	void pushNav(MenuBox* mBox);
	MenuBox* popNav();
	
	void okMenu(cocos2d::CCObject* item);
	
	//input touches/mouse
	virtual void registerWithTouchDispatcher();
	
	bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	
	CC_SYNTHESIZE_READONLY(GameScene*, gs, GameScene);
	
	CC_SYNTHESIZE_READONLY(MenuLayout*, ml, Layout);
};

#endif // __MENU_H__
