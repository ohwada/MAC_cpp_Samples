/**
 * C Sample
 * 2021-02-01 K.OHWADA
 */

// get filenames in directory
// gcc file_list.c


#include <stdio.h>
#include <stdlib.h>
#include "file_list.h"


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    char* path = ".";

    char *ext = "c";

    if(argc == 3) {
        path = argv[1];
        ext = argv[2];
    } else if(argc == 2) {
        path = argv[1];
    }else {
        printf( "Usage: %s [directory path]  [ext] \n" , argv[0] );
    }

    const int N = 10;
    const int M = 100;

    int size;
    char error[100];

    char** list = alloc_chars(N, M) ;

    bool ret1 = get_file_list( path,  list, N, &size, (char *)error  );

    if (!ret1) {
            printf ("%s \n", error );
            return EXIT_FAILURE;;
    }

    if(size == 0){
        printf ("no files \n" );
            return EXIT_FAILURE;;
    }

    printf ("get %d files \n", size );

    print_chars( list, size );

    clear_chars( list, N );

   printf("\n");
    printf ("ext: %s \n", ext );

    bool ret2 = get_file_list_ext( path,  list, N, ext, &size, (char *)error  );

    if (!ret2) {
            printf ("%s \n", error );
            return EXIT_FAILURE;;
    }

    if(size == 0){
        printf ("no files \n" );
            return EXIT_FAILURE;;
    }

 
    printf ("get %d files \n", size );

    print_chars( list, size );

    free_chars( list, N );

    return EXIT_SUCCESS;
}


// . 
// .. 
// README.md 
// a.out 
// c_src 
// data 
// src 

