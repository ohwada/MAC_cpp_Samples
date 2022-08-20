/**
 * test_file_list.c
 * 2021-02-01 K.OHWADA
 */

// get filenames in directory

// gcc  test_file_list.c -Wall -o list 

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

    const int BUFSIZE = 100;
    char error[BUFSIZE];
    char error2[BUFSIZE];

    int num;
    int size;
    char** list = get_file_list(path, &num, &size, (char *)error );
    if(num == 0) {
             printf ("%s \n", error );
            return EXIT_FAILURE;;
    }
    if(size == 0) {
             printf ("no files\n");
            return EXIT_FAILURE;;
    }

    printf("get %d files \n", size);
    print_chars( list, size );

    free_chars( list, num );

   printf("\n");
    printf ("ext: %s \n", ext );

int num2;
 int size2;
char **list2 = get_file_list_ext(path, ext, &num2, &size2, (char *)error2 );
   if(num2 == 0) {
            printf ("%s \n", error );
            return EXIT_FAILURE;;
    }
   if(size2 == 0) {
            printf ("no match files \n");
            return EXIT_FAILURE;;
    }

    printf("get %d files \n", size2);
  print_chars( list2, size2 );

    free_chars( list2, num2 );

    return EXIT_SUCCESS;
}


// . 
// .. 
// README.md 
// a.out 
// c_src 
// data 
// src 

