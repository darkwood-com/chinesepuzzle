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
#include <stdlib.h>
#include "CardPlay.h"

#include "JSPP/src/object.h"
#include "JSPP/src/underscore.h"
#include "JSPP/src/operators.h"
#include "JSPP/src/constructors.h"

struct varContainer
{
	var o01, o02, o03, o04, o05, o06, o07, o08;
	var o09, o10, o11, o12, o13, o14, o15, o16;
	var o17, o18, o19, o20, o21, o22, o23, o24; 
	var o25, o26, o27, o28, o29, o30, o31, o32;
};

var array(const varContainer& c)
{
	std::vector<var> list;
	if(c.o01.s->type != JSPP_UNDEFINED) list.push_back(c.o01);
	if(c.o02.s->type != JSPP_UNDEFINED) list.push_back(c.o02);
	if(c.o03.s->type != JSPP_UNDEFINED) list.push_back(c.o03);
	if(c.o04.s->type != JSPP_UNDEFINED) list.push_back(c.o04);
	if(c.o05.s->type != JSPP_UNDEFINED) list.push_back(c.o05);
	if(c.o06.s->type != JSPP_UNDEFINED) list.push_back(c.o06);
	if(c.o07.s->type != JSPP_UNDEFINED) list.push_back(c.o07);
	if(c.o08.s->type != JSPP_UNDEFINED) list.push_back(c.o08);
	if(c.o09.s->type != JSPP_UNDEFINED) list.push_back(c.o09);
	if(c.o10.s->type != JSPP_UNDEFINED) list.push_back(c.o10);
	if(c.o11.s->type != JSPP_UNDEFINED) list.push_back(c.o11);
	if(c.o12.s->type != JSPP_UNDEFINED) list.push_back(c.o12);
	if(c.o13.s->type != JSPP_UNDEFINED) list.push_back(c.o13);
	if(c.o14.s->type != JSPP_UNDEFINED) list.push_back(c.o14);
	if(c.o15.s->type != JSPP_UNDEFINED) list.push_back(c.o15);
	if(c.o16.s->type != JSPP_UNDEFINED) list.push_back(c.o16);
	if(c.o17.s->type != JSPP_UNDEFINED) list.push_back(c.o17);
	if(c.o18.s->type != JSPP_UNDEFINED) list.push_back(c.o18);
	if(c.o19.s->type != JSPP_UNDEFINED) list.push_back(c.o19);
	if(c.o20.s->type != JSPP_UNDEFINED) list.push_back(c.o20);
	if(c.o21.s->type != JSPP_UNDEFINED) list.push_back(c.o21);
	if(c.o22.s->type != JSPP_UNDEFINED) list.push_back(c.o22);
	if(c.o23.s->type != JSPP_UNDEFINED) list.push_back(c.o23);
	if(c.o24.s->type != JSPP_UNDEFINED) list.push_back(c.o24);
	if(c.o25.s->type != JSPP_UNDEFINED) list.push_back(c.o25);
	if(c.o26.s->type != JSPP_UNDEFINED) list.push_back(c.o26);
	if(c.o27.s->type != JSPP_UNDEFINED) list.push_back(c.o27);
	if(c.o28.s->type != JSPP_UNDEFINED) list.push_back(c.o28);
	if(c.o29.s->type != JSPP_UNDEFINED) list.push_back(c.o29);
	if(c.o30.s->type != JSPP_UNDEFINED) list.push_back(c.o30);
	if(c.o31.s->type != JSPP_UNDEFINED) list.push_back(c.o31);
	if(c.o32.s->type != JSPP_UNDEFINED) list.push_back(c.o32);
	return var(list);
}

#define _$(...) array((varContainer)__VA_ARGS__)

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

