#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */


// get mail directory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>


// prototype
char* getHomeDir(void);
char* getMailDir(void);

/**
 *  getHomeDir
 */
char* getHomeDir(void)
{
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    strcpy(buf,  homedir );
    return buf;
}


/**
 *  getMailDir
 */
char* getMailDir(void)
{
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    snprintf(buf, BUFSIZE, "%s/mail", getHomeDir() );

    return buf;
}


