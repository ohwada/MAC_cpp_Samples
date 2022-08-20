/**
 * slink.c
 * show symbolic link
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include"slink.h"


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* path = (char *) "/usr/local/bin/perl";

    if(argc == 2){
        path = argv[1];
    } else {
        printf("Usage: %s <path> \n", argv[0]);
    }

      printf("path: %s \n", path);

    show_link( path );

    return 0;
}


// /usr/local/bin/perl (30) 
// -> ../Cellar/perl/5.32.0/bin/perl (17808) 

