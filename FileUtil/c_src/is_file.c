/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// determine if it is a file or a directory
// test for is_file() and is_dir()

#include <stdio.h>
#include "file_util.h"

/**
 * main
 */
int main(int argc, char** argv)
{

    if(argc < 2) {
        printf( "Usage: %s <filepath>  \n" , argv[0] );
        return 1;
    }

    char* path = argv[1];

    int ret1 = is_file(path);
    int ret2 = is_dir(path);

    if(ret1 == -1) {
            printf("not found: %s \n", path);
    } else if (ret1 == 1) {
        printf("%s : is file \n", path);
    } else if (ret2 == 1) {
            printf("%s : is directory \n", path);
    } 

    return 0;
}
