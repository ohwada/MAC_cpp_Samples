/**
 * libvorbis Sample
 * 2020-03-01 K.OHWADA
 */


// play ogg file with OpenAL
// reference : https://w.atwiki.jp/opengl/pages/172.html

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "OggReader.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{

    OggReader reader;

    ALuint source, buffer;
    ALint state, num;

    if(argc < 2) {
        cout << "Usage: " << argv[0]  << " <oggFile> " << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];

    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        printf( "alcOpenDevice Faild \n");
        return EXIT_FAILURE;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        cout << "alcCreateContext Faild" << endl;
        return EXIT_FAILURE;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);


    int ret1 = reader.open(input);
    if(ret1 != 0){
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    reader.printFileInfo();

    // number of 10 seconds frames
    int num_frames_about_10_secs = 10 *  reader.FRAMES_PER_SEC;

// endless loop
// exit the loop, when read all the data
    int isFirst = 1; // show debug message at once 
    while(1) {

        int ret2 = reader.read();
        if(ret2 == OGG_READER_END){
            break;
        }

        if(isFirst){
            isFirst = 0;
            reader.printOvInfo();
        }

        char *data = reader.getBuffer();

        alGetSourcei(source, AL_BUFFERS_QUEUED, &num);
        if (num < num_frames_about_10_secs) {
            // reading data
            alGenBuffers(1, &buffer);
        } else {
            // it seems that all the data has been read
            alGetSourcei(source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    // play in not
                    alSourcePlay(source);
                    cout << "\n alSourcePlay" << endl;
                }

                // wait for the buffer to be processed
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(source, 1, &buffer);

        } // if num

        alBufferData(buffer, AL_FORMAT_STEREO16, data, OGG_READER_BUFF_SIZE, OGG_READER_SAMPLINGRATE);
        alSourceQueueBuffers(source, 1, &buffer);

        reader.printPregress();

    } //  while


// close
    reader.close();
    fprintf(stderr, "\n"); // add LF to progress


// play if not
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source);
        cout << "alSourcePlay" << endl;
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
             cout << "play Faild: " << err << endl;
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
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

	return EXIT_SUCCESS;
}

