#pragma once
/**
 * sound2.h
 * 2022-06-01 K.OHWADA
 */

// play oga if You can
 // serch CMD_PLAY

#ifndef SOUND2_H
#define SOUND2_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

void playSound2(char *file);
char* getCmdPlay();
bool exists_file(char *path);


/*
 * playSound2
 */
void playSound2(char *file)
{
	const int BUFSIZE = 1024;
    char cmd[BUFSIZE];

	snprintf(cmd, BUFSIZE-1, "%s %s", getCmdPlay(), file );
	system(cmd);
}


/*
 * getCmdPlay
 */
char* getCmdPlay()
{
// Linux
static const char CMD_PLAY1[] = "/usr/bin/paplay";
// if installed
static const char CMD_PLAY2[] = "/usr/local/bin/paplay";
// Mac
static const char CMD_PLAY3[] = "/usr/bin/afplay";

    if( exists_file(( char *) CMD_PLAY1) ) {
        return ( char *) CMD_PLAY1;
    } else if( exists_file(( char *) CMD_PLAY2) ) {
        return ( char *) CMD_PLAY2;
    } else if( exists_file(( char *) CMD_PLAY3) ) {
        return ( char *) CMD_PLAY3;
    }
    return NULL;
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


#endif // SOUND2_H
