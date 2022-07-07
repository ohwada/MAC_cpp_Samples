/**
 * test_sound.c
 * 2022-06-01 K.OHWADA
 */


// play oga if You can
// Require: paplay

// gcc test_sound2.c -o sound2 

#include <stdio.h>
 #include <stdlib.h>
#include <string.h>

#include "sound2.h"


/**
 * main
 */
int main(int argc, char* argv[])
{
const int BUFSIZE = 1024;
char buf[BUFSIZE];

	strcpy(buf, "media/service-login.oga");

    if (argc == 2) {
    		strcpy(buf, argv[1]);
    } else {
        printf("Usage: %s  <soundFile> \n", argv[0] );
    }

    printf("file: %s \n", buf );

    if( !exists_file( buf ) ){
        printf("NOT found: %s \n", buf );
        return EXIT_FAILURE;
    }

	playSound2(buf);

    return EXIT_SUCCESS;
}
