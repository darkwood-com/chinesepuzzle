/**
 *  DecoratedBox.h
 *  DecoratedBox
 *
 *  Created by Mathieu LEDRU on 01/11/11.
 *
 *  Conversion of code from Cocos2D (Fabio Rodella) to Cocos2D-x (Mathieu Ledru)
 *  Adapted for my uses
 *  
 *  Original code can be found at https://github.com/crocodella/DecoratedBox
 */

#ifndef __DECORATED_BOX_H__
#define __DECORATED_BOX_H__

#include "cocos2d.h"

class CC_DLL DecoratedBox : public cocos2d::CCSpriteBatchNode
{
	CC_SYNTHESIZE_READONLY(cocos2d::CCRect, cell, Cell);
	
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxWidth, BoxWidth);
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxHeight, BoxHeight);
	
public:
	static DecoratedBox* decoratedBoxWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect& rect, const cocos2d::CCSize& size);
	static DecoratedBox* decoratedBoxWithFile(const char* filename, const cocos2d::CCSize& size);
	virtual bool initWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect& rect, const cocos2d::CCSize& size);
	virtual bool initWithFile(const char* filename, const cocos2d::CCSize& size);
	
	virtual void setContentSize(const cocos2d::CCSize& size);
};

#endif // __DECORATED_BOX_H__