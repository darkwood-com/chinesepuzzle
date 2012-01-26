/**
 *  cpStruct.h
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

#ifndef __CP_STRUCT_H__
#define __CP_STRUCT_H__

//chinese puzzle struct

#include <vector>
#include <map>
#include "Archivist.h"

class CardPlay;

struct GridCoord {
	int i;
	int j;
	
	bool operator<( const GridCoord & g ) const
	{
		return i < g.i || (i == g.i && j < g.j);
	}
	
	ArchiveAttributes( i, j );
};

struct MoveCoord {
	GridCoord from;
	GridCoord to;
	
	Archivist::Object Encode( void ) const
	{
		Archivist::Object data;
		data["from"] = Archivist::Encode(from);
		data["to"] = Archivist::Encode(to);
		
		return data;
	}
	
	void Decode( const Archivist::Object & data )
	{
		Archivist::Decode(data["from"], from);
		Archivist::Decode(data["to"], to);
	}
};

typedef std::vector<MoveCoord> Moves;
typedef std::map<GridCoord, CardPlay*> Board;

#endif // __CP_STRUCT_H__

