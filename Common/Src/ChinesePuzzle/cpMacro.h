/**
 *  cpMacro.h
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

#ifndef __CP_MACRO_H__
#define __CP_MACRO_H__

//chinese puzzle macro

#include "cocos2d.h"

static cocos2d::CCTexture2D* ccTextureNull = new cocos2d::CCTexture2D();

namespace cocos2d
{
	inline void copySpriteBatchNode(cocos2d::CCSpriteBatchNode* from, cocos2d::CCSpriteBatchNode* to)
	{
		CCAssert(from != NULL, "sprite batch node should not be null");
		CCAssert(to != NULL, "sprite batch node should not be null");
		
		to->removeAllChildrenWithCleanup(true);
		to->setTexture(from->getTexture());
		
		CCArray* pChildren = from->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(pChildren, pObject)
			{
				CCSprite* pChild = (CCSprite*) pObject;
				if (pChild)
				{
					CCSprite* zoneSprite = CCSprite::spriteWithBatchNode(to, pChild->getTextureRect());
					zoneSprite->setAnchorPoint(ccp(0, 0));
					zoneSprite->setPosition(pChild->getPosition());
					to->addChild(zoneSprite);
				}
			}
		}
		
		to->setContentSize(from->getContentSize());
		to->setAnchorPoint(ccp(0.5f, 0.5f));
	}

	inline CCSprite* copyFirstSpriteBatchNode(cocos2d::CCSpriteBatchNode* sprite)
	{
		CCArray* pChildren = sprite->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(pChildren, pObject)
			{
				CCSprite* pChild = (CCSprite*) pObject;
				if (pChild)
				{
					return CCSprite::spriteWithTexture(pChild->getTexture(), pChild->getTextureRect());
				}
			}
		}
		
		return NULL;
	}
}

#define CP_STR(s)			#s
#define CP_CSTR(s1, s2)		CP_STR(s1 ## s2)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#define CP_PLATFORM(file)	CP_CSTR(file,_wophone.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define CP_PLATFORM(file)	CP_CSTR(file,_win32.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define CP_PLATFORM(file)	CP_CSTR(file,_android.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define CP_PLATFORM(file)	CP_CSTR(file,_ios.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define CP_PLATFORM(file)	CP_CSTR(file,_mac.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define CP_PLATFORM(file)	CP_CSTR(file,_marmalade.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#define CP_PLATFORM(file)	CP_CSTR(file,_linux.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
#define CP_PLATFORM(file)	CP_CSTR(file,_bada.h)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
#define CP_PLATFORM(file)	CP_CSTR(file,_qnx.h)
#else
#error
#endif

#endif // __CP_MACRO_H__

