/**
 * libvorbis Sample
 * 2020-03-01 K.OHWADA
 */


// convert ogg to wav
// reference : https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM

#include <string> 
#include<iostream>

#include "vorbis/vorbisfile.h"

#include "wav_header.h"

#include"parse_filename.hpp"

using namespace std;


#define OV_BUFFER_SIZE 4096


/**
 * main
 */
int main(int argc, char** argv) 
{

    char ov_buffer[OV_BUFFER_SIZE];
    int ov_current = 0;


    FILE *fp_output;
    FILE *fp_input;
    OggVorbis_File ovf;
    int ov_channels;
    int ov_rate;


    if(argc < 2) {
        printf( "Usage: %s <oggFile> \n",  argv[0]);
        return 1;
    }

   char* input = argv[1];	


// append suffix to output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    char* output = (char*)outfile.c_str();


    // open input
    fp_input = fopen(input, "rb");
	if (!fp_input){
        printf( "fopen Faild: %s \n", input);
		return 1;
	}
    printf( "open input: %s \n", input);


    // open output
    fp_output = fopen(output, "wb");
	if ( !fp_output ) { 
        printf( "fopen Faild: %s \n", output);
		return 1;
	}


	// write dummy_header header
    writeDummyWavHeader(fp_output);



    // open ogg Vorbis
    int ret = ov_open(fp_input, &ovf, NULL, 0);
	if (ret != 0){
        printf( "ov_open Faild: %s \n", input);
        fclose(fp_input);
		return 1;
	}


	size_t total = ov_pcm_total(&ovf, -1);
    printf("pcm_total = %ld \n", total);

    int num_buffers = total / OV_BUFFER_SIZE;

// endless loop
// exit the loop, when read all the ov_data
    int isFirst = 1; // show debug message at once 
    while(1) {

// if the passed in buffer is large, ov_read() will not fill it
// the passed in buffer size is treated as a limit and not a request. 
        long read_size = ov_read(
            &ovf, ov_buffer, 
            OV_BUFFER_SIZE, 
            0,  //  little endian
            2,  // 16-bit samples
            1, // signed
            &ov_current );

        if (read_size == 0) {
            //  read all the ov_data
            break;
        }

// ov_info
        vorbis_info *info = ov_info(&ovf, -1);

        if(isFirst){
            isFirst = 0;
            ov_channels = info->channels;
            ov_rate = info->rate;
            printf("vorbis_info version = %d \n", info->version);
            printf("vorbis_info channels = %d \n", ov_channels);
            printf("vorbis_info rate = %d \n", ov_rate);
        }

// write pcm
        int size_buffer = sizeof(ov_buffer);
		int num_write = fwrite(ov_buffer, 1, size_buffer, fp_output);
		if(num_write != size_buffer) {
					printf("pcm write error \n");
					//break;
		}

    } //  while


// close
    fclose(fp_input);
    fclose(fp_output);
    ov_clear(&ovf);

	// write wav header
    writeWavHeader(output, ov_channels, ov_rate);

    printf("saved: %s \n", output);

    return 0;
}

