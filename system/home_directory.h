/**
 * C sample
 * 2020-03-01 K.OHWADA
 */


// get home directory
// reference : https://stackoverflow.com/questions/2910377/get-home-directory-in-linux


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
