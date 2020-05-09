/**
 * PulseAudio Sample
 * 2020-03-01 K.OHWADA
 */


// play tone
// reference : https://qiita.com/tose2125/items/9860b2b4b8805b28af8e

#include <string> 
#include<iostream>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <pulse/error.h>
#include <pulse/simple.h>

using namespace std;

#define APP_NAME "pulseaudio_sample"
#define STREAM_NAME "play"

// global
const int TONE_SAMPLINGRATE = 44100;
const int TONE_CHANNELS = 1;// mono


/**
 * crateTone
  * @param frequency : Hz
  * @param duration : sec
 * @return 16 bit 44.1 KHz sampling
 */
int16_t* crateTone(int freq, int duration, int *tone_size)
{

    int bufsize = TONE_SAMPLINGRATE * duration;
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
 *  main
 */
int main(int argc, char **argv) 
{

    int pa_errno, pa_result;

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


    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = TONE_SAMPLINGRATE;
    ss.channels = TONE_CHANNELS; 

    pa_simple *pa = pa_simple_new(NULL, APP_NAME, PA_STREAM_PLAYBACK, NULL, STREAM_NAME, &ss, NULL, NULL, &pa_errno);
    if (pa == NULL) {
        fprintf(stderr, "ERROR: Failed to connect pulseaudio server: %s\n", pa_strerror(pa_errno));
        return EXIT_FAILURE;
    }

    int tone_size;
    int16_t* data = crateTone(freq, duration, &tone_size);

    int write_size = sizeof(int16_t) *  tone_size;
    pa_result = pa_simple_write(pa, data, write_size, &pa_errno);
    if (pa_result < 0) {
            fprintf(stderr, "ERROR: Failed to write data to pulseaudio: %s\n", pa_strerror(pa_errno));
        return EXIT_FAILURE;
    }

    pa_simple_free(pa);
	delete[] data;

    return EXIT_SUCCESS;
}

