/**
 * fdk aac Sample
 * 2020-03-01 K.OHWADA
 */



// play aac file

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <string>
#include <iostream>
#include<unistd.h>

#include "AacReader.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv) 
{

	AacReader reader;

    ALuint source;
    ALuint buffer;
    ALint state;
    ALint  num;


    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <aacFile> "  << endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];


    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        cout << "alcOpenDevice Faild" << endl;
        return EXIT_FAILURE;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        cout << "aalcCreateContext  Faild" << endl;
        return EXIT_FAILURE;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);


// read input
	int ret1 = reader.readFile(input);
    if(ret1 != 0){
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    // number of 10 seconds frames
    int num_frames_about_10_secs = 10 *  reader.FRAMES_PER_SEC;

    // printf("num_frames_about_10_secs: %d \n", num_frames_about_10_secs);


    // Decode frame and synthesize loop
    while (1) {

        // Decode frame from the stream
	    int ret = reader.decodeAac();
    	if (ret == AAC_READER_END) {
    		break;
    	}else if (ret == AAC_READER_CONTINUE) {
			continue;
    	}

	    char* data = reader.getPcmData();
        int data_size = reader.getPcmDataSize();

        alGetSourcei(source, AL_BUFFERS_QUEUED, &num);
        if (num < num_frames_about_10_secs) {
            // wait for the first 10 seconds
            alGenBuffers(1, &buffer);

        } else {
            // it seems to finish reading frames of the first 10 seconds
            alGetSourcei(source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    // play in not
                    alSourcePlay(source);
                    fprintf(stderr, "\n"); // add LF to progress
                    cout <<  "alSourcePlay" << endl;
                }

                // wait for the buffer to be processed
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(source, 1, &buffer);

        } // if num


        alBufferData(buffer,  AL_FORMAT_STEREO16,  data, data_size,  AAC_READER_SAMPLINGRATE);

        alSourceQueueBuffers(source, 1, &buffer);

        // progress info
        reader.printPregress();

    } // while


// play if not
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source);
        cout <<  "alSourcePlay" << endl;
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
     reader.freeBuffer();
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    fprintf(stderr, "\n"); // add LF to progress
    cout <<  "play end" << endl;

    return EXIT_SUCCESS;
}

