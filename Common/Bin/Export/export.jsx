﻿// zoneItright 2002-2007.  Adobe Systems, Incorporated.  All rights reserved.// This script will demonstrate how to load a selection// from a saved alpha channel.// enable double clicking from the Macintosh Finder or the Windows Explorer#target photoshop// in case we double clicked the fileapp.bringToFront();// debug level: 0-2 (0:disable, 1:break on error, 2:break at beginning)//$.level = 2;//debugger; // launch debugger on next linefunction createRect(x, y, width, height){    return new Array(new Array(x,y), new Array(x + width, y), new Array(x + width, y + height), new Array(x, y + height));}function max(a, b){    return a > b ? a : b;}function midPoint(point){    point.to = [        point.to[0] - point.from[2] / 2,        point.to[1] - point.from[3] / 2    ];    return point;}//configvar datadir = "/Users/math/Mathieu/Programmation/Programmation/ChinesePuzzle/ChinesePuzzle/Common/Bin/";var themes = ["classic"];var resolutions = {    "480x320":{        "ui":{            "menuMask":[{from:[0,0,480,320], to:[0,0]}],            "menuContainer":[{from:[480,0,96,96], to:[0,0]}],            "menuItemTheme":[{from:[480,96,58,58], to:[0,0]}],            "menuItemOk":[{from:[480,154,42,42], to:[0,0]}],            "menuItemYes":[{from:[480,196,88,44], to:[0,0]}],            "menuItemNo":[{from:[480,240,88,44], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,480,320], to:[0,0]}],            "cardplaybg":[{from:[506,0,26,36], to:[0,0]}],            "cardboardempty":[{from:[532,0,26,36], to:[0,0]}],            "cardboardyes":[{from:[558,0,26,36], to:[0,0]}],            "cardboardno":[{from:[584,0,26,36], to:[0,0]}],            "cardtouched":[{from:[610,0,26,36], to:[0,0]}],            "newBtn":[{from:[480,94,30,30], to:[0,0]}],            "hintBtn":[{from:[510,94,30,30], to:[0,0]}],            "themeBtn":[{from:[540,94,30,30], to:[0,0]}],            "undoBtn":[{from:[570,94,30,30], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var isRed = colorIndex == 1 || colorIndex == 2;            return [                    {from:[480,0,26,36], to:[0,0]}, //card bg                    {from:[480 + 12 * rankIndex,48 + isRed * 12,12,12], to:[1,1]}, //rank left                    {from:[480 + 12 * colorIndex,36,12,12], to:[13,1]}, //color center                    {from:[480 + 24 * colorIndex,72,24,22], to:[1,13]}, //color right                ];        }    },    "1024x768":{        "ui":{            "menuMask":[{from:[0,0,1024,768], to:[0,0]}],            "menuContainer":[{from:[1024,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[1024,192,84,28], to:[0,0]}],            "menuItemNo":[{from:[1024,222,84,28], to:[0,0]}],            "menuItemOk":[{from:[1024,257,55,55], to:[0,0]}],            "menuItemThemeClassic":[{from:[1024,320,195,156], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,1024,768], to:[0,0]}],            "cardplaybg":[{from:[1100,0,56,78], to:[0,0]}],            "cardboardempty":[{from:[1176,0,56,78], to:[0,0]}],            "cardboardyes":[{from:[1252,0,56,78], to:[0,0]}],            "cardboardno":[{from:[1328,0,56,78], to:[0,0]}],            "cardtouched":[{from:[1404,0,56,78], to:[0,0]}],            "newBtn":[{from:[1024,380,56,56], to:[0,0]}],            "retryBtn":[{from:[1100,380,56,56], to:[0,0]}],            "hintBtn":[{from:[1176,380,56,56], to:[0,0]}],            "soundOnBtn":[{from:[1252,380,56,56], to:[0,0]}],            "soundOffBtn":[{from:[1252,451,56,56], to:[0,0]}],            "themeBtn":[{from:[1328,380,56,56], to:[0,0]}],            "undoBtn":[{from:[1404,380,56,56], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [143,185,231,273];            var txtRankLine = [1102,18,1123,14,1143,14,1162,15,1183,15,1203,14,1223,14,1243,14,1263,14,1281,20,1304,14,1320,21,1343,15];            var shapeColorBig = [[1024,140,31,34],[1027,181,26,36],[1025,224,30,36],[1024,267,34,34]];            var shapeColorSmall = [[1071,146,19,21],[1073,189,16,22],[1072,231,18,22],[1070,274,21,21]];                        return [                    {from:[1024,0,56,78], to:[0,0]}, //card bg                    midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],27], to:[17,20]}), //rank left                    midPoint({from:shapeColorBig[colorIndex], to:[28,54]}), //color center                    midPoint({from:shapeColorSmall[colorIndex], to:[39,20]}), //color right                ];        }    },    "1680x1050":{        "ui":{            "menuMask":[{from:[0,0,1680,1050], to:[0,0]}],            "menuContainer":[{from:[1680,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[1680,196,107,36], to:[0,0]}],            "menuItemNo":[{from:[1680,235,107,36], to:[0,0]}],            "menuItemOk":[{from:[1680,279,72,72], to:[0,0]}],            "menuItemThemeClassic":[{from:[1680,360,250,200], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,1680,1050], to:[0,0]}],            "cardplaybg":[{from:[1760,0,73,100], to:[0,0]}],            "cardboardempty":[{from:[1840,0,73,100], to:[0,0]}],            "cardboardyes":[{from:[1920,0,73,100], to:[0,0]}],            "cardboardno":[{from:[2000,0,73,100], to:[0,0]}],            "cardtouched":[{from:[2080,0,73,100], to:[0,0]}],            "newBtn":[{from:[1680,400,72,72], to:[0,0]}],            "retryBtn":[{from:[1768,400,72,72], to:[0,0]}],            "hintBtn":[{from:[1856,400,72,72], to:[0,0]}],            "soundOnBtn":[{from:[1944,400,72,72], to:[0,0]}],            "soundOffBtn":[{from:[1944,490,72,72], to:[0,0]}],            "themeBtn":[{from:[2032,400,72,72], to:[0,0]}],            "undoBtn":[{from:[2120,400,72,72], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [146,200,258,312];            var txtRankLine = [1780,22,1808,17,1833,17,1858,19,1884,18,1910,17,1936,17,1962,17,1987,17,2010,25,2040,17,2060,26,2090,18];            var shapeColorBig = [[1680,142,41,43],[1685,194,35,47],[1682,249,39,46],[1680,305,44,43]];            var shapeColorSmall = [[1741,150,25,26],[1743,204,21,28],[1742,258,24,28],[1740,313,27,26]];                        return [                    {from:[1680,0,73,100], to:[0,0]}, //card bg                    midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34], to:[22,24]}), //rank left                    midPoint({from:shapeColorBig[colorIndex], to:[36,70]}), //color center                    midPoint({from:shapeColorSmall[colorIndex], to:[51,24]}), //color right                ];        }    },    "1920x1080":{        "ui":{            "menuMask":[{from:[0,0,1920,1080], to:[0,0]}],            "menuContainer":[{from:[1920,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[1920,196,107,36], to:[0,0]}],            "menuItemNo":[{from:[1920,235,107,36], to:[0,0]}],            "menuItemOk":[{from:[1920,279,72,72], to:[0,0]}],            "menuItemThemeClassic":[{from:[1920,360,250,200], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,1920,1080], to:[0,0]}],            "cardplaybg":[{from:[2000,0,73,100], to:[0,0]}],            "cardboardempty":[{from:[2080,0,73,100], to:[0,0]}],            "cardboardyes":[{from:[2160,0,73,100], to:[0,0]}],            "cardboardno":[{from:[2240,0,73,100], to:[0,0]}],            "cardtouched":[{from:[2320,0,73,100], to:[0,0]}],            "newBtn":[{from:[1920,400,72,72], to:[0,0]}],            "retryBtn":[{from:[2008,400,72,72], to:[0,0]}],            "hintBtn":[{from:[2096,400,72,72], to:[0,0]}],            "soundOnBtn":[{from:[2184,400,72,72], to:[0,0]}],            "soundOffBtn":[{from:[2184,490,72,72], to:[0,0]}],            "themeBtn":[{from:[2272,400,72,72], to:[0,0]}],            "undoBtn":[{from:[2360,400,72,72], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [146,200,258,312];            var txtRankLine = [2020,22,2048,17,2073,17,2098,19,2124,18,2150,17,2176,17,2202,17,2227,17,2250,25,2280,17,2300,26,2330,18];            var shapeColorBig = [[1920,142,41,43],[1925,194,35,47],[1922,249,39,46],[1920,305,44,43]];            var shapeColorSmall = [[1981,150,25,26],[1983,204,21,28],[1982,258,24,28],[1980,313,27,26]];                        return [                    {from:[1920,0,73,100], to:[0,0]}, //card bg                    midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34], to:[22,24]}), //rank left                    midPoint({from:shapeColorBig[colorIndex], to:[36,70]}), //color center                    midPoint({from:shapeColorSmall[colorIndex], to:[51,24]}), //color right                ];        }    },    "1920x1200":{        "ui":{            "menuMask":[{from:[0,0,1920,1200], to:[0,0]}],            "menuContainer":[{from:[1920,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[1920,196,107,36], to:[0,0]}],            "menuItemNo":[{from:[1920,235,107,36], to:[0,0]}],            "menuItemOk":[{from:[1920,279,72,72], to:[0,0]}],            "menuItemThemeClassic":[{from:[1920,360,250,200], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,1920,1200], to:[0,0]}],            "cardplaybg":[{from:[2000,0,73,100], to:[0,0]}],            "cardboardempty":[{from:[2080,0,73,100], to:[0,0]}],            "cardboardyes":[{from:[2160,0,73,100], to:[0,0]}],            "cardboardno":[{from:[2240,0,73,100], to:[0,0]}],            "cardtouched":[{from:[2320,0,73,100], to:[0,0]}],            "newBtn":[{from:[1920,400,72,72], to:[0,0]}],            "retryBtn":[{from:[2008,400,72,72], to:[0,0]}],            "hintBtn":[{from:[2096,400,72,72], to:[0,0]}],            "soundOnBtn":[{from:[2184,400,72,72], to:[0,0]}],            "soundOffBtn":[{from:[2184,490,72,72], to:[0,0]}],            "themeBtn":[{from:[2272,400,72,72], to:[0,0]}],            "undoBtn":[{from:[2360,400,72,72], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [146,200,258,312];            var txtRankLine = [2020,22,2048,17,2073,17,2098,19,2124,18,2150,17,2176,17,2202,17,2227,17,2250,25,2280,17,2300,26,2330,18];            var shapeColorBig = [[1920,142,41,43],[1925,194,35,47],[1922,249,39,46],[1920,305,44,43]];            var shapeColorSmall = [[1981,150,25,26],[1983,204,21,28],[1982,258,24,28],[1980,313,27,26]];                        return [                    {from:[1920,0,73,100], to:[0,0]}, //card bg                    midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],34], to:[22,24]}), //rank left                    midPoint({from:shapeColorBig[colorIndex], to:[36,70]}), //color center                    midPoint({from:shapeColorSmall[colorIndex], to:[51,24]}), //color right                ];        }    },};//exportvar exportdirs = [];for(resolution in resolutions){    //push ui    exportdirs.push({        savedir:"ui",        resolution:resolution,        sprites:resolutions[resolution]["ui"]    });        //push themes    for(theme in themes)    {        var sprites = resolutions[resolution]["theme"];                if(resolutions[resolution]["card"])        {            //coeur, careau,pique,trefle            var colors = ["D","S","H","C"];            var ranks = ["A","2","3","4","5","6","7","8","9","10","J","Q","K"];            for(colorIndex in colors)            {                var color = colors[colorIndex];                for(rankIndex in ranks)                {                    var rank = ranks[rankIndex];                    sprites["card_" + color + rank] = resolutions[resolution]["card"](colorIndex, rankIndex);                }            }        }                exportdirs.push({            savedir:"themes/" + themes[theme],            resolution:resolution,            sprites:sprites        });    }}//exportfor(exportdir in exportdirs){    var savedir = exportdirs[exportdir]["savedir"];    var resolution = exportdirs[exportdir]["resolution"];    var sprites = exportdirs[exportdir]["sprites"];    var savePng = new PNGSaveOptions();    var saveFolder = new Folder(datadir + "/Data/" + resolution + "/" + "/" + savedir);    if(!saveFolder.exists) saveFolder.create();         var file = null;    var spriteSrcDoc = null;        for(spritename in sprites)    {        var spriteFile = new File(datadir + "/Data/" + resolution + "/" + savedir  + "/" + spritename + ".png");        if(spriteFile.exists) continue;                if(!spriteSrcDoc)        {            file = new File(datadir + "/Export/" + resolution + "/" + savedir + ".png");            spriteSrcDoc = open(file);        }            var sprite = sprites[spritename];            var width = 0;        var height = 0;            for(zoneIt in sprite)        {            var zone = sprite[zoneIt];            width = max(zone["from"][2] + zone["to"][0], width);            height = max(zone["from"][3] + zone["to"][1], height);        }            var spriteDestDoc = app.documents.add(width, height, 72, spritename, NewDocumentMode.RGB, DocumentFill.TRANSPARENT);            for(zoneIt in sprite)        {            var zone = sprite[zoneIt];            app.activeDocument = spriteSrcDoc;            spriteSrcDoc.selection.select(createRect(zone["from"][0],zone["from"][1],zone["from"][2],zone["from"][3]));            spriteSrcDoc.selection.copy();                        app.activeDocument = spriteDestDoc;            spriteDestDoc.selection.select(createRect(zone["to"][0],zone["to"][1],zone["from"][2],zone["from"][3]));            spriteDestDoc.paste(true);        }            spriteDestDoc.mergeVisibleLayers();        spriteDestDoc.saveAs(spriteFile, savePng);        spriteDestDoc.close(SaveOptions.DONOTSAVECHANGES);        spriteDestDoc = null;    }    if(spriteSrcDoc)    {        spriteSrcDoc.close(SaveOptions.DONOTSAVECHANGES);        spriteSrcDoc = null;        file = null;    }}