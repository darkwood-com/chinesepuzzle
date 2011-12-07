/**
 *  MenuItem.cpp
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


#include "MenuItem.h"
#include <sstream>

using namespace cocos2d;

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

static int nb = 0;

bool MenuItem::init()
{
	std::stringstream label;
	label << "Item " << ++nb;
	
	CCLabelTTF* itemBtn = new CCLabelTTF();
	itemBtn->initWithString(label.str().c_str(), "Arial", 12);
	itemBtn->setPosition(ccp(0, 0));
	this->addChild(itemBtn);
	
	return true;
}

void MenuItem::draw(void)
{
	CCSize size = this->getContentSize();
	
	CCNode::draw();
	
	CCPoint vertices[] = {
		CCPoint(0, 0),
		CCPoint(size.width, 0),
		CCPoint(size.width, size.height),
		CCPoint(0, size.height),
	};
	
	ccDrawPoly(vertices, 4, true);
}