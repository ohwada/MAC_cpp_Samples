/**
 * wav Sample
 * 2020-03-01 K.OHWADA
 */

// create wav file of "Flog Song"
// "Flog Song" is Japanese popular kid song <br/>
// https://youtu.be/H18SYpZShmQ <br/>

#include <string> 
#include<iostream>

#include "wav_header.h"
#include "flog_song.hpp"

using namespace std;



/**
 * main
 */
int main(int argc, char** argv) 
{

   char* output = (char*)"flog_song.wav";	


    // open output
    FILE *fp_output = fopen(output, "wb");
	if ( !fp_output ) { 
        printf( "fopen Faild: %s \n", output);
		return 1;
	}


	// write dummy_header header
    writeDummyWavHeader(fp_output);

// get score
    std::vector<std::string> score = getFlogScore();

// process score and write pcm data to file
    for(auto itr = score.begin(); itr != score.end(); ++itr) {

// create pcm
        string note = *itr;
        int pcm_size;
		int16_t* pcm_data = createFlogPcm(note, &pcm_size);

// write pcm
        int write_size = FLOG_BYTES_PER_SAMPLE * pcm_size;
		int num_write = fwrite(pcm_data, 1, write_size, fp_output);
		if(num_write != write_size) {
					printf("pcm write error \n");
					//break;
		}

  } // for


// close
    fclose(fp_output);

	// write wav header
    overwriteWavHeader(output, (int)FLOG_CHANNELS, (int)FLOG_SAMPLINGRATE);

    printf("saved: %s \n", output);

    return 0;
}

