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
#ifndef __CCBITMAPMULTILINE_FONT_ATLAS_H__
#define __CCBITMAPMULTILINE_FONT_ATLAS_H__
#include "CCLabelBMFont.h"
namespace cocos2d{
	
	typedef enum {
		CCLabelBMFontMultilineCenterAlignment,
		CCLabelBMFontMultilineLeftAlignment,
		CCLabelBMFontMultilineRightAlignment
	} CCLabelBMFontMultilineAlignment;
	
	class CC_DLL CCLabelBMFontMultiline  : public CCSpriteBatchNode, public CCLabelProtocol, public CCRGBAProtocol
	{
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY(GLubyte, m_cOpacity, Opacity)
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color)
		/** conforms to CCRGBAProtocol protocol */
		CC_PROPERTY(bool, m_bIsOpacityModifyRGB, IsOpacityModifyRGB)
	protected:
		// string to render
		std::string m_sString;
		CCBMFontConfiguration *m_pConfiguration;
	public:
		CCLabelBMFontMultiline()
		: m_cOpacity(0)           
		, m_bIsOpacityModifyRGB(false)
		, m_sString("")
		, m_pConfiguration(NULL)
		{}
		virtual ~CCLabelBMFontMultiline();
		/** Purges the cached data.
		 Removes from memory the cached configurations and the atlas name dictionary.
		 @since v0.99.3
		 */
		static void purgeCachedData();
		/** creates a bitmap font altas with an initial string and the FNT file */
		static CCLabelBMFontMultiline * labelWithString(const char *str, const char *fntFile, float width, CCLabelBMFontMultilineAlignment align);

		/** init a bitmap font altas with an initial string and the FNT file */
		bool initWithString(const char *str, const char *fntFile, float width, CCLabelBMFontMultilineAlignment align);
		/** updates the font chars based on the string to render */
		void createFontChars();
		int substrlenInPixels(char *);

		// super method
		virtual void setString(const char *label);
		virtual const char* getString(void);
        virtual void setCString(const char *label);
		virtual void setAnchorPoint(const CCPoint& var);
		
#if CC_LABELBMFONT_DEBUG_DRAW
		virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW
		
		CC_PROPERTY(float, m_width, Width);
		CC_PROPERTY(CCLabelBMFontMultilineAlignment, m_align, Align);
	private:
		std::string m_sfntFile;
		char * atlasNameFromFntFile(const char *fntFile);
		int kerningAmountForFirst(unsigned short first, unsigned short second);

	};
	
}// namespace cocos2d

#endif //__CCBITMAPMULTILINE_FONT_ATLAS_H__
