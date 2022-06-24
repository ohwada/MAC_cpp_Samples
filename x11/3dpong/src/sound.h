#pragma once
/**
 * sound.h
 * define PLAY_CMD for each OS
 * 2022-06-01 K.OHWADA
 */

// reference :  : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/

#ifndef SOUND_H
#define SOUND_H


#ifdef __linux__
#define PLAY_CMD  "/usr/bin/paplay"		// PulseAudio (for Linux)
#endif

// for mac
#ifdef __APPLE__
#define PLAY_CMD  "/usr/bin/afplay"		// afplay (for MacOSX/BSD)
#endif

#endif // SOUND_H
