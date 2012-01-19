/**
 *  CCMenuItemBMFont.ccp
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

#include "CCMenuItemBMFont.h"
#include "CCLabelBMFont.h"

using namespace cocos2d;

CCMenuItemBMFont * CCMenuItemBMFont::itemFromString(const char *value, const char *fntFile)
{
	return CCMenuItemBMFont::itemFromString(value, fntFile, NULL, NULL);
}

CCMenuItemBMFont * CCMenuItemBMFont::itemFromString(const char *value, const char *fntFile, SelectorProtocol* target, SEL_MenuHandler selector)
{
	CCMenuItemBMFont *pRet = new CCMenuItemBMFont();
	pRet->initFromString(value, fntFile, target, selector);
	pRet->autorelease();
	return pRet;
}

bool CCMenuItemBMFont::initFromString(const char *value, const char *fntFile, SelectorProtocol* target, SEL_MenuHandler selector)
{
	CCAssert( value != NULL && strlen(value) != 0, "value length must be greater than 0");
	CCLabelBMFont *label = new CCLabelBMFont();
	label->initWithString(value, fntFile);
	label->autorelease();
	if (CCMenuItemLabel::initWithLabel(label, target, selector))
	{
		// do something ?
	}
	return true;
}

void CCMenuItemBMFont::selected()
{
	// subclass to change the default action
	if(m_bIsEnabled)
	{
		CCMenuItem::selected();
	}
}

void CCMenuItemBMFont::unselected()
{
	// subclass to change the default action
	if(m_bIsEnabled)
	{
		CCMenuItem::unselected();
	}
}