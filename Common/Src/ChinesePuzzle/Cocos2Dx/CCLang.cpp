/**
 *  CCLang.cpp
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

#include "CCLang.h"

USING_NS_CC;

CCLang::CCLang()
{
	m_oData = new CCDictionary<std::string, cocos2d::CCString*>();
}

CCLang::~CCLang()
{
	CC_SAFE_RELEASE(m_oData);
}

const char* CCLang::get(const std::string& key)
{
	CCString* value = m_oData->objectForKey(key);
	return (value) ? value->m_sString.c_str() : key.c_str();
}

void CCLang::set(const std::string& key, cocos2d::CCString* value)
{
	m_oData->setObject(value, key);
}

void CCLang::addLang(const char* pFileName)
{
	std::string pFilePath = CCFileUtils::fullPathFromRelativePath(pFileName);
	
	switch(lang)
	{
		case kLanguageFrench: pFilePath += "-fr"; break;
		case kLanguageGerman: pFilePath += "-de"; break;
		case kLanguageEnglish:
		default: pFilePath += "-en"; break;
	}
	
	const char* pPath = CCFileUtils::fullPathFromRelativePath((pFilePath + ".plist").c_str());
	CCDictionary<std::string, cocos2d::CCObject*>* dict = CCFileUtils::dictionaryWithContentsOfFile(pPath);
	
	std::vector<std::string> keys = dict->allKeys();
	for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
	{
		CCString* value = dynamic_cast<CCString*>(dict->objectForKey(*it));
		if(value)
		{
			set(*it, value);
		}
	}
}

CCLang* CCLang::sharedLang()
{
    static CCLang sharedLang;
    
    return &sharedLang;
}