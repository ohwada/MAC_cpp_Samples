#pragma once
/**
 * home_directory.h
 * 2020-07-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>


// prototype
char* getHomeDir(void);


/**
 *  getHomeDir
 */
char* getHomeDir(void)
{
    const size_t BUFSIZE = 256;
    static char buf[BUFSIZE];

    char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    strcpy(buf,  homedir );
    return buf;
}

