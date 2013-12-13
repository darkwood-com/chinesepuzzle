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
#import "EAGLView.h"
#include "CCEGLView.h"
#import "AppDelegate.h"
//#include CP_PLATFORM(GameScene)

@implementation AppController
@synthesize window;

USING_NS_CC;

- (id)init
{
    if (self = [super init])
	{
		resolutions = [NSMutableDictionary dictionary];
    }
    
    return self;
}

- (void)dealloc
{
}

- (NSMenuItem*) resolution480x320
{
	return [resolutions valueForKey:@"480x320"];
}

- (void) setResolution480x320:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"480x320"];
}

- (NSMenuItem*) resolution960x640
{
	return [resolutions valueForKey:@"960x640"];
}

- (void) setResolution960x640:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"960x640"];
}

- (NSMenuItem*) resolution1024x768
{
	return [resolutions valueForKey:@"1024x768"];
}

- (void) setResolution1024x768:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1024x768"];
}

- (NSMenuItem*) resolution1280x800
{
	return [resolutions valueForKey:@"1280x800"];
}

- (void) setResolution1280x800:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1280x800"];
}

- (NSMenuItem*) resolution1280x1024
{
	return [resolutions valueForKey:@"1280x1024"];
}

- (void) setResolution1280x1024:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1280x1024"];
}

- (NSMenuItem*) resolution1366x768
{
	return [resolutions valueForKey:@"1366x768"];
}

- (void) setResolution1366x768:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1366x768"];
}

- (NSMenuItem*) resolution1440x900
{
	return [resolutions valueForKey:@"1440x900"];
}

- (void) setResolution1440x900:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1440x900"];
}

- (NSMenuItem*) resolution1680x1050
{
	return [resolutions valueForKey:@"1680x1050"];
}

- (void) setResolution1680x1050:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1680x1050"];
}

- (NSMenuItem*) resolution1920x1080
{
	return [resolutions valueForKey:@"1920x1080"];
}

- (void) setResolution1920x1080:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1920x1080"];
}

- (NSMenuItem*) resolution1920x1200
{
	return [resolutions valueForKey:@"1920x1200"];
}

- (void) setResolution1920x1200:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1920x1200"];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [window close];
    
    AppDelegate app;
    EGLView eglView;
    eglView.init("Chinese Puzzle",900,640);

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

- (IBAction)changeResolution:(NSMenuItem*)sender
{
	for(NSString* menuItemKey in resolutions)
	{
		NSMenuItem* menuItem = [resolutions valueForKey:menuItemKey];
		if(menuItem == sender)
		{
//			AppDelegate* app = &dynamic_cast<AppDelegate&>(cocos2d::CCApplication::sharedApplication());
//			std::string sRes = [menuItemKey cStringUsingEncoding:NSUTF8StringEncoding];
//			app->getGameScene()->setResolution(sRes);
			[menuItem setState:NSOnState];
		}
		else
		{
			[menuItem setState:NSOffState];
		}
	}
}

@end
