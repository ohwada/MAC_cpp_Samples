/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */


// play mp3 file with OpenAL

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include "MP3Reader.hpp"


/**
 * main
 */
int main(int argc, char **argv) 
{

    MP3Reader reader;


    ALuint source;
    ALuint buffer;
    ALint state;
    ALint  num;


    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];


    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        printf("alcOpenDevice Faild \n");
		return 1;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        printf("aalcCreateContext  Faild \n");
		return 1;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);


    // open input
    int ret = reader.open(input);
    if(ret != 0){
        printf("fopen Failed: %s \n", input);
        return 1;
    }

    reader.printFileInfo();

    // number of 10 seconds frames
    int num_frames_about_10_secs = 10 *  reader.FRAMES_PER_SEC;


    // Decode frame and synthesize loop
    while (1) {

        // Decode frame from the stream
    int ret2 = reader.decode();
        if (ret2 == MP3_DECODE_SKIP) {
                continue;
        } else if (ret2 == MP3_DECODE_END) { 
                break;
        }

    unsigned char* data = reader.getFrameData();
    int size = reader.getFrameDataSize();

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
                    fprintf(stderr, "\n alSourcePlay \n");
                }

                // wait for the buffer to be processed
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(source, 1, &buffer);

        } // if num


        alBufferData(buffer,  AL_FORMAT_STEREO16,  data, size,  MP3_SAMPLINGRATE);

        alSourceQueueBuffers(source, 1, &buffer);

        // progress info
        reader.printPregress();

    } // while


    // Close
    reader.close();
    fprintf(stderr, "\n"); // add LF to progress


// play if not
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source);
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
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return EXIT_SUCCESS;
}

