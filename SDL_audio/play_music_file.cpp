/**
 * SDL Mixer Sample
 * 2020-02-01 K.OHWADA
 */


// play music file
// suport format : wav, ogg
// NOT support mp3

// reference : https://k38.hatenadiary.jp/entry/2018/10/26/005855


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include<iostream>

using namespace std;



/**
 * main
 */
int main(int argc, char **argv)
{

    const int MUSIC_CHANNELS_STEREO = 2;
    const int MUSIC_CHUNKSIZE = 4096;
    const int MUSIC_LOOPS = 1;


    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <musicFile> " << endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];


    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) != 0){
        cout <<  "SDL_Init Failed" << endl;
        return EXIT_FAILURE;
    }


    // Initialize SDL_mixer 
    int ret1 = Mix_OpenAudio( 
    MIX_DEFAULT_FREQUENCY, // 22050
    MIX_DEFAULT_FORMAT, // 16bit unsigned 16 bit, system byte order
    MUSIC_CHANNELS_STEREO, 
    MUSIC_CHUNKSIZE
    );

    if(ret1 != 0 ){
        cout << "Mix_OpenAudio Failed" << endl;
        return EXIT_FAILURE;
    }


    // load music file
    Mix_Music *music = Mix_LoadMUS(input);
    if (!music){
            cout << "Mix_LoadMUS Failed: " << Mix_GetError() << endl;
            return EXIT_FAILURE;
    }


    // play music once
    int ret2 = Mix_PlayMusic( music, MUSIC_LOOPS);
    if ( ret2 != 0 ){
            cout << "Mix_PlayMusic Failed: " << endl;
            return EXIT_FAILURE;
    }


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

    } // while 

    fprintf(stderr, "\n"); // add LF to progress

    // cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();

	return EXIT_SUCCESS;
}

