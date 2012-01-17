/**
 *  CCMenuItemBMFont.h
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

#ifndef __CCMENU_ITEM_BM_FONT_
#define __CCMENU_ITEM_BM_FONT_

#include "CCMenuItem.h"

namespace   cocos2d {

class CC_DLL CCMenuItemBMFont : public CCMenuItemLabel
{
public:
	CCMenuItemBMFont(){}
	virtual ~CCMenuItemBMFont(){}
	/** creates a menu item from a string and atlas with a target/selector */
	static CCMenuItemBMFont* itemFromString(const char *value, const char *fntFile);
	/** creates a menu item from a string and atlas. Use it with MenuItemToggle */
	static CCMenuItemBMFont* itemFromString(const char *value, const char *fntFile, SelectorProtocol* target, SEL_MenuHandler selector);
	/** initializes a menu item from a string and atlas with a target/selector */
	bool initFromString(const char *value, const char *fntFile, SelectorProtocol* target, SEL_MenuHandler selector);
};

} //namespace   cocos2d 

#endif