/*
var addThemeSelected(var sprites)
{
	if(sprites.get_key("menuItemThemeSelect") != undefined)
	{
		if(sprites.get_key("menuItemThemeClassic") != undefined)
		{
			sprites["menuItemThemeClassicSelect"] = _$({sprites["menuItemThemeClassic"][0], sprites["menuItemThemeSelect"][0]});
		}
		
		if(sprites.get_key("menuItemThemeChinese") != undefined)
		{
			sprites["menuItemThemeChineseSelect"] = _$({sprites["menuItemThemeChinese"][0], sprites["menuItemThemeSelect"][0]});
		}
	}
	
	return sprites;
}

var midPoint(var point)
{
	point["to"] = _$({
		point["to"][0] - point["from"][2] / 2,
		point["to"][1] - point["from"][3] / 2
	});
    return point;
}

var card480x320(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({53,73,93,112});
    var txtRankLine = _$({516,8,526,7,535,7,544,7,553,7,562,7,571,7,580,7,589,7,597,9,608,7,616,10,627,7});
    var shapeColorBig = _$({_$({480,52,15,16}),_$({481,70,12,17}),_$({480,90,14,17}),_$({480,110,16,16})});
    var shapeColorSmall = _$({_$({501,54,9,10}),_$({502,74,8,10}),_$({502,93,9,10}),_$({501,113,10,10})});
	
    return _$({
		_$({_["from"] = _$({480,0,26,36}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],13}), _["to"] = _$({8,27})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({13,11})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({18,27})})), //color right
    });
}

var card960x640(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({106,146,186,224});
    var txtRankLine = _$({1032,16,1052,14,1070,14,1088,14,1106,14,1124,14,1142,14,1160,14,1178,14,1194,18,1216,14,1232,20,1254,14});
    var shapeColorBig = _$({_$({960,104,30,32}),_$({962,140,24,34}),_$({960,180,28,34}),_$({960,220,32,32})});
    var shapeColorSmall = _$({_$({1002,108,18,20}),_$({1004,148,16,20}),_$({1004,186,18,20}),_$({1002,226,20,20})});
	
    return _$({
		_$({_["from"] = _$({960,0,52,72}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],26}), _["to"] = _$({16,54})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({26,22})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({36,54})})), //color right
    });
}

var card1024x768(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({143,185,231,273});
    var txtRankLine = _$({1102,18,1123,14,1143,14,1162,15,1183,15,1203,14,1223,14,1243,14,1263,14,1281,20,1304,14,1320,21,1343,15});
    var shapeColorBig = _$({_$({1024,140,31,34}),_$({1027,181,26,36}),_$({1025,224,30,36}),_$({1024,267,34,34})});
    var shapeColorSmall = _$({_$({1071,146,19,21}),_$({1073,189,16,22}),_$({1072,231,18,22}),_$({1070,274,21,21})});
	
    return _$({
		_$({_["from"] = _$({1024,0,56,78}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],27}), _["to"] = _$({17,58})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({28,24})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({39,58})})), //color right
    });
}

var card1280x800(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({143,185,231,273});
    var txtRankLine = _$({1358,18,1379,14,1399,14,1418,15,1439,15,1459,14,1479,14,1499,14,1519,14,1537,20,1560,14,1576,21,1599,15});
    var shapeColorBig = _$({_$({1280,140,31,34}),_$({1283,181,26,36}),_$({1281,224,30,36}),_$({1280,267,34,34})});
    var shapeColorSmall = _$({_$({1327,146,19,21}),_$({1329,189,16,22}),_$({1328,231,18,22}),_$({1326,274,21,21})});
	
    return _$({
		_$({_["from"] = _$({1280,0,56,78}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],27}), _["to"] = _$({17,58})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({28,24})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({39,58})})), //color right
    });
}

var card1280x1024(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({145,194,246,296});
    var txtRankLine = _$({1370,20,1395,16,1418,16,1441,18,1464,17,1488,16,1512,16,1536,16,1559,16,1580,23,1608,16,1627,24,1655,17});
    var shapeColorBig = _$({_$({1280,142,37,40}),_$({1284,190,31,42}),_$({1282,239,35,42}),_$({1280,290,40,40})});
    var shapeColorSmall = _$({_$({1336,149,22,24}),_$({1336,198,19,26}),_$({1336,248,21,26}),_$({1334,298,24,24})});
	
    return _$({
		_$({_["from"] = _$({1280,0,66,92}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],31}), _["to"] = _$({18,68})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({32,28})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({46,68})})), //color right
    });
}

var card1366x768(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({143,185,231,273});
    var txtRankLine = _$({1444,18,1465,14,1485,14,1504,15,1525,15,1545,14,1565,14,1585,14,1605,14,1623,20,1646,14,1662,21,1685,15});
    var shapeColorBig = _$({_$({1366,140,31,34}),_$({1369,181,26,36}),_$({1367,224,30,36}),_$({1366,267,34,34})});
    var shapeColorSmall = _$({_$({1413,146,19,21}),_$({1415,189,16,22}),_$({1414,231,18,22}),_$({1412,274,21,21})});
	
    return _$({
		_$({_["from"] = _$({1366,0,56,78}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],27}), _["to"] = _$({17,58})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({28,24})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({39,58})})), //color right
    });
}

var card1440x900(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({145,194,246,296});
    var txtRankLine = _$({1530,20,1555,16,1578,16,1601,18,1624,17,1648,16,1672,16,1696,16,1719,16,1740,23,1768,16,1787,24,1815,17});
    var shapeColorBig = _$({_$({1440,142,37,40}),_$({1444,190,31,42}),_$({1442,239,35,42}),_$({1440,290,40,40})});
    var shapeColorSmall = _$({_$({1496,149,22,24}),_$({1496,198,19,26}),_$({1496,248,21,26}),_$({1494,298,24,24})});
	
    return _$({
		_$({_["from"] = _$({1440,0,66,92}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],31}), _["to"] = _$({18,68})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({32,28})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({46,68})})), //color right
    });
}

var card1680x1050(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({146,200,258,312});
    var txtRankLine = _$({1780,22,1808,17,1833,17,1858,19,1884,18,1910,17,1936,17,1962,17,1987,17,2010,25,2040,17,2060,26,2090,18});
    var shapeColorBig = _$({_$({1680,142,41,43}),_$({1685,194,35,47}),_$({1682,249,39,46}),_$({1680,305,44,43})});
    var shapeColorSmall = _$({_$({1741,150,25,26}),_$({1743,204,21,28}),_$({1742,258,24,28}),_$({1740,313,27,26})});
	
    return _$({
		_$({_["from"] = _$({1680,0,73,100}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34}), _["to"] = _$({22,76})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({36,30})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({51,76})})), //color right
    });
}

var card1920x1080(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({146,200,258,312});
    var txtRankLine = _$({2020,22,2048,17,2073,17,2098,19,2124,18,2150,17,2176,17,2202,17,2227,17,2250,25,2280,17,2300,26,2330,18});
    var shapeColorBig = _$({_$({1920,142,41,43}),_$({1925,194,35,47}),_$({1922,249,39,46}),_$({1920,305,44,43})});
    var shapeColorSmall = _$({_$({1981,150,25,26}),_$({1983,204,21,28}),_$({1982,258,24,28}),_$({1980,313,27,26})});
	
    return _$({
		_$({_["from"] = _$({1920,0,73,100}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34}), _["to"] = _$({22,76})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({36,30})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({51,76})})), //color right
    });
}

var card1920x1200(var This, var colorIndex, var rankIndex)
{
    var txtColorLine = _$({146,200,258,312});
    var txtRankLine = _$({2020,22,2048,17,2073,17,2098,19,2124,18,2150,17,2176,17,2202,17,2227,17,2250,25,2280,17,2300,26,2330,18});
    var shapeColorBig = _$({_$({1920,142,41,43}),_$({1925,194,35,47}),_$({1922,249,39,46}),_$({1920,305,44,43})});
    var shapeColorSmall = _$({_$({1981,150,25,26}),_$({1983,204,21,28}),_$({1982,258,24,28}),_$({1980,313,27,26})});
	
    return _$({
		_$({_["from"] = _$({1920,0,73,100}), _["to"] = _$({0,0})}), //card bg
		midPoint(_$({_["from"] = _$({txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34}), _["to"] = _$({22,76})})), //rank left
		midPoint(_$({_["from"] = shapeColorBig[colorIndex], _["to"] = _$({36,30})})), //color center
		midPoint(_$({_["from"] = shapeColorSmall[colorIndex], _["to"] = _$({51,76})})), //color right
    });
}
*/

