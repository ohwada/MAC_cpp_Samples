#pragma once
/**
 * system sample
 * 2020-07-01 K.OHWADA
 */


// get home directory

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/03/121904


#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>


// prototype
char* getEnvHome(void);
char* getPwDir(void);
char* getHomeDir(void);


/**
 *  getEnvHome
 */
char* getEnvHome(void)
{
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    strcpy(buf, getenv("HOME"));
    return buf;
}


/**
 *  getPwDir
 */
char* getPwDir(void)
{   
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    strcpy(buf,  getpwuid(getuid())->pw_dir );
    return buf;
}


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
