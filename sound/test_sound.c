/**
 * test_sound.c
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
 #include <stdlib.h>
#include <string.h>

#include "sound.h"

/**
 * main
 */
int main(int argc, char* argv[])
{
const int BUFSIZE = 1024;
char buf[BUFSIZE];

	strcpy(buf, SND_SHOT);

    if (argc == 2) {
    		strcpy(buf, argv[1]);
   } else {
        printf("Usage: %s  <soundFile> \n", argv[0] );
    }

    printf("file: %s \n", buf );

    if( !exists_file( CMD_PLAY) ){
        printf("NOT found: %s \n", CMD_PLAY );
        return EXIT_FAILURE;
    }

    if( !exists_file( buf ) ){
        printf("NOT found: %s \n", buf );
        return EXIT_FAILURE;
    }

	playSound(buf);

	return EXIT_SUCCESS;
}
