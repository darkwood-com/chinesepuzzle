/**
 *  AppController.mm
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

#import <AppKit/AppKit.h>
#import "AppController.h"
//#include "cpMacro.h"
//#import "EAGLView.h"
//#include "CCEGLView.h"
#include "platform/desktop/CCGLView.h"
#include "CCDirector.h"
#include "CCGeometry.h"
#import "AppDelegate.h"
//#include CP_PLATFORM(GameScene)

@implementation AppController
@synthesize window;

USING_NS_CC;

- (id)init
{
    if (self = [super init])
	{
        
    }

    return self;
}

- (void)dealloc
{
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [window close];

    AppDelegate app;

    Director *director = Director::getInstance();
    GLView* glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("Chinese Puzzle", cocos2d::Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

//    NSRect rect = NSMakeRect(0, 0, 1024, 768);
//
//	[window setFrame:[[NSScreen mainScreen] frame] display:YES];
//
//    NSOpenGLPixelFormatAttribute attributes[] = {
//        NSOpenGLPFADoubleBuffer,
//        NSOpenGLPFADepthSize, 24,
//        NSOpenGLPFAStencilSize, 8,
//        0
//    };
//
//    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
//
//	CCEAGLView* __glView = [[CCEAGLView alloc] initWithFrame:rect pixelFormat:pixelFormat];
//	[NSOpenGLContext clearCurrentContext];
//	[__glView.openGLContext makeCurrentContext];
//
//	// Set RootViewController to window
//    [window becomeFirstResponder];
//    [window setContentView:__glView];

	Application::getInstance()->run();

//	for(NSString* menuItemKey in resolutions)
//	{
//		[[resolutions valueForKey:menuItemKey] setState:NSOffState];
//	}
//	NSString* sRes = [NSString stringWithCString:app->getGameScene()->getConf()->getResolution().c_str() encoding:NSUTF8StringEncoding];
//	if([resolutions valueForKey:sRes])
//	{
//		[[resolutions valueForKey:sRes] setState:NSOnState];
//	}
}

@end
