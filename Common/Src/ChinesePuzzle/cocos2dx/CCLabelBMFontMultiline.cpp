/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Use any of these editors to generate BMFonts:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#include "CCLabelBMFontMultiline.h"

#include "platform/platform.h"
#include "CCMutableDictionary.h"
#include "CCConfiguration.h"
#include "CCDrawingPrimitives.h"
#include "CCSprite.h"
#include "CCPointExtension.h"

#include "CCFileUtils.h"
#include "support/data_support/uthash.h"

namespace cocos2d{
	
	//
	//Hash Element
	//
	// Equal function for targetSet.
	typedef struct _KerningHashElement
	{	
		int				key;		// key for the hash. 16-bit for 1st element, 16-bit for 2nd element
		int				amount;
		UT_hash_handle	hh;
	} tKerningHashElement;
	
	//
	//CCLabelBMFontMultiline
	//

	//LabelBMFont - Creation & Init
	CCLabelBMFontMultiline *CCLabelBMFontMultiline::labelWithString(const char *str, const char *fntFile, float width, CCLabelBMFontMultilineAlignment align)
	{
		CCLabelBMFontMultiline *pRet = new CCLabelBMFontMultiline();
		if(pRet && pRet->initWithString(str, fntFile, width, align))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}

	bool CCLabelBMFontMultiline::initWithString(const char *theString, const char *fntFile, float width, CCLabelBMFontMultilineAlignment align)
	{	
		m_sfntFile = fntFile;
		m_width = width;
		m_align = align;

		if (CCLabelBMFont::initWithString(theString, fntFile))
		{
			return true;
		}
		return false;
	}

	// LabelBMFont - Atlas generation
	int CCLabelBMFontMultiline::kerningAmountForFirst(unsigned short first, unsigned short second)
	{
		int ret = 0;
		unsigned int key = (first<<16) | (second & 0xffff);

		if( m_pConfiguration->m_pKerningDictionary ) {
			tKerningHashElement *element = NULL;
			HASH_FIND_INT(m_pConfiguration->m_pKerningDictionary, &key, element);		
			if(element)
				ret = element->amount;
		}
		return ret;
	}
	void CCLabelBMFontMultiline::createFontChars()
	{
		int nextFontPositionX = 0;
        int nextFontPositionY = 0;
		unsigned short prev = -1;
		int kerningAmount = 0;

		CCSize tmpSize = CCSizeZero;

        int longestLine = 0;
        unsigned int totalHeight = 0;

        unsigned int quantityOfLines = 1;

		unsigned int stringLen = m_sString.length();

        if (0 == stringLen)
        {
            return;
        }

        for (unsigned int i = 0; i < stringLen - 1; ++i)
        {
            unsigned short c = m_sString[i];
            if (c == '\n')
            {
                quantityOfLines++;
            }
        }

        totalHeight = m_pConfiguration->m_uCommonHeight * quantityOfLines;
        nextFontPositionY = -(m_pConfiguration->m_uCommonHeight - m_pConfiguration->m_uCommonHeight * quantityOfLines);
		for (unsigned int i= 0; i < stringLen; i++)
		{
			unsigned short c = m_sString[i];
			CCAssert( c < kCCBMFontMaxChars, "LabelBMFont: character outside bounds");

            if (c == '\n')
            {
				if (m_align == CCLabelBMFontMultilineLeftAlignment)
					nextFontPositionX = 0;
				else
					if (m_align == CCLabelBMFontMultilineRightAlignment)
					{
						nextFontPositionX = m_width-substrlenInPixels(&m_sString[i+1]);
					}
					else
						if (m_align == CCLabelBMFontMultilineCenterAlignment)
						{
							nextFontPositionX = (m_width-substrlenInPixels(&m_sString[i+1]))/2;
						}
                nextFontPositionY -= m_pConfiguration->m_uCommonHeight;

                continue;
            }
            
			kerningAmount = this->kerningAmountForFirst(prev, c);

			const ccBMFontDef& fontDef = m_pConfiguration->m_pBitmapFontArray[c];

			CCRect rect = fontDef.rect;

			CCSprite *fontChar;

			fontChar = (CCSprite*)(this->getChildByTag(i));
			if( ! fontChar )
			{
				fontChar = new CCSprite();
				fontChar->initWithBatchNodeRectInPixels(this, rect);
				this->addChild(fontChar, 0, i);
				fontChar->release();
			}
			else
			{
				// reusing fonts
				fontChar->setTextureRectInPixels(rect, false, rect.size);

				// restore to default in case they were modified
				fontChar->setIsVisible(true);
				fontChar->setOpacity(255);
			}

            float yOffset = (float) (m_pConfiguration->m_uCommonHeight - fontDef.yOffset);
			fontChar->setPositionInPixels( ccp( nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width / 2.0f + kerningAmount,
				                                (float) nextFontPositionY + yOffset - rect.size.height/2.0f ) );		

			//CCLog("position.y: %f", fontChar->getPosition().y);

			// update kerning
			nextFontPositionX += m_pConfiguration->m_pBitmapFontArray[c].xAdvance + kerningAmount;
			prev = c;

			// Apply label properties
			fontChar->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
			// Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
			fontChar->setColor(m_tColor);

			// only apply opaccity if it is different than 255 )
			// to prevent modifying the color too (issue #610)
			if( m_cOpacity != 255 )
			{
				fontChar->setOpacity(m_cOpacity);
			}

            if (longestLine < nextFontPositionX)
            {
                longestLine = nextFontPositionX;
            }
		}

        tmpSize.width  = (float) longestLine;
        tmpSize.height = (float) totalHeight;

		this->setContentSizeInPixels(tmpSize);
	}

