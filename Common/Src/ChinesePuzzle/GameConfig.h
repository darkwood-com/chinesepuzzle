/**
 *  GameConfig.h
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

#ifndef __GAME_CONFIG_COMMON_H__
#define __GAME_CONFIG_COMMON_H__

#include <stdio.h>
#include "cpMacro.h"

class CC_DLL GameConfigCommon : public cocos2d::CCObject
{
public:
	GameConfigCommon();
	virtual ~GameConfigCommon();
	
	virtual bool init();
	std::string getRootPath(const char* file);
	std::string getResolutionPath(const char* file);
	std::string getUiPath(const char* file);
	std::string getThemePath(const char* file);
	
	CC_SYNTHESIZE(std::string, resolution, Resolution);
	CC_SYNTHESIZE(std::string, theme, Theme);
};

#include CP_PLATFORM(GameConfig)
 
#endif // __GAME_CONFIG_COMMON_H__
