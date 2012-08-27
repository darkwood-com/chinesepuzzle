/**
 *  CCLang.h
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

#ifndef  _CCLANG_H_
#define  _CCLANG_H_

#include "cocos2d.h"

class CC_DLL CCLang : public cocos2d::CCObject
{
private:
	CCLang();
	virtual ~CCLang();
	
protected:
	cocos2d::CCDictionary<std::string, cocos2d::CCString*>* m_oData;

public:
	CC_SYNTHESIZE(cocos2d::ccLanguageType, lang, Lang);
	
	const char* get(const std::string& key);
	void set(const std::string& key, cocos2d::CCString* value);
	
	void addLang(const char *pFileName);
	
	static CCLang* sharedLang();
};

#endif // _CCLANG_H_

