#!/usr/bin/env perl

use strict;
use Path::Class;

my $TexturePackerOpts = "--format cocos2d --algorithm Basic --no-trim";

my $datadir = "/Users/math/Mathieu/Programmation/Programmation/ChinesePuzzle/Common/Bin/";
my @themes = ("classic","chinese");
my @resolutions = ("480x320","960x640","1024x768","1280x800","1280x1024","1366x768","1440x900","1680x1050","1920x1080","1920x1200");

foreach my $resolution (@resolutions)
{
	my $importdir = dir($datadir, "Export", $resolution, "ui")->stringify;
	my $exportdir = dir($datadir, "Data", $resolution)->stringify;
	if(-d $importdir && -d $exportdir)
	{
		system("TexturePacker $TexturePackerOpts --data $exportdir/ui.plist --sheet $exportdir/ui.png $importdir/*.png");
	}

	foreach my $theme (@themes)
	{
		my $importdir = dir($datadir, "Export", $resolution, "themes", $theme)->stringify;
		my $exportdir = dir($datadir, "Data", $resolution, "themes")->stringify;
		if(-d $importdir && -d $exportdir)
		{
			system("TexturePacker $TexturePackerOpts --data $exportdir/$theme.plist --sheet $exportdir/$theme.png $importdir/*.png");
		}
	}
}
