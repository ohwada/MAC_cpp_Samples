/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// parse filepath
// test for c_parse_filename.h

#include<stdlib.h>
#include<stdio.h>

#include "c_parse_filename.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    if(argc < 2) {
        printf( "Usage: %s <filepath> \n", argv[0] );
        return 1;
    }

    char* filepath = argv[1];


    printf("filepath: %s \n", filepath);

    char *fname_with = get_filename_with_ext(filepath); 
    printf("filename_with_ext: %s \n", fname_with);

    char *fname_without = get_filename_without_ext(filepath); 
    printf("filename_without_ext: %s \n", fname_without);

    char *ext = get_file_ext(filepath); 
    printf("ext: %s \n", ext);

	return 0;

}


// % ./a.out data/sample.txt 
// filepath: data/sample.txt 
// filename_with_ext: sample.txt 
// filename_without_ext: sample 
//ext: txt 


