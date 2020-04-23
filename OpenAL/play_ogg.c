/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 */


// play ogg file
// reference : https://w.atwiki.jp/opengl/pages/172.html

#include <stdlib.h>
#include <stdio.h>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include "vorbis/vorbisfile.h"


#define BUFFER_SIZE 4096


/**
 * main
 */
int main(int argc, char** argv) 
{

    char data[BUFFER_SIZE];
    ALuint source, buffer;
    ALint state, num;
    int current = 0;


    if(argc < 2) {
        printf( "Usage: %s <oggFile> \n",  argv[0]);
        return 1;
    }

   char* input = argv[1];

    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        printf( "alcOpenDevice Faild \n");
		return 1;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        printf( "alcCreateContext Faild \n");
		return 1;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);

    FILE *fp = fopen(input, "rb");
	if (!fp){
        printf( "fopen Faild: %s \n", input);
		return 1;
	}

        printf( "fopen: %s \n", input);

    OggVorbis_File vf;
    int ret = ov_open(fp, &vf, NULL, 0);
	if (ret != 0){
        printf( "ov_open Faild: %s \n", input);
        fclose(fp);
		return 1;
	}

	size_t total = ov_pcm_total(&vf, -1);
    printf("pcm_total = %ld \n", total);

    int num_buffers = total / BUFFER_SIZE;

// endless loop
// exit the loop, when read all the data
    int isFirst = 1; // show debug message at once 
    while(1) {

// if the passed in buffer is large, ov_read() will not fill it
// the passed in buffer size is treated as a limit and not a request. 
        long size = ov_read(
            &vf, data, 
            BUFFER_SIZE, 
            0,  //  little endian
            2,  // 16-bit samples
            1, // signed
            &current );


        if (size == 0) {
            //  read all the data
            break;
        }

        vorbis_info *info = ov_info(&vf, -1);

        if(isFirst){
            isFirst = 0;
            printf("vorbis_info version = %d \n", info->version);
            printf("vorbis_info channels = %d \n", info->channels);
            printf("vorbis_info rate = %ld \n", info->rate);
        }

        ALenum format =  (info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        alGetSourcei(source, AL_BUFFERS_QUEUED, &num);
        if (num < num_buffers) {
            // reading data
            alGenBuffers(1, &buffer);
        } else {
            // it seems that all the data has been read
            alGetSourcei(source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    // play in not
                    alSourcePlay(source);
                }

                // wait for the buffer to be processed
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(source, 1, &buffer);

        } // if num

        alBufferData(buffer, format, data, size, info->rate);
        alSourceQueueBuffers(source, 1, &buffer);

    } //  while


// play if not
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source);
        printf("alSourcePlay \n");
    }


// wait to finish
    state = AL_PLAYING;
    while (1)
    {

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING){
            // finish
            break;
        }

        ALenum err = alGetError(); 
        if(err != AL_NO_ERROR){
             printf("play Faild: %d \n", err);
            break;
        }


        sleep(1);

  } // while


// remove queueing buffers
    ALint num_processed;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_processed);
    for(int i=0; i<num_processed; i++){
        alSourceUnqueueBuffers(source, 1, &buffer);
        alDeleteBuffers(1, &buffer);
    }


// cleanup
    ov_clear(&vf);
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}

