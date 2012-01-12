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
#include "cpMacro.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#include CP_PLATFORM(GameScene)

@implementation AppController
@synthesize window;

#pragma mark -
#pragma mark Application lifecycle

using namespace cocos2d;

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (id)init
{
    if (self = [super init])
	{
		resolutions = [[NSMutableDictionary dictionary] retain];
    }
    
    return self;
}

- (void)dealloc
{
	[resolutions release];
}

- (NSMenuItem*) resolution480x320
{
	return [resolutions valueForKey:@"480x320"];
}

- (NSMenuItem*) resolution1920x1200
{
	return [resolutions valueForKey:@"1920x1200"];
}

- (void) setResolution480x320:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"480x320"];
}

- (void) setResolution1920x1200:(NSMenuItem*) item
{
	return [resolutions setValue:item forKey:@"1920x1200"];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	EAGLView* __glView = [[[EAGLView alloc] initWithFrame:NSZeroRect shareContext:nil] autorelease];
	[NSOpenGLContext clearCurrentContext];
	[__glView.context makeCurrentContext];
	
	// Set RootViewController to window
    [window setContentView:__glView];
	
	AppDelegate* app = &dynamic_cast<AppDelegate&>(cocos2d::CCApplication::sharedApplication());
	app->run();
	
	for(NSString* menuItemKey in resolutions)
	{
		[[resolutions valueForKey:menuItemKey] setState:NSOffState];
	}
	NSString* sRes = [NSString stringWithCString:app->getGameScene()->getConf()->getResolution().c_str() encoding:NSUTF8StringEncoding];
	if([resolutions valueForKey:sRes])
	{
		[[resolutions valueForKey:sRes] setState:NSOnState];
	}
}

- (IBAction)changeResolution:(NSMenuItem*)sender
{
	for(NSString* menuItemKey in resolutions)
	{
		NSMenuItem* menuItem = [resolutions valueForKey:menuItemKey];
		if(menuItem == sender)
		{
			AppDelegate* app = &dynamic_cast<AppDelegate&>(cocos2d::CCApplication::sharedApplication());
			std::string sRes = [menuItemKey cStringUsingEncoding:NSUTF8StringEncoding];
			app->getGameScene()->setResolution(sRes);
			[menuItem setState:NSOnState];
		}
		else
		{
			[menuItem setState:NSOffState];
		}
	}
}

@end
