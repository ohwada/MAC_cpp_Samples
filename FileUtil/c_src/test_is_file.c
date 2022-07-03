/**
 * test_is_file.c
 * 2020-02-01 K.OHWADA
 */

// determine if it is a file or a directory
// test for is_file() and is_dir()

// gcc  test_is_file.c -o is_file 

#include <stdio.h>
#include "file_util.h"

/**
 * main
 */
int main(int argc, char** argv)
{
    char* path = "sample.txt";

    if(argc == 2) {
        path = argv[1];
    } else {
        printf( "Usage: %s <filepath>  \n" , argv[0] );
    }

    bool ret1 = is_file(path);
    bool ret2 = is_dir(path);

    if ( ret1 ) {
        printf("%s : is file \n", path);
    } else if ( ret2 ) {
            printf("%s : is directory \n", path);
    } 

    return EXIT_SUCCESS;
}


// data/sample.txt : is file

