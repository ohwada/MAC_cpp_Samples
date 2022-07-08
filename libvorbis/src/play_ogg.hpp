/**
 * play_ogg.hpp
 * 2022-06-01 K.OHWADA
 */


// play ogg file with OpenAL


// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <stdio.h>
# include <unistd.h> // sleep
#include "play.h"


bool _play_ogg(char* file) ;
void play_buffer(int size, int rate, unsigned char *data );


const int OGG_FORMAT = AL_FORMAT_STEREO16;


// global variable
ALuint source;
int cnt_call = 0;


/**
 * play_ogg
 */
bool play_ogg(char* file) 
{
    const int MAX_TIME = 60;  // 60 sec

    FILE *fp = fopen(file, "rb");
    if(!fp){
         fprintf(stderr, "fopen Faild: %s \n", file);
        return false;
    }

     ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
         fprintf(stderr, "alcOpenDevice Faild \n");
        return false;
	}

    ALCcontext *context  = alcCreateContext(device, NULL);
	   if (!context){
         fprintf(stderr, "alcCreateContext Faild \n");
        return false;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);

    FUNC_POINTER p;
    p = play_buffer;
    bool ret = play( fp, p);
    if(ret != 0){
        return false;
    }


  // play
     alSourcePlay(source);
    fprintf(stderr, "alSourcePlay \n" );

    int cnt_time = 0;
    ALint state;
 while(1) 
{
	    sleep(1); // 1 sec

      alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        break;
    }

		// progess info
		cnt_time++;
    fprintf(stderr, "\r ( %3d sec ) ",  cnt_time);
 

        if ( cnt_time > MAX_TIME ){
	        fprintf(stderr, "time over \n "  );
            break;
        }

} // while

    fprintf(stderr, "close \n" );


// close
    fclose(fp);
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return true;
}


/**
 *  play_buffer
 */
void play_buffer(int size, int rate, unsigned char *data )
{
    cnt_call ++;
    fprintf(stderr, "\r buffer: %d ", cnt_call);

    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, OGG_FORMAT, data, 
    size, rate);
    alSourceQueueBuffers(source, 1, &buffer);

}


