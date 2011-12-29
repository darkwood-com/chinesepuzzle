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
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	EAGLView* __glView = [[[EAGLView alloc] initWithFrame:NSZeroRect shareContext:nil] autorelease];
	[NSOpenGLContext clearCurrentContext];
	[__glView.context makeCurrentContext];
	
	// Set RootViewController to window
    [window setContentView:__glView];
	
	cocos2d::CCApplication::sharedApplication().run();
}

@end
