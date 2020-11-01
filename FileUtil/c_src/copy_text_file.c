/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// copy text file
// test for  file_text_copy()

#include <stdio.h>
#include "file_util.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    char* from = "data/sample.txt";
    char* to = "sample_out.txt";

    if(argc == 3) {
        from = argv[1];
        to = argv[2];
    } else {
        printf( "Usage:  %s <from> <to> \n",  argv[0] );
    }


    char error[100];

    bool ret = file_text_copy(from, to, (char *)error);
    if(! ret ) {
        printf( "error: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("copied to: %s \n", to);
    return EXIT_SUCCESS;
}


// % ./a.out data/sample.txt out.txt
// copied to out.txt 


