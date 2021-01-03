/**
 * system sample
 * 2020-07-01 K.OHWADA
 */

 // get executable path for Linux
// work on Linux only

// Document
https://ken-ohwada.hatenadiary.org/entry/2021/01/03/120707

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>


// prototype
bool get_executable_path( char *path, char *error ) ;


/**
 *  get_executable_path
 */
bool get_executable_path( char *path, char *error ) 
{

    char buf[PATH_MAX + 1];

    const size_t LINKSIZE = 100;
    char link[LINKSIZE];

// lnk to the currently running process.
    int pid = getpid();

    snprintf(link, LINKSIZE, "/proc/%d/exe", pid);

    printf( "link: %s \n",  link );

    ssize_t size = readlink( (char *)link, (char *)buf, PATH_MAX);

    if(size == -1){
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
    }

    strcpy(path, buf);
    return true;
}


/**
 *  main
 */
int main(void) 
{
    char path[PATH_MAX + 1];
    char error[100];

    bool ret = get_executable_path( (char *)path, (char *)error ) ;
    if(!ret){
        fprintf( stderr, "%s \n",  error );
        return EXIT_FAILURE;
    }

    printf( "executable_path: %s \n",  path );

    return EXIT_SUCCESS;
}


// link: /proc/4610/exe 
// executable_path: /home/taro/hoge/a.out 