//internal json data like parser
void GameConfigCommon::getNodePath(std::string mode, const char* file, CCSpriteBatchNode* sprite)
{
	static CCMutableDictionary<std::string, CCSpriteBatchNode*>* sGameConfigBatchNodePath = new CCMutableDictionary<std::string, CCSpriteBatchNode*>();
	
	std::string path = resolution  + "/" + ((mode == "theme") ? "themes/" + theme : "ui");
	std::string plistPath = path + ".plist";
	std::string texturePath = path + ".png";
	std::string nodePath = path  + ":" + file;
	CCSpriteBatchNode* node = sGameConfigBatchNodePath->objectForKey(nodePath);
	if(node == NULL)
	{
		/*
		var data = _$({
			_["480x320"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,480,320}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({480,0,96,96}),		_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({480,96,84,28}),		_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({480,139,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({480,183,36,36}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({480,230,90,72}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,480,320}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({528,0,26,36}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({576,0,26,36}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({624,0,26,36}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({672,0,26,36}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({720,0,26,36}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({480,158,36,36}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({528,158,36,36}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({576,158,36,36}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({624,158,36,36}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({624,208,36,36}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({672,158,36,36}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({720,158,36,36}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card480x320
			}),
			_["960x640"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,960,640}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({960,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({960,192,100,36}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({960,278,100,36}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({960,366,72,72}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({960,460,180,144}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,960,640}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1056,0,52,72}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1152,0,52,72}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1248,0,52,72}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1344,0,52,72}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1440,0,52,72}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({960,316,72,72}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1056,316,72,72}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1152,316,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1248,316,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1248,416,72,72}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1344,316,72,72}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1440,316,72,72}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card960x640
			}),
			_["1024x768"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1024,768}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1024,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1024,192,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1024,222,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1024,257,55,55}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1024,320,195,156}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1024,768}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1100,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1176,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1252,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1328,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1404,0,56,78}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1024,380,56,56}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1100,380,56,56}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1176,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1252,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1252,451,56,56}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1328,380,56,56}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1404,380,56,56}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1024x768
			}),
			_["1280x800"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1280,800}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1280,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1280,192,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1280,222,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1280,257,55,55}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1280,320,195,156}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1280,800}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1356,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1432,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1508,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1584,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1660,0,56,78}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1280,380,56,56}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1356,380,56,56}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1432,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1508,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1508,451,56,56}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1584,380,56,56}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1660,380,56,56}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1280x800
			}),
			_["1280x1024"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1280,1024}),	_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1280,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1280,192,96,32}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1280,235,96,32}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1280,279,64,64}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1280,360,228,182}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1280,1024}),	_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1358,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1436,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1514,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1592,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1670,0,66,92}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1280,400,64,64}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1358,400,64,64}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1436,400,64,64}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1514,400,64,64}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1514,480,64,64}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1592,400,64,64}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1670,400,64,64}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1280x1024
			}),
			_["1366x768"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1366,768}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1366,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1366,192,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1366,222,84,28}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1366,257,55,55}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1366,320,195,156}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1366,768}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1442,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1518,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1594,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1670,0,56,78}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1746,0,56,78}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1366,380,56,56}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1442,380,56,56}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1518,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1594,380,56,56}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1594,451,56,56}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1670,380,56,56}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1746,380,56,56}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1366x768
			}),
			_["1440x900"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1440,900}),		_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1440,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1440,192,96,32}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1440,235,96,32}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1440,279,64,64}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1440,360,228,182}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1440,900}),		_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1518,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1596,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1674,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({1752,0,66,92}),		_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({1830,0,66,92}),		_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1440,400,64,64}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1518,400,64,64}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1596,400,64,64}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1674,400,64,64}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1674,480,64,64}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({1752,400,64,64}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({1830,400,64,64}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1440x900
			}),
			_["1680x1050"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1680,1050}),	_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1680,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1680,196,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1680,235,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1680,279,72,72}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1680,360,250,200}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1680,1050}),	_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({1760,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({1840,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({1920,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({2000,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({2080,0,73,100}),	_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1680,400,72,72}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({1768,400,72,72}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({1856,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({1944,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({1944,490,72,72}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({2032,400,72,72}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({2120,400,72,72}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1680x1050
			}),
			_["1920x1080"] = _$({
				_["ui"] = _$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1920,1080}),	_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1920,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1920,196,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1920,235,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1920,279,72,72}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1920,360,250,200}),	_["to"] = _$({0,0})})}),
				}),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1920,1080}),	_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({2000,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({2080,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({2160,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({2240,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({2320,0,73,100}),	_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1920,400,72,72}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({2008,400,72,72}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({2096,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({2184,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({2184,490,72,72}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({2272,400,72,72}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({2360,400,72,72}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1920x1080
			}),
			_["1920x1200"] = _$({
				_["ui"] = addThemeSelected(_$({
					_["menuMask"] =						_$({_$({_["from"] = _$({0,0,1920,1200}),	_["to"] = _$({0,0})})}),
					_["menuContainer"] =				_$({_$({_["from"] = _$({1920,0,192,192}),	_["to"] = _$({0,0})})}),
					_["menuItemYes"] =					_$({_$({_["from"] = _$({1920,196,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemNo"] =					_$({_$({_["from"] = _$({1920,235,107,36}),	_["to"] = _$({0,0})})}),
					_["menuItemOk"] =					_$({_$({_["from"] = _$({1920,279,72,72}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeSelect"] =			_$({_$({_["from"] = _$({1920,360,250,200}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeClassic"] =			_$({_$({_["from"] = _$({1920,560,250,200}),	_["to"] = _$({0,0})})}),
					_["menuItemThemeChinese"] =			_$({_$({_["from"] = _$({1920,760,250,200}),	_["to"] = _$({0,0})})}),
				})),
				_["theme"] = _$({
					_["bg"] =							_$({_$({_["from"] = _$({0,0,1920,1200}),	_["to"] = _$({0,0})})}),
					_["cardplaybg"] =					_$({_$({_["from"] = _$({2000,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardempty"] =				_$({_$({_["from"] = _$({2080,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardyes"] =					_$({_$({_["from"] = _$({2160,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardboardno"] =					_$({_$({_["from"] = _$({2240,0,73,100}),	_["to"] = _$({0,0})})}),
					_["cardtouched"] =					_$({_$({_["from"] = _$({2320,0,73,100}),	_["to"] = _$({0,0})})}),
					_["newBtn"] =						_$({_$({_["from"] = _$({1920,400,72,72}),	_["to"] = _$({0,0})})}),
					_["retryBtn"] =						_$({_$({_["from"] = _$({2008,400,72,72}),	_["to"] = _$({0,0})})}),
					_["hintBtn"] =						_$({_$({_["from"] = _$({2096,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOnBtn"] =					_$({_$({_["from"] = _$({2184,400,72,72}),	_["to"] = _$({0,0})})}),
					_["soundOffBtn"] =					_$({_$({_["from"] = _$({2184,490,72,72}),	_["to"] = _$({0,0})})}),
					_["themeBtn"] =						_$({_$({_["from"] = _$({2272,400,72,72}),	_["to"] = _$({0,0})})}),
					_["undoBtn"] =						_$({_$({_["from"] = _$({2360,400,72,72}),	_["to"] = _$({0,0})})}),
				}),
				_["card"] = &card1920x1200
			}),
		});
		
		var sprites = _$({});
		if(mode == 0)
		{
			sprites = data[resolution]["ui"];
		}
		else if(mode == 1)
		{
			sprites = data[resolution]["theme"];
			
			var colors = _$({"D","S","H","C"});
            var ranks = _$({"A","2","3","4","5","6","7","8","9","10","J","Q","K"});
			for (var colorIndex = 0; colorIndex < colors["length"]; ++colorIndex)
			{
				for (var rankIndex = 0; rankIndex < ranks["length"]; ++rankIndex)
				{
					sprites[std::string("card_") + colors[colorIndex].s->s + ranks[rankIndex].s->s] = data[resolution]["card"](colorIndex, rankIndex);
				}
			}
		}
		
		std::string spritePath = resolution  + "/" + ((mode == 1) ? "themes/" + theme : "ui") + ".png";
		for(std::map<std::string, var>::iterator sprite = sprites.begin(); sprite != sprites.end(); ++sprite)
		{
			if(sprite->second != undefined)
			{
				node = CCSpriteBatchNode::batchNodeWithFile(spritePath.c_str());
				
				CCSize nodeSize;
				for (var zone = 0; zone < sprite->second["length"]; ++zone)
				{
					CCRect zoneRect;
					zoneRect.origin = ccp(sprite->second[zone]["from"][0].s->n, sprite->second[zone]["from"][1].s->n);
					zoneRect.size = CCSizeMake(sprite->second[zone]["from"][2].s->n, sprite->second[zone]["from"][3].s->n);
					CCPoint zonePosition = ccp(sprite->second[zone]["to"][0].s->n, sprite->second[zone]["to"][1].s->n);
					nodeSize.width = std::max(zonePosition.x + zoneRect.size.width, nodeSize.width);
					nodeSize.height = std::max(zonePosition.y + zoneRect.size.height, nodeSize.height);
					
					CCSprite* zoneSprite = CCSprite::spriteWithBatchNode(node, zoneRect);
					zoneSprite->setAnchorPoint(ccp(0, 0));
					zoneSprite->setPosition(zonePosition);
					node->addChild(zoneSprite);
				}
				node->setContentSize(nodeSize);
				
				sGameConfigBatchNodePath->setObject(node, spritePath + ":" + sprite->first);
			}
		}
		*/
		CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		spriteFrameCache->addSpriteFramesWithFile(plistPath.c_str());
		
		var sprites = _$({});
		if(mode == "ui")
		{
			sprites = _$({
				_["menuMask"] =				"auto",
				_["menuContainer"] =		"auto",
				_["menuItemYes"] =			"auto",
				_["menuItemNo"] =			"auto",
				_["menuItemOk"] =			"auto",
				_["menuItemThemeClassic"] =	"auto",
			});
		}
		else if(mode == "theme")
		{
			sprites = _$({
				_["bg"] =					"auto",
				_["cardplaybg"] =			"auto",
				_["cardboardempty"] =		"auto",
				_["cardboardyes"] =			"auto",
				_["cardboardno"] =			"auto",
				_["cardtouched"] =			"auto",
				_["newBtn"] =				"auto",
				_["retryBtn"] =				"auto",
				_["hintBtn"] =				"auto",
				_["soundOnBtn"] =			"auto",
				_["soundOffBtn"] =			"auto",
				_["themeBtn"] =				"auto",
				_["undoBtn"] =				"auto",
			});
			
			CCSprite* cardBgSprite = CCSprite::spriteWithSpriteFrameName("cardbg.png");
			CCRect box = cardBgSprite->boundingBox();
			
			var colors = _$({"D","S","H","C"});
            var ranks = _$({"A","2","3","4","5","6","7","8","9","10","J","Q","K"});
			for (var colorIndex = 0; colorIndex < colors["length"]; ++colorIndex)
			{
				for (var rankIndex = 0; rankIndex < ranks["length"]; ++rankIndex)
				{
					sprites[var("card_") + colors[colorIndex] + ranks[rankIndex]] = _$({
						_$({_["from"] = "cardbg", _["to"] = _$({0,0})}),
						_$({
							_["from"] = var("rank_") + colors[colorIndex] + ranks[rankIndex],
							_["to"] = _$({1.0 * box.size.width / 4, 3.0 * box.size.height / 4}),
							_["anchor"] = _$({0.5, 0.5}),
						}),
						_$({
							_["from"] = var("big_") + colors[colorIndex],
							_["to"] = _$({2.0 * box.size.width / 4, 1.0 * box.size.height / 4}),
							_["anchor"] = _$({0.5, 0.5}),
						}),
						_$({
							_["from"] = var("small_") + colors[colorIndex],
							_["to"] = _$({3.0 * box.size.width / 4, 3.0 * box.size.height / 4}),
							_["anchor"] = _$({0.5, 0.5}),
						}),
					});
				}
			}
		}
		
		for(std::map<std::string, var>::iterator sprite = sprites.begin(); sprite != sprites.end(); ++sprite)
		{
			if(sprite->second != undefined)
			{
				if(sprite->second == "auto")
				{
					sprite->second = _$({_$({
						_["from"] = var(sprite->first),
						_["to"] = _$({0,0})
					})});
				}
				
				node = CCSpriteBatchNode::batchNodeWithFile(texturePath.c_str());
				
				CCSize nodeSize;
				for (var zone = 0; zone < sprite->second["length"]; ++zone)
				{
					if(sprite->second[zone]["anchor"] == undefined)
					{
						sprite->second[zone]["anchor"] = _$({0, 0});
					}
					
					CCPoint zonePosition = ccp(sprite->second[zone]["to"][0].s->n, sprite->second[zone]["to"][1].s->n);
					CCPoint zoneAnchor = ccp(sprite->second[zone]["anchor"][0].s->n, sprite->second[zone]["anchor"][1].s->n);
					
					CCSprite* zoneSprite = CCSprite::spriteWithSpriteFrameName((sprite->second[zone]["from"] + ".png").toString().c_str());
					zoneSprite->setAnchorPoint(zoneAnchor);
					zoneSprite->setPosition(zonePosition);
					node->addChild(zoneSprite);
					
					CCRect box = zoneSprite->boundingBox();
					nodeSize.width = std::max(box.origin.x + box.size.width, nodeSize.width);
					nodeSize.height = std::max(box.origin.y + box.size.height, nodeSize.height);
				}
				node->setContentSize(nodeSize);
				
				sGameConfigBatchNodePath->setObject(node, path + ":" + sprite->first);
			}
		}
		
		node = sGameConfigBatchNodePath->objectForKey(nodePath);
	}
	
	if(node)
	{
		copySpriteBatchNode(node, sprite);
	}
}

