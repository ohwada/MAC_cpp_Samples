/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// check file exists
// test for  file_exists()

#include <stdio.h>
#include "file_util.h"

/**
 * main
 */
int main(int argc, char *argv[]) 
{
    char * file = "data/sample.txt";

    if (argc == 2) {
        file = argv[1];
        printf("Usage: %s <filepath> \n", argv[0] );
    }

    bool ret =file_exists(file);
    if ( ret ){
        printf("%s exists\n", file);
   } else{
        printf("%s does not exist \n", file);
    }

        return EXIT_SUCCESS;
}


// data/sample.txt exists


