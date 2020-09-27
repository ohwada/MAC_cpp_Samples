/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// copy file
// test for  file_copy()

#include <stdio.h>
#include "file_util.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    if(argc < 3) {
        printf( "Usage:  %s <from> <to> \n",  argv[0] );
        return 1;
    }

    char* from = argv[1];
    char* to = argv[2];
    char error[100];

    int ret = file_copy(from, to, (char *)error);
    if(ret != 0) {
        printf( "error: %s \n", error);
        return 1;
    }

    printf("copied to %s \n", to);
    return 0;
}


// % ./a.out data/sample.txt out.txt
// copied to out.txt 


