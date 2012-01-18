/**
 *  DecoratedBox.cpp
 *  DecoratedBox
 *
 *  Created by Mathieu LEDRU on 01/11/11.
 *
 *  Conversion of code from Cocos2D (Fabio Rodella) to Cocos2D-x (Mathieu Ledru)
 *  Adapted for my uses
 *  
 *  Original code can be found at https://github.com/crocodella/DecoratedBox
 */

#include "DecoratedBox.h"
#include <math.h>

using namespace cocos2d;

DecoratedBox* DecoratedBox::decoratedBoxWithFile(const char* filename, const cocos2d::CCSize& size)
{
	DecoratedBox* box = new DecoratedBox();
	if (box && box->initWithFile(filename, size))
	{
        box->autorelease();
        return box;
    }
    CC_SAFE_DELETE(box);
	return NULL;
}

bool DecoratedBox::initWithFile(const char*  filename, const cocos2d::CCSize& size)
{
	if(!CCSpriteBatchNode::initWithFile(filename, 9))
	{
		return false;
	}
	
	cellSize = this->getTextureAtlas()->getTexture()->getContentSize().width / 3;
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->setContentSize(size);
	
    return true;
}

void DecoratedBox::setContentSize(const CCSize& size)
{
	this->removeAllChildrenWithCleanup(true);
    
	CCSpriteBatchNode::setContentSize(size);
	
    boxWidth = size.width;
    boxHeight = size.height;
    
    int uw = ceilf(size.width / cellSize);
    int uh = ceilf(size.height / cellSize);
    float offw = fmod(size.width, cellSize);
    float offh = fmod(size.height, cellSize);
	
    for (int j = 0; j < uh; j++) {
        for (int i = 0; i < uw; i++) {
            
            CCRect rect;
            
			if (i == (uw - 2) && j == (uw - 2)) {
				rect = CCRectMake(cellSize, cellSize, offw, offh);
            } else if (i == (uw - 2)) {
				if (j == (uh - 1)) {
                    // Top border
                    rect = CCRectMake(cellSize, 0, offw, cellSize);
                } else if (j == 0) {
                    // Bottom border
                    rect = CCRectMake(cellSize, cellSize * 2, offw, cellSize);
				} else {
                    // Middle
                    rect = CCRectMake(cellSize, cellSize, offw, cellSize);
                }
            } else if (j == (uw - 2)) {
				if (i == (uh - 1)) {
                    // Right border
                    rect = CCRectMake(cellSize * 2, cellSize, cellSize, offh);
                } else if (i == 0) {
                    // Left border
                    rect = CCRectMake(0, cellSize, cellSize, offh);
				} else {
                    // Middle
                    rect = CCRectMake(cellSize, cellSize, cellSize, offh);
                }
            } else if (i == 0) {
                
                if (j == (uh - 1)) {
                    // Top left cap
                    rect = CCRectMake(0, 0, cellSize, cellSize);
                } else if (j == 0) {
                    // Bottom left cap
                    rect = CCRectMake(0, cellSize * 2, cellSize, cellSize);
				} else {
                    // Left border
                    rect = CCRectMake(0, cellSize, cellSize, cellSize);
                }
                
            } else if (i == (uw - 1)) {
                
                if (j == (uh - 1)) {
                    // Top right cap
                    rect = CCRectMake(cellSize * 2, 0, cellSize, cellSize);
                } else if (j == 0) {
                    // Bottom right cap
                    rect = CCRectMake(cellSize * 2, cellSize * 2, cellSize, cellSize);
                } else {
                    // Right border
                    rect = CCRectMake(cellSize * 2, cellSize, cellSize, cellSize);
                }
                
            } else if (j == (uh - 1)) {
                // Top border
                rect = CCRectMake(cellSize, 0, cellSize, cellSize);
            } else if (j == 0) {
                // Bottom border
                rect = CCRectMake(cellSize, cellSize * 2, cellSize, cellSize);
            } else {
                // Middle
                rect = CCRectMake(cellSize, cellSize, cellSize, cellSize);
            }
            
			CCSprite* b = CCSprite::spriteWithBatchNode(this, rect);
			b->setAnchorPoint(ccp(0, 0));
			if (j == (uh - 1) && i == (uw - 1)) {
				b->setPosition(ccp((i - 1) * cellSize + offw, (j - 1) * cellSize + offh));
			} else if (j == (uh - 1)) {
				b->setPosition(ccp(i * cellSize, (j - 1) * cellSize + offh));
			} else if (i == (uw - 1)) {
				b->setPosition(ccp((i - 1) * cellSize + offw, j * cellSize));
			} else {
				b->setPosition(ccp(i * cellSize, j * cellSize));
			}
			b->setTag(j * cellSize + i);
            
			this->addChild(b);
        }
    }
}