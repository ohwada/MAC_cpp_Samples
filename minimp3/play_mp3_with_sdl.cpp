/**
 * minimp3 Sample
 * 2020-03-01 K.OHWADA
 */

// play mp3 file
// original : https://github.com/lieff/minimp3

#include <string> 
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <SDL2/SDL.h>

#include "src/audio_sdl.h"
#include "src/decode.h"

using namespace std;

// global
const int SAMPLINGRATE = 44100;

static void *_render;
decoder _dec;


/**
 * getFileSize
 */
int getFileSize(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return -1;
    }

    // fetch file size
    struct stat file_stat;
    int fd = fileno(fp);
    int ret = fstat(fd, &file_stat);
    if (ret != 0) {
        fclose(fp);
        return -2;
    }

    int file_size = (int)file_stat.st_size;
    fclose(fp);

    return file_size;
}


/**
 * getPlaybackTime
 */
int getPlaybackTime(int file_size)
{
    // calculate roughly
    int time = (float)file_size /  (float)SAMPLINGRATE ;

    return time;
}


/**
 * main
 */
int main(int argc, char **argv)
{

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <mp3File> " <<  endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];


// file info
    int file_size = getFileSize(input);
    int time = getPlaybackTime(file_size);
    int delay = 1000 * (time + 10);
    printf("File: %d bytes ( %d sec )  \n",  file_size, time);


     if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        cout << "SDL_Init faild: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    sdl_audio_init(&_render, 
        SAMPLINGRATE, 
        2, // channels: stereo
        0,  // format: default : signed 8-bit samples
        0// buffer: default : 4096
    );

    sdl_audio_set_dec(_render, 0);
    open_dec(&_dec, input);
    sdl_audio_set_dec(_render, &_dec);

    size_t progress = 0;
    uint64_t cur_sample = _dec.mp3d.cur_sample;
    progress = cur_sample;

    SDL_PauseAudio(1); // play
    mp3dec_ex_seek(&_dec.mp3d, progress);
    SDL_Delay(delay);
    SDL_PauseAudio(0); // pause

// cleanup
    close_dec(&_dec);
    SDL_CloseAudio();

    cout << "play end" << endl;

    return EXIT_SUCCESS;
}
