/**
 * wav Sample
 * 2020-03-01 K.OHWADA
 */

// play wav file with OenAL
// http://www-fps.nifs.ac.jp/ito/memo/openal02.html

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#include "wav_header.h"


/**
 * getFormat
 */
ALenum getFormat(int wavChannels,  int wavBit)
{
	ALenum format;
	if(wavChannels == WAVH_CHANNELS_MONO){
		if(wavBit == 8) {
			format = AL_FORMAT_MONO8;
		}else if(wavBit == 16) {
			format = AL_FORMAT_MONO16;
		}
	}else if(wavChannels == WAVH_CHANNELS_STEREO){
		if(wavBit== 8){
			format = AL_FORMAT_STEREO8;
		}else if(wavBit == 16) {
			format = AL_FORMAT_STEREO16;
		}
	}
	return format;
}


/**
 * main
 */
int main (int argc, char **argv)
{
	
	ALuint source;
	ALuint buffer;
	
    if (argc != 2) {
        printf( "Usage: %s <wavFile> \n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];


// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		printf("alcOpenDevice Faild \n");
        return EXIT_FAILURE;
	}


		ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		printf("alcCreateContext Faild \n");
        return EXIT_FAILURE;
	}

	alcMakeContextCurrent(context);

	alGenSources (1, &source);
	alGenBuffers(1, &buffer);

	FILE* fp = fopen(input,"rb");
	if(!fp){
		printf("fopen Faild: %s\n", input);
        return EXIT_FAILURE;
	}

	printf("fopen : %s\n", input);

	// read header
	int wavChannels, wavBit, wavSize, wavSamplingrate;
	int ret = readWavHeader(fp, &wavChannels, &wavBit, &wavSize, &wavSamplingrate);
	if (ret != 0){
		printf("NOT wav format \n");
        return EXIT_FAILURE;
	}

	printf("wavChannels: %d \n", wavChannels);
	printf("wavBit: %d \n", wavBit);
	printf("wavSize: %d \n", wavSize);
	printf("wavSamplingrate: %d \n", wavSamplingrate);

	int time_playback = (float)wavSize / (float)(4*wavSamplingrate);
	printf("time_playback: %d sec \n", time_playback);


	// read pcm data
	unsigned char * data = new unsigned char[wavSize];

	int rsize = fread(data, 1, wavSize, fp);
		if(rsize != wavSize){
			printf("fread faild \n");
		}

	ALenum format = getFormat(wavChannels,  wavBit);
	alBufferData(buffer, format, data, wavSize, wavSamplingrate);

	alSourcei (source, AL_BUFFER, buffer);

	alSourcePlay (source);
	printf("alSourcePlay \n");

	int time_count = 0;
	while(1)
	{
		sleep (1);

		time_count++;
		if(time_count > time_playback) {
			break;
		}

		// progess info
		int time_remain = time_playback - time_count;
    	fprintf(stderr, "\r ( %3d sec)",  time_remain);
	}

	// cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	
	delete [] data;
	fclose(fp);

	printf("end \n");

	return EXIT_SUCCESS;
}

