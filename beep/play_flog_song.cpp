/**
 * OpenAL Beep Sample
 * 2020-03-01 K.OHWADA
 */


// "Flog Song" is Japanese popular kid song <br/>
// https://youtu.be/H18SYpZShmQ <br/>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include<iostream>
#include<unistd.h>

#include "flog_song.hpp"

using namespace std;



/**
 * main
 */
int main(int argc, char** argv)
{

// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cout << "alcOpenDevice Faild" << endl;
		return 1;
	}

// create context
	ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		cout << "alcCreateContext Faild" << endl;
		return 1;
	}

	alcMakeContextCurrent(context);


// generate Buffer and Source
	ALuint buffer;
	ALuint source;
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

// get score
	vector<string> score = getFlogScore();

// process score and put pcm data in the queue 
    for(auto itr = score.begin(); itr != score.end(); ++itr) {

// create pcm
        string note = *itr;
        int pcm_size;
		int16_t* pcm_data = createFlogPcm(note, &pcm_size);

// set pcm
        alGenBuffers(1, &buffer);
		alBufferData(buffer, AL_FORMAT_MONO16, &pcm_data[0], pcm_size, FLOG_SAMPLINGRATE);

// queueing
        alSourceQueueBuffers(source, 1, &buffer);

  	} // for
  
	alSourcePlay(source);

// wait to finish
        ALint state = AL_PLAYING;
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

// Cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	alcDestroyContext(context);
	alcCloseDevice(device);

	return 0;
}

