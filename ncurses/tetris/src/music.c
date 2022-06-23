// 2022-05-01 K.OHWADA
// original : https://github.com/brenns10/tetris

// change log 
// 2022-05-01
// create this file
// chang SDL_mixer to SDL2_mixer

#if WITH_SDL
# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
#endif

#include <stdio.h>

#include "music.h"
#include "file_util.h"

const char FILE_MUSIC[] = "tetris.mp3";

// volume : 0 to 128
const int VOLUME = 16;

#if WITH_SDL 
  Mix_Music *music = NULL;
#endif


/**
 *  pauseMusic
 */
void pauseMusic()
{
#if WITH_SDL 
   Mix_PauseMusic();
#endif
}


/**
 *  resumeMusic
 */
 void  resumeMusic()
{
#if WITH_SDL 
  Mix_ResumeMusic();
#endif
}


/**
 * initMusic
 * return 0: succesful 1: ffaild
 */
int initMusic()
{

#if WITH_SDL 

    // Check for the existence of the file
    if( existsFile( (char *)FILE_MUSIC ) != 0 ) {
        fprintf(stderr, "not found FILE_MUSIC: %s \n", (char *)FILE_MUSIC );
        return 1;
    }

        // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
                fprintf(stderr, "SDL_Init: %s\n",Mix_GetError() );
                return 1;
        }

        // Initialize SDL_mixer 
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
            fprintf(stderr, "Mix_OpenAudio: %s\n",Mix_GetError() );
           return 1;
        }

    // set the volume
    Mix_VolumeMusic(VOLUME);

        // load music files
        music = Mix_LoadMUS( FILE_MUSIC);
        if (music == NULL){
            fprintf(stderr, "Mix_LoadMUS: %s\n",Mix_GetError() );
           return 1;
        }

#endif

    return 0;
}


/**
 * playMusic
 * return 0: succesful 1: ffaild
 */
int playMusic()
{

#if WITH_SDL 

    Mix_AllocateChannels(1); // only need background music

    //  play music endless
    if ( Mix_PlayMusic( music, -1) == -1 ){
            fprintf(stderr, "Mix_PlayMusic: %s\n",Mix_GetError() );
           return 1;
    }

#endif

    return 0;
}


/**
 *  closeMusic
 */
void closeMisic()
{

#if WITH_SDL 
  // Deinitialize Sound
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  Mix_Quit();
#endif

    return;
}