void GameConfigCommon::getNodeUiPath(const char* file, CCSpriteBatchNode* sprite)
{
	getNodePath("ui", file, sprite);
}

void GameConfigCommon::getNodeThemePath(const char* file, CCSpriteBatchNode* sprite)
{
	getNodePath("theme", file, sprite);
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
	initBoard->begin();
	GridCoord gridKey;
	CardPlay* cardValue = NULL;
	while((cardValue = initBoard->next(&gridKey)))
	{
		Archivist::Object coordCard;
		coordCard["coord"] = Archivist::Encode(gridKey);
		coordCard["card"] = Archivist::Encode(CardPlayStruct(cardValue));
		board.Insert(coordCard);
	}
	initBoard->end();
	data["board"] = board;
	
	return data;
}

void GameConfigCommon::Decode( const Archivist::Object & data )
{
	std::multimap<CardPlayStruct,CardPlay*> mapCard; //keep card instance comparison with card pointer
	initBoard->begin();
	GridCoord gridKey;
	CardPlay* cardValue = NULL;
	while((cardValue = initBoard->next(&gridKey)))
	{
		mapCard.insert(std::pair<CardPlayStruct, CardPlay*>(CardPlayStruct(cardValue), cardValue));
	}
	initBoard->end();
	
	moves->clear();
	initBoard->removeAllObjects();
	
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
		
		std::multimap<CardPlayStruct,CardPlay*>::iterator mapIt = mapCard.find(card);
		if(mapIt == mapCard.end())
		{
			CardPlay* cardInstance = CardPlay::cardBoardWithConfAndColorAndRank(this,card.color,card.rank);
			initBoard->setObject(cardInstance, coord);
		}
		else
		{
			initBoard->setObject(mapIt->second, coord);
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
		return true;
	}
	
	return false;
}
