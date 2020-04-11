/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 */


// play wav file
// reference : https://w.atwiki.jp/darui_program/pages/94.html


#include <string> 
#include<iostream>
#include<limits.h>
#include <math.h>
#include<unistd.h>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <OpenAL/alure.h>


using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{

	const unsigned int PLAY_DURATION = 1; // play one time

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputAudioFile> "  << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];

// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cout << "alcOpenDevice Faild" << endl;
		return 1;
	}

	ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		cout << "alcCreateContext Faild" << endl;
		return 1;
	}

	alcMakeContextCurrent(context);

// read wav file
	ALuint buffer = alureCreateBufferFromFile(input);


// generate Buffer and Source
	ALuint source;
	alGenSources(1, &source);

// play sound data in buffer
	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);
	cout << "alSourcePlay"<< endl;

// play one time
	sleep(PLAY_DURATION);

	alSourcePause(source);
	cout << "alSourcePause"<< endl;

// Cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	alcDestroyContext(context);
	alcCloseDevice(device);

//alutExit();

	return 0;
}