	int CCLabelBMFontMultiline::substrlenInPixels (char* str)
	{
		int kerningAmount = 0;
		int substrlen=0;
		unsigned short prev = -1;

		for (unsigned int i= 0; i < strlen(str); i++)
		{
			unsigned short c = *(str+i);
			if (c != '\n' && c != '\0')
			{
				kerningAmount = this->kerningAmountForFirst(prev, c);
				substrlen += m_pConfiguration->m_pBitmapFontArray[c].xAdvance + kerningAmount;
				prev = c;
			}
			else
				return substrlen;
		}
		return substrlen;
	}

	//LabelBMFont - CCLabelProtocol protocol
	void CCLabelBMFontMultiline::setString(const char *newString)
	{
		int lastInsertedWord=0, prev_cnt=0;
		
		char tempstr[4096]; memset(tempstr, 0, 4096);
		int cnt=0;
		for (int i=0; i < strlen(newString); ++i)
		{
			if (newString[i] == ' ' || newString[i] == ',' || newString[i] == '.' || newString[i] == '!' || newString[i] == '?')
			{
				CCLabelBMFont * jopa = CCLabelBMFont::labelWithString(tempstr, m_sfntFile.c_str());
				CCSize size = jopa->getContentSize();
				if (size.width < m_width)
				{
					lastInsertedWord = i;
					prev_cnt = cnt;
					tempstr[cnt++] = newString[i];
					tempstr[cnt] = '\0';
				}
				else if (newString[lastInsertedWord] == ' ')
				{
					tempstr[prev_cnt] = '\n';
					tempstr[cnt++] = newString[i];
					tempstr[cnt] = '\0';
				}
				else
				{
					memcpy(&tempstr[prev_cnt+2], newString, i-lastInsertedWord);
					tempstr[prev_cnt+1] = '\n';
					cnt+=2;
				}
			}
			else
			{
				tempstr[cnt++] = newString[i];
				tempstr[cnt] = '\0';
			}
		}
		
		m_sString.clear();
		m_sString = tempstr;
		

		if (m_pChildren && m_pChildren->count() != 0)
		{
            CCObject* child;
            CCARRAY_FOREACH(m_pChildren, child)
            {
                CCNode* pNode = (CCNode*) child;
                if (pNode)
                {
                    pNode->setIsVisible(false);
                }
            }
		}
		this->createFontChars();
	}
	
	void CCLabelBMFontMultiline::setWidth(float width)
	{
		m_width = width;
		this->createFontChars();
	}
	
	float CCLabelBMFontMultiline::getWidth()
	{
		return m_width;
	}
	
	void CCLabelBMFontMultiline::setAlign(CCLabelBMFontMultilineAlignment align)
	{
		m_align = align;
		this->createFontChars();
	}
	
	CCLabelBMFontMultilineAlignment CCLabelBMFontMultiline::getAlign()
	{
		return m_align;
	}
}
