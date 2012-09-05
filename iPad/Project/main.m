//
//  main.m
//  ChinesePuzzle
//
//  Created by Mathieu Ledru on 05/09/12.
//  Copyright (c) 2012 Mathieu Ledru. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppController.h"

int main(int argc, char *argv[])
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
