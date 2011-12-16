/**
 *  BoardCard.cpp
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


#include "BoardCard.h"

using namespace cocos2d;

BoardCard::BoardCard()
{
}

BoardCard::~BoardCard()
{
}

bool BoardCard::init()
{
	emptyTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("Data/themes/classic/480x320/boardcard.png")).c_str());
	yesTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("Data/themes/classic/480x320/boardcardno.png")).c_str());
	noTexture = CCTextureCache::sharedTextureCache()->addImage((std::string("Data/themes/classic/480x320/boardcardyes.png")).c_str());
	
	if(!CCSprite::initWithTexture(emptyTexture))
	{
		return false;
	}
	
	return true;
}