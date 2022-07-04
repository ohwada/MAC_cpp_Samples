#pragma once
/**
 * play_music.h
 * 2022-05-01 K.OHWADA
 */

// reference: https://k38.hatenadiary.jp/entry/2018/10/26/005855


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

bool playMusic(char* file);



/**
 *  playMusic
 */
bool playMusic(char* file)
{

    Mix_Music *music = NULL;


        // Initialize SDL.
        if (SDL_Init(SDL_INIT_AUDIO) < 0){
                printf("SDL_Init: %s\n",Mix_GetError() );
                return false;
        }

        // Initialize SDL_mixer 
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
            printf("Mix_OpenAudio: %s\n",Mix_GetError() );
           return false;
        }

    // set the volume in the range of 0 to 128
    Mix_VolumeMusic(64);

        // load music files
        music = Mix_LoadMUS(file);
        if (music == NULL){
            printf("Mix_LoadMUS: %s\n",Mix_GetError() );
           return false;
        }

        //  play music once
        if ( Mix_PlayMusic( music, 1) == -1 ){
            printf("Mix_PlayMusic: %s\n",Mix_GetError() );
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

        Mix_FreeMusic(music);

        // quit SDL2_mixer
        Mix_CloseAudio();

        return true;
}

