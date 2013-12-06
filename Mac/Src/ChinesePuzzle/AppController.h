/**
 *  AppController.h
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

#import <Cocoa/Cocoa.h>

@interface AppController : NSObject <NSApplicationDelegate> {
@private
	__unsafe_unretained NSWindow* window;
	
	NSDictionary* resolutions;
}

@property (assign) IBOutlet NSWindow* window;

@property (nonatomic, strong) IBOutlet NSMenuItem* resolution480x320;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution960x640;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1024x768;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1280x800;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1280x1024;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1366x768;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1440x900;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1680x1050;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1920x1080;
@property (nonatomic, strong) IBOutlet NSMenuItem* resolution1920x1200;

- (IBAction)changeResolution:(NSMenuItem*)sender;

@end
