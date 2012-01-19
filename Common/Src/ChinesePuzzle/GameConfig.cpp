/**
 *  GameConfig.cpp
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

#include "GameConfig.h"

#include <stdio.h>

using namespace cocos2d;

GameConfigCommon::GameConfigCommon() :
moves(new std::vector<MoveCoord>())
{
	
}

GameConfigCommon::~GameConfigCommon()
{
	delete moves;
}

bool GameConfigCommon::init()
{
	this->resolution = std::string("480x320");
	//this->resolution = std::string("1920x1200");
	this->theme = std::string("classic");
	this->isSoundOn = true;
	
	return true;
}

CCSize GameConfigCommon::getResolutionSize()
{
	CCSize resolution = CCSizeZero;
	if(sscanf(this->resolution.c_str(), "%fx%f", &resolution.width, &resolution.height)) return resolution;
	else return CCSizeZero;
}

std::string GameConfigCommon::getRootPath(const char* file)
{
	return std::string(file);
}

std::string GameConfigCommon::getResolutionPath(const char* file)
{
	return this->resolution + std::string("/") + std::string(file);
}

std::string GameConfigCommon::getUiPath(const char* file)
{
	return this->resolution + std::string("/ui/") + std::string(file);
}

std::string GameConfigCommon::getThemePath(const char* file)
{
	return this->resolution + std::string("/themes/") + this->theme + std::string("/") + std::string(file);
}

std::string GameConfigCommon::getFontPath(const char* file)
{
	return std::string("fonts/") + file;
}

