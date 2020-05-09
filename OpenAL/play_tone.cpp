/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 */


// play tone
// reference : https://achapi2718.blogspot.com/2013/02/c-openal.html

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <string> 
#include<iostream>
#include<limits.h>
#include <math.h>
#include<unistd.h>

using namespace std;

// global
const int TONE_SAMPLINGRATE = 44100;


/**
 * crateTone
  * @param frequency : Hz
  * @param duration : sec
 * @return 16 bit 44.1 KHz sampling
 */
int16_t* crateTone(int freq, int duration, int *tone_size)
{

    int bufsize = TONE_SAMPLINGRATE  * duration;
	int16_t* buff = new int16_t[bufsize];

// radian per sample rate
	double delta = (2 * M_PI * freq ) / TONE_SAMPLINGRATE;

// Generate Sin wave 
	for (int i = 0; i < bufsize; i++) {
		buff[i] = SHRT_MAX * sin(delta * i);
	}

    *tone_size = bufsize;
	return buff;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    int freq = 440; // Hz
    int duration = 1; // sec


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " [freq] [duration] "  << endl;

    } else if(argc == 3) {
        freq = atoi(argv[1]);
        duration = atoi(argv[2]);

    } else if(argc == 2) {
        freq = atoi(argv[1]);
    }


// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cerr << "alcOpenDevice Faild" << endl;
        return EXIT_FAILURE;
	}

	// version
	ALCint major_version;
	ALCint minor_version;
	alcGetIntegerv(
    	device, ALC_MAJOR_VERSION, 256, &major_version);
	alcGetIntegerv(
    	device, ALC_MINOR_VERSION, 256, &minor_version);

	printf("OpenAL Version: %d.%d \n", major_version, minor_version);


	ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		cout << "alcCreateContext Faild" << endl;
        return EXIT_FAILURE;
	}

	alcMakeContextCurrent(context);


// generate Buffer and Source
	ALuint buffer;
	ALuint source;
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);



// generate tone
    int tone_size;
	int16_t* data = crateTone(freq, duration, &tone_size);

// fills a buffer with audio data
	int data_size =  tone_size * sizeof(int16_t);
	alBufferData(buffer, AL_FORMAT_MONO16, &data[0], data_size, TONE_SAMPLINGRATE);

// play sound data in buffer
	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);
	sleep(duration);
	alSourcePause(source);

// Cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	alcDestroyContext(context);
	alcCloseDevice(device);
	delete[] data;

    return EXIT_SUCCESS;
}

