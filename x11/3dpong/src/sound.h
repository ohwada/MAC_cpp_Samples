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

void playSound(char *file);

#ifdef __linux__
#define CMD_PLAY  "/usr/bin/paplay"		// PulseAudio (for Linux)
#endif

// for mac
#ifdef __APPLE__
#define CMD_PLAY  "/usr/bin/afplay"		// afplay (for MacOSX/BSD)
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

#endif // SOUND_H
