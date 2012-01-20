/**
 *  MenuLayout.h
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

#ifndef __MENU_LAYOUT_H__
#define __MENU_LAYOUT_H__

#import "cocos2d.h"
#include "MenuBox.h"

class Menu;

// MenuLayout Layer
class CC_DLL MenuLayout : public cocos2d::CCObject, public cocos2d::SelectorProtocol
{
private:
	template <class T> T* layoutRes(const char* key);
	
protected:
	Menu* menu;
	cocos2d::CCMutableDictionary<std::string, cocos2d::CCMenuItemImage*>* themes;
	
	MenuBox* mBox;
	cocos2d::CCMenuItemImage* miTheme;
	
public:
	typedef enum
	{
		TypeNone,
		TypeNewGame,
		TypeRetryGame,
		TypeHint,
		TypeTheme,
	} Type;
	
	MenuLayout(Menu* menu);
	virtual ~MenuLayout();
	
	virtual bool initWithType(Type type);
	
	void layout();
	
	CC_SYNTHESIZE_READONLY(Type, type, Type);
};

#endif // __MENU_LAYOUT_H__
