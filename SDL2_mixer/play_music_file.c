/**
 * play_music_file.c
 * 2022-05-01 K.OHWADA
 */


// gcc  play_music_file.c  -o play `pkg-config --cflags --libs sdl2_mixer`

#include <stdio.h>
#include "play_music.h"

/**
 * main
 */
int main(int argc, char* argv[])
{

    if (argc != 2) {
        printf("Usage: %s  <musicFile> \n", argv[0] );
        return EXIT_FAILURE;
    }

    char *file = argv[1];

    printf("file: %s \n", file);

    bool ret = playMusic(file);
    if(!ret){
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
