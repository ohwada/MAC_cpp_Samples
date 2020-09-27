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
    if (argc != 2) {
        printf("Usage: %s <filepath> \n", argv[0] );
        return 1;
    }

    char * file = argv[1];

    int ret =file_exists(file);
    if (ret == 0){
        printf("%s exists\n", file);
   } else{
        printf("%s does not exist \n", file);
    }

    return 0;
}

