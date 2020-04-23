/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 */


// play 440 Hz tone for 3 seconds
// reference : https://achapi2718.blogspot.com/2013/02/c-openal.html


#include <string> 
#include<iostream>
#include<limits.h>
#include <math.h>
#include<unistd.h>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

// 44.1 Khz
#define SAMPLINGRATE 44100

using namespace std;


/**
 * crateToneWav
 * 16 bit 44.1 KHz sampling
 */
int16_t* crateToneWav(double freq)
{

// buffer size for one second
	int16_t* wav_data = new int16_t[SAMPLINGRATE];

// radian per sample rate
	double delta = (2 * M_PI * freq ) / SAMPLINGRATE;

// Generate Sin wave for one second
	for (int i = 0; i < SAMPLINGRATE; i++) {
		wav_data[i] = SHRT_MAX * sin(delta * i);
	}

	return wav_data;
}


/**
 * main
 */
int main(int argc, char** argv)
{

// play 440 Hz tone for 3 seconds

	const double TONE_FREQ = 440.0; // Hz

	const unsigned int PLAY_DURATION = 3; // seconds


// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cout << "alcOpenDevice Faild" << endl;
		return 1;
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
		return 1;
	}

	alcMakeContextCurrent(context);


// generate Buffer and Source
	ALuint buffer;
	ALuint source;
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);



// generate audio data : 440Hz Sin wave for One second
	int16_t* wav_data = crateToneWav(TONE_FREQ);

// fills a buffer with audio data
	ALsizei size = SAMPLINGRATE * sizeof(int16_t);
	alBufferData(buffer, AL_FORMAT_MONO16, &wav_data[0], size, SAMPLINGRATE);

// play sound data in buffer
	alSourcei(source, AL_BUFFER, buffer);

// loop playback
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alSourcePlay(source);
	cout << "alSourcePlay"<< endl;

// play tone for 3 seconds
	sleep(PLAY_DURATION);

	alSourcePause(source);
	cout << "alSourcePause"<< endl;

// Cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	alcDestroyContext(context);
	alcCloseDevice(device);
	delete[] wav_data;

	return 0;
}

