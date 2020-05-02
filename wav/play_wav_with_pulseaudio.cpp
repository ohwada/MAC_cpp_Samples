/**
 * wav Sample
 * 2020-03-01 K.OHWADA
 */


// play wav file with PulseAudio
// reference : https://qiita.com/tose2125/items/9860b2b4b8805b28af8e


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include <pulse/error.h>
#include <pulse/simple.h>

#include "wav_header.h"

#define APP_NAME "pulseaudio_sample"
#define STREAM_NAME "play"



/**
 *  main
 */
int main(int argc, char **argv) 
{

    int pa_errno, pa_result, read_bytes;

    if (argc != 2) {
        printf( "Usage: %s <wavFile> \n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];

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

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = wavSamplingrate;
    ss.channels = wavChannels;

    pa_simple *pa = pa_simple_new(NULL, APP_NAME, PA_STREAM_PLAYBACK, NULL, STREAM_NAME, &ss, NULL, NULL, &pa_errno);
    if (pa == NULL) {
        fprintf(stderr, "ERROR: Failed to connect pulseaudio server: %s\n", pa_strerror(pa_errno));
        return 1;
    }

    pa_result = pa_simple_write(pa, data, wavSize, &pa_errno);
    if (pa_result < 0) {
            fprintf(stderr, "ERROR: Failed to write data to pulseaudio: %s\n", pa_strerror(pa_errno));
            return 1;
    }

    pa_simple_free(pa);
    return 0;
}

