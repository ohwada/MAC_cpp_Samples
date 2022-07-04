#pragma once
/**
 * play_music.h
 * 2020-02-01 K.OHWADA
 */


// reference : https://k38.hatenadiary.jp/entry/2018/10/26/005855


#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool playMusic(char *file);


/**
 * playMusic
 */
bool playMusic(char *file)
{

    const int MUSIC_CHANNELS_STEREO = 2;
    const int MUSIC_CHUNKSIZE = 4096;
    const int MUSIC_LOOPS = 1;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) != 0){
        printf("SDL_Init: %s\n",Mix_GetError() );
        return false;
    }


    // Initialize SDL_mixer 
    int ret1 = Mix_OpenAudio( 
    MIX_DEFAULT_FREQUENCY, // 22050
    MIX_DEFAULT_FORMAT, // 16bit unsigned 16 bit, system byte order
    MUSIC_CHANNELS_STEREO, 
    MUSIC_CHUNKSIZE
    );

    if(ret1 != 0 ){
        printf("Mix_OpenAudio : %s \n",  Mix_GetError() );
        return false;
    }


    // load music file
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music){
            printf("Mix_LoadMUS : %s \n",  Mix_GetError() );
            return false;
    }


    // play music once
    int ret2 = Mix_PlayMusic( music, MUSIC_LOOPS);
    if ( ret2 != 0 ){
            printf("Mix_PlayMusic : %s \n",  Mix_GetError() );
            return false;
    }

    const int MAX = 60; // 60 sec

    // wait to finish play
	int time_count = 0;
	while(1)
	{

		SDL_Delay(1000); // 1 sec

        // wait to finish play
        if( Mix_PlayingMusic() == 0 ){
            break;
        }

		// progess info
		time_count++;
		//int time_remain = time_playback - time_count;
    	fprintf(stderr, "\r ( %3d sec ) ",  time_count);

        if ( time_count > MAX ){
	        fprintf(stderr, "time over \r "  );
            break;
        }
 
    } // while 

    fprintf(stderr, "\n");


    // cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();

	return true;
}

