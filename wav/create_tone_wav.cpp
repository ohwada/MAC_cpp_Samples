/**
 * create_tone_wav.cpp
 * 2020-03-01 K.OHWADA
 */

// create tone wav file

#include <string> 
#include<iostream>
#include<math.h>

#include "wav_header.h"

using namespace std;

// global
const int TONE_SAMPLINGRATE = 44100;
const int TONE_CHANNELS = 1;
const int TONE_BITS = 16;

/**
 * createTone
  * @param frequency : Hz
  * @param duration : sec
 * @return 16 bit 44.1 KHz sampling
 */
int16_t* createTone(int freq, int duration, int *tone_size)
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
 * createOutputFileName
 */
std::string createOutputFileName(int freq, int duration)
{
    const char UNDERBAR = '_';
    string str_freq = std::to_string(freq);
    string str_duration = std::to_string(duration);
    string output = "tone_" +  str_freq + UNDERBAR + str_duration +".wav";
    return output;
}


/**
 * main
 */
int main(int argc, char** argv) 
{
    int freq = 440; // Hz
    int duration = 1; // sec

    if(argc == 3) {
        freq = atoi(argv[1]);
        duration = atoi(argv[2]);

    } else if(argc == 2) {
        freq = atoi(argv[1]);
    } else {
        cerr << "Usage: " << argv[0] << " [freq] [duration] "  << endl;
        return EXIT_FAILURE;
    }

    string output = createOutputFileName(freq, duration);	


    // open output
    FILE *fp_output = fopen(output.c_str(), "wb");
	if ( !fp_output ) { 
       cerr << "fopen Faild: " << output << endl;
        return EXIT_FAILURE;
	}

	// write dummy_header header
    writeDummyWavHeader(fp_output);

// create tone
    int tone_size;
    int16_t* data = createTone(freq, duration, &tone_size);

// write tone
    int write_size = sizeof(int16_t) * tone_size;
	int num_write = fwrite(data, 1, write_size, fp_output);
	if(num_write != write_size) {
			cerr << "fwrite Faild" << endl;
             fclose(fp_output);
            return EXIT_FAILURE;
	}

// close
    fclose(fp_output);

	// write wav header
    overwriteWavHeader((char *)output.c_str(), TONE_CHANNELS, TONE_BITS, TONE_SAMPLINGRATE);

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

