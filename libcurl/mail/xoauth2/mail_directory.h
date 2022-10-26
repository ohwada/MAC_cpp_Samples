#pragma once
/**
 * mail_directory.h
 * 2020-07-01 K.OHWADA
 */

// getMailDir


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

    strcpy( buf, getHomeDir() );
    strcat( buf, "/mail");

    return buf;
}
