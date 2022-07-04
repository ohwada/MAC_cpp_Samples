/**
 * play_music._filec
 * 2020-02-01 K.OHWADA
 */



#include <stdio.h>
#include "play_music.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    if (argc != 2) {
        printf("Usage: %s  <musicFile> \n", argv[0] );
        return EXIT_FAILURE;
    }

    char *file = argv[1];

    bool ret = playMusic(file);
    if(!ret) {
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}

