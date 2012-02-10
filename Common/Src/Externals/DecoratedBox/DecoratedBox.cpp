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

DecoratedBox* DecoratedBox::decoratedBoxWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect& rect, const cocos2d::CCSize& size)
{
	DecoratedBox* box = new DecoratedBox();
	if (box && box->initWithTexture(pTexture, rect, size))
	{
        box->autorelease();
        return box;
    }
    CC_SAFE_DELETE(box);
	return NULL;
}

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

bool DecoratedBox::initWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect& rect, const cocos2d::CCSize& size)
{
	if(!CCSpriteBatchNode::initWithTexture(pTexture, 9))
	{
		return false;
	}
	
	cell.origin = rect.origin;
	cell.size = CCSizeMake(rect.size.width / 3, rect.size.height / 3);
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->setContentSize(size);
	
    return true;
}

bool DecoratedBox::initWithFile(const char*  filename, const cocos2d::CCSize& size)
{
	if(!CCSpriteBatchNode::initWithFile(filename, 9))
	{
		return false;
	}
	
	CCSize textureSize = this->getTextureAtlas()->getTexture()->getContentSize();
	
	cell.origin = ccp(0, 0);
	cell.size = CCSizeMake(textureSize.width / 3, textureSize.height / 3);
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
    
    int uw = ceilf(size.width / cell.size.width);
    int uh = ceilf(size.height / cell.size.height);
    float offw = fmod(size.width, cell.size.width);
    float offh = fmod(size.height, cell.size.height);
	
    for (int j = 0; j < uh; j++) {
        for (int i = 0; i < uw; i++) {
            
            CCRect rect;
            
			if (i == (uw - 2) && j == (uw - 2)) {
				rect = CCRectMake(cell.size.width, cell.size.height, offw, offh);
            } else if (i == (uw - 2)) {
				if (j == (uh - 1)) {
                    // Top border
                    rect = CCRectMake(cell.size.width, 0, offw, cell.size.height);
                } else if (j == 0) {
                    // Bottom border
                    rect = CCRectMake(cell.size.width, cell.size.height * 2, offw, cell.size.height);
				} else {
                    // Middle
                    rect = CCRectMake(cell.size.width, cell.size.height, offw, cell.size.height);
                }
            } else if (j == (uw - 2)) {
				if (i == (uh - 1)) {
                    // Right border
                    rect = CCRectMake(cell.size.width * 2, cell.size.height, cell.size.width, offh);
                } else if (i == 0) {
                    // Left border
                    rect = CCRectMake(0, cell.size.height, cell.size.width, offh);
				} else {
                    // Middle
                    rect = CCRectMake(cell.size.width, cell.size.height, cell.size.width, offh);
                }
            } else if (i == 0) {
                
                if (j == (uh - 1)) {
                    // Top left cap
                    rect = CCRectMake(0, 0, cell.size.width, cell.size.height);
                } else if (j == 0) {
                    // Bottom left cap
                    rect = CCRectMake(0, cell.size.height * 2, cell.size.width, cell.size.height);
				} else {
                    // Left border
                    rect = CCRectMake(0, cell.size.height, cell.size.width, cell.size.height);
                }
                
            } else if (i == (uw - 1)) {
                
                if (j == (uh - 1)) {
                    // Top right cap
                    rect = CCRectMake(cell.size.width * 2, 0, cell.size.width, cell.size.height);
                } else if (j == 0) {
                    // Bottom right cap
                    rect = CCRectMake(cell.size.width * 2, cell.size.height * 2, cell.size.width, cell.size.height);
                } else {
                    // Right border
                    rect = CCRectMake(cell.size.width * 2, cell.size.height, cell.size.width, cell.size.height);
                }
                
            } else if (j == (uh - 1)) {
                // Top border
                rect = CCRectMake(cell.size.width, 0, cell.size.width, cell.size.height);
            } else if (j == 0) {
                // Bottom border
                rect = CCRectMake(cell.size.width, cell.size.height * 2, cell.size.width, cell.size.height);
            } else {
                // Middle
                rect = CCRectMake(cell.size.width, cell.size.height, cell.size.width, cell.size.height);
            }
			rect.origin = ccpAdd(rect.origin, cell.origin);
			
			CCSprite* b = CCSprite::spriteWithBatchNode(this, rect);
			b->setAnchorPoint(ccp(0, 0));
			if (j == (uh - 1) && i == (uw - 1)) {
				b->setPosition(ccp((i - 1) * cell.size.width + offw, (j - 1) * cell.size.height + offh));
			} else if (j == (uh - 1)) {
				b->setPosition(ccp(i * cell.size.width, (j - 1) * cell.size.height + offh));
			} else if (i == (uw - 1)) {
				b->setPosition(ccp((i - 1) * cell.size.width + offw, j * cell.size.height));
			} else {
				b->setPosition(ccp(i * cell.size.width, j * cell.size.height));
			}
			b->setTag(j * cell.size.height + i);
            
			this->addChild(b);
        }
    }
}