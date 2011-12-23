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

#ifndef __DecoratedBox_H__
#define __DecoratedBox_H__

#include "cocos2d.h"

class CC_DLL DecoratedBox : public cocos2d::CCSpriteBatchNode
{
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, cellSize, CellSize);
	
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxWidth, BoxWidth);
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxHeight, BoxHeight);
	
public:
	static DecoratedBox* decoratedBoxWithFile(const char* filename, const cocos2d::CCSize& size);
	virtual bool initWithFile(const char* filename, const cocos2d::CCSize& size);
	
	virtual void setContentSize(const cocos2d::CCSize& size);
};

#endif // __DecoratedBox_H__