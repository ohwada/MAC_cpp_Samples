/**
 * test_zip_util.c
 * 2022-06-01 K.OHWADA
 */

// gcc test_zip_util.c

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zip_util.h"



/**
 *  main
 */
int main() 
{
const int NUM = 10;
const int BUFSIZE = 256;
char list[NUM][BUFSIZE];
;

	char* FULLPATH = (char *)"test/aaa/bbb/sample.txt";

	printf("%s\n", FULLPATH);

    int size;
    get_parent_list(FULLPATH, &size, NUM, BUFSIZE, list);

    for(int i=0; i<size; i++){
	    printf("%d: %s \n", i, list[i]);
    }

    assert( strcmp(list[0], "test") == 0 );
    assert( strcmp(list[1], "test/aaa") == 0 );

    assert( is_zip_dir("test/") );
    assert( is_zip_dir("test.txt") == false );


    return 0;
}


