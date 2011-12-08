/**
 *  DecoratedBox.h
 *  DecoratedBox
 *
 *  Created by Mathieu LEDRU on 01/11/11.
 *
 *  Conversion of code from Cocos2D (Fabio Rodella) to Cocos2D-x (Mathieu Ledru)
 *  Original code can be found at https://github.com/crocodella/DecoratedBox
 */

#ifndef __DecoratedBox_H__
#define __DecoratedBox_H__

#import "cocos2d.h"

class CC_DLL DecoratedBox : public cocos2d::CCSpriteBatchNode
{
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, cellSize, CellSize);
	
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxWidth, BoxWidth);
	CC_SYNTHESIZE_READONLY(cocos2d::CGFloat, boxHeight, BoxHeight);
	
public:
	static DecoratedBox* decoratedBoxWithFile(const char* filename, cocos2d::CGFloat w, cocos2d::CGFloat h);
	virtual bool initWithFile(const char* filename, cocos2d::CGFloat w, cocos2d::CGFloat h);
	
	virtual void resizeToWidth(cocos2d::CGFloat w, cocos2d::CGFloat h);
};

#endif // __DecoratedBox_H__