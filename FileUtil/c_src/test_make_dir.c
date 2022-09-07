/**
 * test_make_dir.c
 * 2022-06-01 K.OHWADA
 */

// gcc  test_make_dir.c -o bin/make_dir 

#include <stdio.h>
 #include <assert.h>
#include "file_util.h"


/**
 * main
 */
int main(int argc, char** argv)
{
    char* dir = "test";

    if(argc == 2) {
        dir = argv[1];
    } else {
        printf( "Usage: %s <new dir>  \n" , argv[0] );
    }

    bool ret = make_dir(dir, 0777);

    if ( ret) {
        printf("mkdir %s \n", dir);
    } 

    assert( is_dir(dir) );

    return EXIT_SUCCESS;
}


// data/sample.txt : is file

