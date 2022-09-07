/**
 * test_file_rename.c
 * 2020-03-01 K.OHWADA
 */

// rename file
// test for file_rename()

// gcc test_file_rename.c -o bin/rename

#include <stdio.h>
#include "file_util.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    if(argc < 3) {
        printf( "Usage:  %s <oldpath> <newpath> \n",  argv[0] );
        return EXIT_FAILURE;
    }

    char* oldpath = argv[1];
    char* newpath = argv[2];
    char error[100];

    bool ret = file_rename(oldpath, newpath, (char *)error);
    if( !ret ){
        printf( "error: %s \n", error);
                return EXIT_FAILURE;
    }

    printf( "renamed to %s \n", newpath);
    return EXIT_SUCCESS;
}
