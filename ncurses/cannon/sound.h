// 2022-05-01 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/


#ifndef SOUND_H
#define SOUND_H

// === Audio playback command ===

#ifdef __linux__
#define PLAY_CMD  "/usr/bin/paplay"		// PulseAudio (for Linux)
#endif

// for mac
#ifdef __APPLE__
#define PLAY_CMD  "/usr/bin/afplay"		// afplay (for MacOSX/BSD)
#endif

// #define PLAY_CMD  "/usr/bin/aplay"		// ALSA (for Linux)
// #define PLAY_CMD  "/usr/bin/play"		// SOX (for Linux)
// #define PLAY_CMD  "/usr/bin/esdplay"		// Esound (for Linux)


// === Sound effect file ===

// for generic Linux
#ifdef __linux__
#define START_SND "/usr/share/sounds/freedesktop/stereo/service-login.oga" 	// Start sound
#define SHOT_SND  "/usr/share/sounds/freedesktop/stereo/message.oga"		// Bullet Fire sound
#define JET_SND  "/usr/share/sounds/freedesktop/stereo/dialog-warning.oga"	// Missile Fire sound
#define BOOM_SND  "/usr/share/sounds/freedesktop/stereo/bell.oga"	// Explosion sound
#endif


// for Mac
#ifdef __APPLE__
#define START_SND "/System/Library/Sounds/Submarine.aiff"
// Start sound
#define SHOT_SND "/System/Library/Sounds/Ping.aiff"
// Bullet Fire sound
#define JET_SND "/System/Library/Sounds/Glass.aiff" //Missile Fire sound
#define BOOM_SND  "/System/Library/Sounds/Blow.aiff" // Explosion sound
#endif

// for old Fedora + gnome-games package
// #define START_SND "/usr/share/sounds/gaim/redalert.wav"
// #define SHOT_SND  "/usr/share/sounds/k3b_wait_media1.wav"
// #define BOOM_SND  "/usr/share/sounds/gnobots2/splat.wav"

#endif