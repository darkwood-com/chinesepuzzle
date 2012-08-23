/**
 *  MenuLayout.cpp
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

#include "MenuLayout.h"
#include "Menu.h"
#include "MenuGridContainer.h"
#include "MenuLabelContainer.h"
#include "GameScene.h"

using namespace cocos2d;

typedef enum  
{
	kMenuTagBg,
	kMenuTagNewTitle,
	kMenuTagNewYes,
	kMenuTagNewNo,
	kMenuTagRetryTitle,
	kMenuTagRetryYes,
	kMenuTagRetryNo,
} kMenuTag;

template <class T> T* MenuLayout::layoutRes(const char* key)
{
	static std::map<std::string, void*>* datas = NULL;
	
	if(!datas)
	{
		datas = new std::map<std::string, void*>();
		
		std::string sRes;
		
		sRes = "480x320";
		(*datas)[sRes + "font"] = new std::string("arial16.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(200,200);
		
		sRes = "960x640";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(150,50);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(50,50);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(200,200);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(200,200);
		
		sRes = "1024x768";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1280x800";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1280x1024";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1366x768";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1440x900";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1680x1050";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1920x1080";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
		
		sRes = "1920x1200";
		(*datas)[sRes + "font"] = new std::string("arial32.fnt");
		(*datas)[sRes + "menuNewBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuNewTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuNewYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuNewNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuRetryBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuRetryTitle"] = new CCPoint(200,200);
		(*datas)[sRes + "menuRetryYes"] = new CCPoint(300,100);
		(*datas)[sRes + "menuRetryNo"] = new CCPoint(100,100);
		(*datas)[sRes + "menuHintBoxSize"] = new CCSize(400,400);
		(*datas)[sRes + "menuThemeBoxSize"] = new CCSize(800,800);
		(*datas)[sRes + "menuNoneBoxSize"] = new CCSize(400,400);
	}
	
	string sRes = menu->getGameScene()->getConf()->getResolution();
	return reinterpret_cast<T*>((*datas)[sRes + key]);
}

MenuLayout::MenuLayout(Menu* menu) :
bg(NULL),
menu(menu),
themes(NULL),
mBox(NULL),
miTheme(NULL)
{
}

MenuLayout::~MenuLayout()
{
	CC_SAFE_RELEASE(themes);
	CC_SAFE_RELEASE(mBox);
	CC_SAFE_RELEASE(miTheme);
}

bool MenuLayout::initWithType(Type type)
{
	this->type = type;
	
	return true;
}

static std::string lastFontFile;

void MenuLayout::layout(bool anim)
{
	GameConfigCommon* conf = menu->getGameScene()->getConf();
	CCPoint center = ccpMult(ccp(conf->getResolutionSize().width, conf->getResolutionSize().height), 0.5);
	
	if(!bg)
	{
		bg = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
		menu->addChild(bg, 0, kMenuTagBg);
	}
	conf->getNodeUiPath("menuMask", bg);
	bg->setPosition(ccp(0, 0));
	bg->setAnchorPoint(ccp(0, 0));
	
	CCSpriteBatchNode* yesNode = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
	conf->getNodeUiPath("menuItemYes", yesNode);
	CCSprite* yesSprite = copyFirstSpriteBatchNode(yesNode);
	
	CCSpriteBatchNode* noNode = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
	conf->getNodeUiPath("menuItemNo", noNode);
	CCSprite* noSprite = copyFirstSpriteBatchNode(noNode);
	
	std::string currentFontFile = *this->layoutRes<std::string>("font");
	
	switch (this->type)
	{
		case TypeNewGame:
		{
			if(!mBox)
			{
				mBox = new MenuBox();
				mBox->initWithConf(conf);
				mBox->setOkTarget(menu, menu_selector(Menu::okMenu));
				mBox->setTitle("New game");
				
				menu->pushNav(mBox);
			}
			mBox->setContentSize(*this->layoutRes<CCSize>("menuNewBoxSize"));
			mBox->setPosition(center);
			mBox->setAnchorPoint(ccp(0.5f, 0.5f));
			
			CCLabelBMFont* itemTitle = dynamic_cast<CCLabelBMFont*>(mBox->getChildByTag(kMenuTagNewTitle));
			if(!itemTitle || currentFontFile != lastFontFile)
			{
				mBox->removeChildByTag(kMenuTagNewTitle, true);
				itemTitle = CCLabelBMFont::labelWithString("Do you want start a new game?", conf->getFontPath(currentFontFile.c_str()).c_str());
				itemTitle->setAnchorPoint(ccp(0.5f, 0.5f));
				mBox->addChild(itemTitle, 0, kMenuTagNewTitle);
			}
			itemTitle->setPosition(*this->layoutRes<CCPoint>("menuNewTitle"));
			
			CCMenuItemSprite* itemYes = dynamic_cast<CCMenuItemSprite*>(mBox->getChildByTag(kMenuTagNewYes));
			if(!itemYes)
			{
				itemYes = new CCMenuItemSprite();
				itemYes->initWithTarget(menu->getGameScene(), menu_selector(GameSceneCommon::newGame));
				itemYes->setAnchorPoint(ccp(0.5f, 0.5f));
				itemYes->autorelease();
				mBox->addChild(itemYes, 1, kMenuTagNewYes);
			}
			itemYes->setNormalImage(yesSprite);
			itemYes->setContentSize(yesSprite->getContentSize());
			itemYes->setPosition(*this->layoutRes<CCPoint>("menuNewYes"));
			
			CCMenuItemSprite* itemNo = dynamic_cast<CCMenuItemSprite*>(mBox->getChildByTag(kMenuTagNewNo));
			if(!itemNo)
			{
				itemNo = new CCMenuItemSprite();
				itemNo->initWithTarget(menu, menu_selector(Menu::okMenu));
				itemNo->setAnchorPoint(ccp(0.5f, 0.5f));
				itemNo->autorelease();
				mBox->addChild(itemNo, 2, kMenuTagNewNo);
			}
			itemNo->setNormalImage(noSprite);
			itemNo->setContentSize(noSprite->getContentSize());
			itemNo->setPosition(*this->layoutRes<CCPoint>("menuNewNo"));
			
			mBox->layout(anim);
		}
		break;
		case TypeRetryGame:
		{
			if(!mBox)
			{
				mBox = new MenuBox();
				mBox->initWithConf(conf);
				mBox->setOkTarget(menu, menu_selector(Menu::okMenu));
				mBox->setTitle("Retry game");
				
				menu->pushNav(mBox);
			}
			
			mBox->setContentSize(*this->layoutRes<CCSize>("menuRetryBoxSize"));
			mBox->setPosition(center);
			mBox->setAnchorPoint(ccp(0.5f, 0.5f));
			
			CCLabelBMFont* itemTitle = dynamic_cast<CCLabelBMFont*>(mBox->getChildByTag(kMenuTagRetryTitle));
			if(!itemTitle || currentFontFile != lastFontFile)
			{
				mBox->removeChildByTag(kMenuTagRetryTitle, true);
				itemTitle = CCLabelBMFont::labelWithString("Do you want retry the game?", conf->getFontPath(currentFontFile.c_str()).c_str());
				itemTitle->setAnchorPoint(ccp(0.5f, 0.5f));
				mBox->addChild(itemTitle, 0, kMenuTagRetryTitle);
			}
			itemTitle->setPosition(*this->layoutRes<CCPoint>("menuRetryTitle"));
			
			CCMenuItemSprite* itemYes = dynamic_cast<CCMenuItemSprite*>(mBox->getChildByTag(kMenuTagRetryYes));
			if(!itemYes)
			{
				itemYes = new CCMenuItemSprite();
				itemYes->initWithTarget(menu->getGameScene(), menu_selector(GameSceneCommon::retryGame));
				itemYes->setAnchorPoint(ccp(0.5f, 0.5f));
				itemYes->autorelease();
				mBox->addChild(itemYes, 1, kMenuTagRetryYes);
			}
			itemYes->setNormalImage(yesSprite);
			itemYes->setContentSize(yesSprite->getContentSize());
			itemYes->setPosition(*this->layoutRes<CCPoint>("menuRetryYes"));
			
			CCMenuItemSprite* itemNo = dynamic_cast<CCMenuItemSprite*>(mBox->getChildByTag(kMenuTagRetryNo));
			if(!itemNo)
			{
				itemNo = new CCMenuItemSprite();
				itemNo->initWithTarget(menu, menu_selector(Menu::okMenu));
				itemNo->setAnchorPoint(ccp(0.5f, 0.5f));
				itemNo->autorelease();
				mBox->addChild(itemNo, 2, kMenuTagRetryNo);
			}
			itemNo->setNormalImage(noSprite);
			itemNo->setContentSize(noSprite->getContentSize());
			itemNo->setPosition(*this->layoutRes<CCPoint>("menuRetryNo"));
			
			mBox->layout(anim);
		}
		break;
		case TypeHint:
		{
			if(!mBox)
			{
				MenuLabelContainer* mb = new MenuLabelContainer();
				mb->initWithConfAndContentSizeAndFntFile(conf, *this->layoutRes<CCSize>("menuHintBoxSize"), conf->getFontPath((*this->layoutRes<std::string>("font")).c_str()).c_str());
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setMargin(CCSizeMake(50, 50));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("Hint");
				mb->setString("Chinese Puzzle is a two-deck solitaire card game in which your memory and familiarity with the rules are tested to the limit. The game laid out in a tableau of eight rows. The goal is to move cards around in vacant spaces, so that all rows end up in a same family-colored and sorted order from Ace to King. Ace cards can only be moved at the first column, then you can fill the vacant space by drag and dropping one of the two card from same family color and next rank to the left card. Not clear? Just make some moves and play the game, but be careful with Kings!");
				
				mBox =  mb;
				
				menu->pushNav(mBox);
			}
			
			mBox->setContentSize(*this->layoutRes<CCSize>("menuHintBoxSize"));
			mBox->setPosition(center);
			mBox->setAnchorPoint(ccp(0.5f, 0.5f));
			mBox->layout(anim);
		}
		break;
		case TypeTheme:
		{
			if(!themes)
			{
				std::map<std::string, std::string> themeNodes;
                themeNodes["classic"]       = "menuItemThemeClassic";
                themeNodes["chinese"]       = "menuItemThemeChinese";
                themeNodes["circle"]        = "menuItemThemeCircle";
                themeNodes["polkadots"]     = "menuItemThemePolkadots";
                themeNodes["seamless"]      = "menuItemThemeSeamless";
                themeNodes["skullshearts"]  = "menuItemThemeSkullshearts";
                themeNodes["splash"]        = "menuItemThemeSplash";
                themeNodes["spring"]        = "menuItemThemeSpring";
                themeNodes["stripes"]       = "menuItemThemeStripes";
                themeNodes["vivid"]         = "menuItemThemeVivid";
				
				themes = new CCMutableDictionary<std::string, cocos2d::CCMenuItemSprite*>();
				for (std::map<std::string, std::string>::const_iterator it = themeNodes.begin(); it != themeNodes.end(); ++it)
				{
					CCSpriteBatchNode* themeNode = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
					CCSpriteBatchNode* themeNodeSelected = CCSpriteBatchNode::batchNodeWithTexture(ccTextureNull);
					conf->getNodeUiPath(it->second.c_str(), themeNode);
					conf->getNodeUiPath((it->second + "Select").c_str(), themeNodeSelected);
					
					themes->setObject(CCMenuItemSprite::itemFromNormalSprite(themeNode, themeNodeSelected, this, menu_selector(MenuLayout::selectTheme)), it->first.c_str());
				}
			}
			
			if(!mBox)
			{
				MenuGridContainer* mb = new MenuGridContainer();
				mb->initWithConf(conf);
				mb->setMargin(CCSizeMake(50, 50));
				mb->setGridSize(ccg(2, 2));
				mb->setPage(0);
				mb->setMinimumTouchLengthToChangePage((200 - 50 * 2) / 8);
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("Themes");
				
				CCArray* items = CCArray::array();
				
				std::vector<std::string> sTheme = themes->allKeys();
				for(std::vector<std::string>::iterator it = sTheme.begin(); it != sTheme.end(); ++it)
				{
					CCMenuItemSprite* mItem = themes->objectForKey(*it);
					items->addObject(mItem);
				}
				
				mb->setItems(items);
				
				mBox =  mb;
				
				menu->pushNav(mBox);
			}
			
			mBox->setContentSize(*this->layoutRes<CCSize>("menuThemeBoxSize"));
			mBox->setPosition(center);
			mBox->setAnchorPoint(ccp(0.5f, 0.5f));
			mBox->layout(anim);
		}
		break;
		case TypeNone:
		{
			if(!mBox)
			{
				MenuBox* mb = new MenuBox();
				mb->initWithConfAndContentSize(conf, *this->layoutRes<CCSize>("menuNoneBoxSize"));
				mb->setPosition(center);
				mb->setAnchorPoint(ccp(0.5f, 0.5f));
				mb->setOkTarget(menu, menu_selector(Menu::okMenu));
				mb->setTitle("None");
				
				CCArray* items = CCArray::array();
				
				CCMenuItemFont* item = new CCMenuItemFont();
				item->initFromString("Exit menu", menu, menu_selector(Menu::okMenu));
				item->setAnchorPoint(ccp(0.5f, 0.5f));
				item->setPosition(ccp(0, 0));
				items->addObject(item);
				item->release();
				
				mb->setItems(items);
				mb->layout(anim);
				
				mBox =  mb;
				
				menu->pushNav(mBox);
			}
			
			mBox->layout(anim);
		}
		break;
	}
	
	lastFontFile = currentFontFile;
}

void MenuLayout::selectTheme(cocos2d::CCObject* themeNode)
{
	std::vector<std::string> sTheme = themes->allKeys();
	for(std::vector<std::string>::iterator it = sTheme.begin(); it != sTheme.end(); ++it)
	{
		if(themes->objectForKey(*it) == themeNode)
		{
			menu->getGameScene()->setTheme(*it);
		}
	}
}