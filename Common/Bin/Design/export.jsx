﻿// enable double clicking from the Macintosh Finder or the Windows Explorer#target photoshop// in case we double clicked the fileapp.bringToFront();// debug level: 0-2 (0:disable, 1:break on error, 2:break at beginning)//$.level = 2;//debugger; // launch debugger on next linefunction createRect(x, y, width, height){    return new Array(new Array(x,y), new Array(x + width, y), new Array(x + width, y + height), new Array(x, y + height));}function max(a, b){    return a > b ? a : b;}function midPoint(point){    point.to = [        point.to[0] - point.from[2] / 2,        point.to[1] - point.from[3] / 2    ];    return point;}function zeroPoint(point){    point.to = [0, 0];    return point;}function spriteSize(sprite){    var width = 0;    var height = 0;        for(zoneIt in sprite)    {        var zone = sprite[zoneIt];        width = max(zone["from"][2] + zone["to"][0], width);        height = max(zone["from"][3] + zone["to"][1], height);    }    return {        "width":new UnitValue(width + "pixels"),        "height":new UnitValue(height + "pixels"),     };}function spriteCopy(sprite, spriteSrcDoc, spriteDestDoc){    for(zoneIt in sprite)    {        var zone = sprite[zoneIt];        app.activeDocument = spriteSrcDoc;        spriteSrcDoc.selection.select(createRect(zone["from"][0],zone["from"][1],zone["from"][2],zone["from"][3]));        spriteSrcDoc.selection.copy();                app.activeDocument = spriteDestDoc;        spriteDestDoc.selection.select(createRect(zone["to"][0],zone["to"][1],zone["from"][2],zone["from"][3]));        spriteDestDoc.paste(true);    }}//configvar exportmode = "debug"; //debug or release or texturepackervar datadir = "/Users/math/Mathieu/Programmation/Programmation/ChinesePuzzle/ChinesePuzzle/Common/Bin/";var themes = ["chinese"];var resolutions = {    "960x640":{         "ui":{            "menuMask":[{from:[0,0,960,640], to:[0,0]}],            "menuContainer":[{from:[960,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[960,192,100,36], to:[0,0]}],            "menuItemNo":[{from:[960,278,100,36], to:[0,0]}],            "menuItemOk":[{from:[960,366,72,72], to:[0,0]}],            "menuItemThemeSelect":[{from:[960,460,180,144], to:[0,0]}],            "menuItemThemeClassic":[{from:[1140,316,180,144], to:[0,0]}],            "menuItemThemeChinese":[{from:[1500,28,180,144], to:[0,0]}],            "menuItemThemeCircle":[{from:[1500,172,180,144], to:[0,0]}],            "menuItemThemePolkadots":[{from:[1140,460,180,144], to:[0,0]}],            "menuItemThemeSeamless":[{from:[1320,28,180,144], to:[0,0]}],            "menuItemThemeSkullshearts":[{from:[1320,172,180,144], to:[0,0]}],            "menuItemThemeSplash":[{from:[1320,316,180,144], to:[0,0]}],            "menuItemThemeSpring":[{from:[1320,460,180,144], to:[0,0]}],            "menuItemThemeStripes":[{from:[1500,316,180,144], to:[0,0]}],            "menuItemThemeVivid":[{from:[1500,460,180,144], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,960,640], to:[0,0]}],            "cardplaybg":[{from:[1056,0,52,72], to:[0,0]}],            "cardboardempty":[{from:[1152,0,52,72], to:[0,0]}],            "cardboardyes":[{from:[1248,0,52,72], to:[0,0]}],            "cardboardno":[{from:[1344,0,52,72], to:[0,0]}],            "cardtouched":[{from:[1440,0,52,72], to:[0,0]}],            "newBtn":[{from:[960,316,72,72], to:[0,0]}],            "retryBtn":[{from:[1056,316,72,72], to:[0,0]}],            "hintBtn":[{from:[1152,316,72,72], to:[0,0]}],            "soundOnBtn":[{from:[1248,316,72,72], to:[0,0]}],            "soundOffBtn":[{from:[1248,416,72,72], to:[0,0]}],            "themeBtn":[{from:[1344,316,72,72], to:[0,0]}],            "undoBtn":[{from:[1440,316,72,72], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [106,146,186,224];            var txtRankLine = [1032,16,1052,14,1070,14,1088,14,1106,14,1124,14,1142,14,1160,14,1178,14,1194,18,1216,14,1232,20,1254,14];            var shapeColorBig = [[960,104,30,32],[962,140,24,34],[960,180,28,34],[960,220,32,32]];            var shapeColorSmall = [[1002,108,18,20],[1004,148,16,20],[1004,186,18,20],[1002,226,20,20]];                        return {                "cardbg":{from:[960,0,52,72], to:[0,0]},                "rankleft":midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],26], to:[16,18]}),                "colorcenter":midPoint({from:shapeColorBig[colorIndex], to:[26,50]}),                "colorright":midPoint({from:shapeColorSmall[colorIndex], to:[36,18]}),            };        }    },    "1024x768":{        "ui":{            "menuMask":[{from:[0,0,1024,768], to:[0,0]}],            "menuContainer":[{from:[1024,0,192,192], to:[0,0]}],            "menuItemYes":[{from:[1024,192,84,28], to:[0,0]}],            "menuItemNo":[{from:[1024,222,84,28], to:[0,0]}],            "menuItemOk":[{from:[1024,257,55,55], to:[0,0]}],            "menuItemThemeSelect":[{from:[1024,319,195,156], to:[0,0]}],            "menuItemThemeClassic":[{from:[1024,475,195,156], to:[0,0]}],            "menuItemThemeChinese":[{from:[1609,319,195,156], to:[0,0]}],            "menuItemThemeCircle":[{from:[1804,321,195,156], to:[0,0]}],            "menuItemThemePolkadots":[{from:[1219,319,195,156], to:[0,0]}],            "menuItemThemeSeamless":[{from:[1219,475,195,156], to:[0,0]}],            "menuItemThemeSkullshearts":[{from:[1609,475,195,156], to:[0,0]}],            "menuItemThemeSplash":[{from:[1804,477,195,156], to:[0,0]}],            "menuItemThemeSpring":[{from:[1414,319,195,156], to:[0,0]}],            "menuItemThemeStripes":[{from:[1414,475,195,156], to:[0,0]}],            "menuItemThemeVivid":[{from:[1609,163,195,156], to:[0,0]}],        },        "theme":{            "bg":[{from:[0,0,1024,768], to:[0,0]}],            "cardplaybg":[{from:[1100,0,56,78], to:[0,0]}],            "cardboardempty":[{from:[1176,0,56,78], to:[0,0]}],            "cardboardyes":[{from:[1252,0,56,78], to:[0,0]}],            "cardboardno":[{from:[1328,0,56,78], to:[0,0]}],            "cardtouched":[{from:[1404,0,56,78], to:[0,0]}],            "newBtn":[{from:[1024,380,56,56], to:[0,0]}],            "retryBtn":[{from:[1100,380,56,56], to:[0,0]}],            "hintBtn":[{from:[1176,380,56,56], to:[0,0]}],            "soundOnBtn":[{from:[1252,380,56,56], to:[0,0]}],            "soundOffBtn":[{from:[1252,451,56,56], to:[0,0]}],            "themeBtn":[{from:[1328,380,56,56], to:[0,0]}],            "undoBtn":[{from:[1404,380,56,56], to:[0,0]}],        },        "card":function(colorIndex, rankIndex) {            var txtColorLine = [143,185,231,273];            var txtRankLine = [1102,18,1123,14,1143,14,1162,15,1183,15,1203,14,1223,14,1243,14,1263,14,1281,20,1304,14,1320,21,1343,15];            var shapeColorBig = [[1024,140,31,34],[1027,181,26,36],[1025,224,30,36],[1024,267,34,34]];            var shapeColorSmall = [[1071,146,19,21],[1073,189,16,22],[1072,231,18,22],[1070,274,21,21]];                        return {                "cardbg":{from:[1024,0,56,78], to:[0,0]},                "rankleft":midPoint({from:[txtRankLine[rankIndex*2],txtColorLine[colorIndex],txtRankLine[rankIndex*2+1],27], to:[17,20]}),                "colorcenter":midPoint({from:shapeColorBig[colorIndex], to:[28,54]}),                "colorright":midPoint({from:shapeColorSmall[colorIndex], to:[39,20]}),            };        }    },};//exportvar exportdirs = [];for(resolution in resolutions){    //push ui    exportdirs.push({        savedir:{"folder":"","file":"ui"},        resolution:resolution,        sprites:resolutions[resolution]["ui"]    });        //push themes    for(theme in themes)    {        //coeur, careau,pique,trefle        var colors = ["D","S","H","C"];        var ranks = ["A","2","3","4","5","6","7","8","9","10","J","Q","K"];        var sprites = null;        if(exportmode == "debug")        {			sprites = resolutions[resolution]["theme"];						for(colorIndex in colors)			{				var color = colors[colorIndex];				for(rankIndex in ranks)				{					var rank = ranks[rankIndex];					var card = resolutions[resolution]["card"](colorIndex, rankIndex);					sprites["card_" + color + rank] = [card["cardbg"],card["rankleft"],card["colorcenter"],card["colorright"]];				}			}        }        else if(exportmode == "texturepacker")        {            sprites = resolutions[resolution]["theme"];                        for(colorIndex in colors)		   {				var color = colors[colorIndex];				for(rankIndex in ranks)				{				    var rank = ranks[rankIndex];				    var card = resolutions[resolution]["card"](colorIndex, rankIndex);				    sprites["cardbg"] = [zeroPoint(card["cardbg"])];				    sprites["big_" + color] = [zeroPoint(card["colorcenter"])];                      sprites["small_" + color] = [zeroPoint(card["colorright"])];                      sprites["rank_" + color  + rank] = [zeroPoint(card["rankleft"])];				}			}        }                exportdirs.push({            savedir:{"folder":"themes","file":"themes/" + themes[theme]},            resolution:resolution,            sprites:sprites        });    }}//exportvar savePng = new PNGSaveOptions();for(exportdir in exportdirs){    var savedir = exportdirs[exportdir]["savedir"];    var resolution = exportdirs[exportdir]["resolution"];    var sprites = exportdirs[exportdir]["sprites"];    //check psd exist    var filepsd = new File(datadir + "/Design/" + resolution + "/" + savedir["file"] + ".psd");    if(!filepsd.exists) continue;    if(exportmode == "release")    {        var saveFolder = new Folder(datadir + "/Export/" + resolution + "/" + savedir["folder"]);        if(!saveFolder.exists) saveFolder.create();        var filepng = new File(datadir + "/Export/" + resolution + "/" + savedir["file"] + ".png");        if(!filepng.exists)        {            var spritePsdDoc = open(filepsd);            spritePsdDoc.mergeVisibleLayers();              spritePsdDoc.saveAs(filepng, savePng, true);            spritePsdDoc.close(SaveOptions.DONOTSAVECHANGES);            spritePsdDoc = null;        }    }    else if(exportmode == "debug")    {        var saveFolder = new Folder(datadir + "/Export/" + resolution + "/" + savedir["file"]);        if(!saveFolder.exists) saveFolder.create();        var filepng = new File(datadir + "/Export/" + resolution + "/" + savedir["file"] + ".png");        if(!filepng.exists)        {            var spritePsdDoc = open(filepsd);            spritePsdDoc.mergeVisibleLayers();            spritePsdDoc.saveAs(filepng, savePng, true);            spritePsdDoc.close(SaveOptions.DONOTSAVECHANGES);            spritePsdDoc = null;        }        var spriteSrcDoc = null;        for(spritename in sprites)        {            var spriteFile = new File(datadir + "/Export/" + resolution + "/" + savedir["file"]  + "/" + spritename + ".png");            if(spriteFile.exists) continue;                        if(!spriteSrcDoc)            {                spriteSrcDoc = open(filepng);            }                var sprite = sprites[spritename];            var size = spriteSize(sprite);                        var spriteDestDoc = app.documents.add(size["width"], size["height"], 72, spritename, NewDocumentMode.RGB, DocumentFill.TRANSPARENT);            spriteCopy(sprite, spriteSrcDoc, spriteDestDoc);            spriteDestDoc.mergeVisibleLayers();            spriteDestDoc.saveAs(spriteFile, savePng, true);            spriteDestDoc.close(SaveOptions.DONOTSAVECHANGES);            spriteDestDoc = null;        }        if(spriteSrcDoc)        {            spriteSrcDoc.close(SaveOptions.DONOTSAVECHANGES);            spriteSrcDoc = null;            filepng = null;        }    }    else if(exportmode == "texturepacker")    {        var saveFolder = new Folder(datadir + "/Export/" + resolution + "/" + savedir["file"]);        if(!saveFolder.exists) saveFolder.create();        var filepng = new File(datadir + "/Export/" + resolution + "/" + savedir["file"] + ".png");        if(!filepng.exists)        {            var spritePsdDoc = open(filepsd);            spritePsdDoc.mergeVisibleLayers();            spritePsdDoc.saveAs(filepng, savePng, true);            spritePsdDoc.close(SaveOptions.DONOTSAVECHANGES);            spritePsdDoc = null;        }        var spriteSrcDoc = null;        for(spritename in sprites)        {            var spriteFile = new File(datadir + "/Export/" + resolution + "/" + savedir["file"]  + "/" + spritename + ".png");            if(spriteFile.exists) continue;                        if(!spriteSrcDoc)            {                spriteSrcDoc = open(filepng);            }                var sprite = sprites[spritename];            var size = spriteSize(sprite);                        var spriteDestDoc = app.documents.add(size["width"], size["height"], 72, spritename, NewDocumentMode.RGB, DocumentFill.TRANSPARENT);            spriteCopy(sprite, spriteSrcDoc, spriteDestDoc);            spriteDestDoc.mergeVisibleLayers();            spriteDestDoc.saveAs(spriteFile, savePng, true);            spriteDestDoc.close(SaveOptions.DONOTSAVECHANGES);            spriteDestDoc = null;        }        if(spriteSrcDoc)        {            spriteSrcDoc.close(SaveOptions.DONOTSAVECHANGES);            spriteSrcDoc = null;            filepng = null;        }    }}