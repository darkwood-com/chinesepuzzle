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
#include "CardPlay.h"

using namespace cocos2d;

GameConfigCommon::GameConfigCommon() :
moves(new Moves()),
initBoard(new Board())
{
	
}

GameConfigCommon::~GameConfigCommon()
{
	delete moves;
	delete initBoard;
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

struct CardPlayStruct {
	CardPlayColor color;
	CardPlayRank rank;
	
	CardPlayStruct() :
	color(CardPlayColorSpade),
	rank(CardPlayRankAce)
	{
	}
	
	CardPlayStruct(CardPlay* card)
	{
		color = card->getColor();
		rank = card->getRank();
	}
	
	bool operator<( const CardPlayStruct & c ) const
	{
		return color < c.color || (color == c.color && rank < c.rank);
	}
	
	virtual Archivist::Object Encode( void ) const
	{
		Archivist::Object data;
		data["color"] = Archivist::Encode(CardPlay::matchColor(color));
		data["rank"] = Archivist::Encode(CardPlay::matchRank(rank));
		return data;
	}
	
	virtual void Decode( const Archivist::Object & data )
	{
		std::string sColor, sRank;
		Archivist::Decode(data["color"], sColor);
		Archivist::Decode(data["rank"], sRank);
		
		color = CardPlay::matchColor(sColor);
		rank = CardPlay::matchRank(sRank);
	}
};

Archivist::Object GameConfigCommon::Encode( void ) const
{
	Archivist::Object data;
	data["resolution"] = Archivist::Encode(resolution);
	data["theme"] = Archivist::Encode(theme);
	data["isSoundOn"] = Archivist::Encode(isSoundOn);
	data["moves"] = Archivist::Encode(*moves);
	
	Archivist::Array board;
	for(Board::const_iterator it = initBoard->begin(); it != initBoard->end(); ++it)
	{
		Archivist::Object coordCard;
		coordCard["coord"] = Archivist::Encode(it->first);
		coordCard["card"] = Archivist::Encode(CardPlayStruct(it->second));
		board.Insert(coordCard);
	}
	data["board"] = board;
	
	return data;
}

void GameConfigCommon::Decode( const Archivist::Object & data )
{
	std::multimap<CardPlayStruct,CardPlay*> mapCard; //keep card instance comparison with card pointer
	for(Board::const_iterator it = initBoard->begin(); it != initBoard->end(); ++it)
	{
		mapCard.insert(std::pair<CardPlayStruct, CardPlay*>(CardPlayStruct(it->second), it->second));
	}
	
	moves->clear();
	initBoard->clear();
	
	Archivist::Decode(data["resolution"], resolution);
	Archivist::Decode(data["theme"], theme);
	Archivist::Decode(data["isSoundOn"], isSoundOn);
	Archivist::Decode(data["moves"], *moves);
	
	Archivist::Array board = data["board"];
	for (Archivist::Array::ConstIterator it = board.Begin(); it != board.End(); ++it)
	{
		Archivist::Object coordCard = *it;
		GridCoord coord; Archivist::Decode(coordCard["coord"], coord);
		CardPlayStruct card; Archivist::Decode(coordCard["card"], card);
		
		std::map<CardPlayStruct,CardPlay*>::iterator mapIt = mapCard.find(card);
		if(mapIt != mapCard.end())
		{
			(*initBoard)[coord] = mapIt->second;
			mapCard.erase(mapIt);
		}
	}
}

bool GameConfigCommon::save()
{
	Archivist::Archive::Save(CCFileUtils::getWriteablePath() + XML_FILE_NAME, this->Encode());
	
	return true;
}

bool GameConfigCommon::load()
{
	Archivist::Unknown data = Archivist::Archive::Load(CCFileUtils::getWriteablePath() + XML_FILE_NAME);
	if(data.Type() != Archivist::Type::Null)
	{
		this->Decode(data);
	}
	
	return true;
}
