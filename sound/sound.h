#pragma once
/**
 * sound.h
 * 2022-06-01 K.OHWADA
 */

 // define CMD_PLAY for each OS
// reference :  : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/

#ifndef SOUND_H
#define SOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

// prototype
void playSound(char *file);
bool exists_file(char *path);


#ifdef __linux__
#define CMD_PLAY  "/usr/bin/paplay"		// PulseAudio (for Linux)
#define SND_SHOT  "/usr/share/sounds/freedesktop/stereo/message.oga"
#endif

// for mac
#ifdef __APPLE__
#define CMD_PLAY  "/usr/bin/afplay"		// afplay (for MacOSX/BSD)
#define SND_SHOT "/System/Library/Sounds/Ping.aiff"
#endif


/*
 * playSound
 */
void playSound(char *file)
{
	const int BUFSIZE = 1024;
    char cmd[BUFSIZE];

	snprintf(cmd, BUFSIZE-1, "%s %s", CMD_PLAY, file );
	system(cmd);
}


/**
 * fexists_file
 */
bool exists_file(char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}

#endif // SOUND_H
