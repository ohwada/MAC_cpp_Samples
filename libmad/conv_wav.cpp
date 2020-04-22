/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */


// convrt mp3 to wav
// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mad.h>

#include "wav_header.h"

#include"parse_filename.hpp"

using namespace std;

// global
const int SAMPLINGRATE = 44100; // 44.1 KHz
const int FRAME_LENGTH = 1152; // mp3 frame length
const int BUFF_SIZE  = 4 * FRAME_LENGTH;
const int CHANNELS_STEREO = 2;


struct mad_stream mad_stream;
struct mad_frame mad_frame;
struct mad_synth mad_synth;


// prototype
char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm);

int scale(mad_fixed_t sample);


/**
 * main
 */
int main(int argc, char **argv) 
{

    int error;
    int num_frames_total; 

	unsigned int frame_count = 0;

    FILE *fp_input;
    FILE *fp_output;


    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];


// append suffix to output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    char* output = (char*)outfile.c_str();


    // Initialize MAD library
    mad_stream_init(&mad_stream);
    mad_synth_init(&mad_synth);
    mad_frame_init(&mad_frame);


    // open input
    fp_input = fopen(input, "rb");
    if (!fp_input) {
        printf("fopen Failed: %s \n", input);
        return 1;
    }


    // Fetch file size, etc
    struct stat file_stat;
    int fd = fileno(fp_input);
    int ret = fstat(fd, & file_stat);
    if (ret != 0) {
        printf("fstat Failed: %s \n", input);
        fclose(fp_input);
        return 1;
    }

    int file_size = (int)file_stat.st_size;
    printf("open: %s (%d bytes) \n",  input, file_size);

    // Let kernel do all the dirty job of buffering etc, map file contents to memory
    unsigned char *input_stream = (unsigned char *)mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);

    // Copy pointer and length to mad_stream struct
    mad_stream_buffer(&mad_stream, input_stream, file_size);


    // open output
    fp_output = fopen(output, "wb");
	if ( !fp_output ) { 
        printf( "fopen Faild: %s \n", output);
		return 1;
	}


	// write dummy_header header
    writeDummyWavHeader(fp_output);


    // total  frames
    num_frames_total = ( file_size / FRAME_LENGTH ) ;
    printf("total: %d frames \n",  num_frames_total);


    // Decode frame and synthesize loop
    int isFirst = 1;

    while (1) {

        // Decode frame from the stream
        if (mad_frame_decode(&mad_frame, &mad_stream)) {
            enum mad_error stream_error = mad_stream.error;
            if (MAD_RECOVERABLE(stream_error)) {
                continue;
            } else if (stream_error == MAD_ERROR_BUFLEN) {
                continue;
            } else {
                break;
            }
        }

		frame_count++;

        // Synthesize PCM data of frame
        mad_synth_frame(&mad_synth, &mad_frame);
        //output(device, &mad_frame.header, &mad_synth.pcm);

    struct mad_pcm *pcm = &mad_synth.pcm;
    int pcm_samplerate = pcm->samplerate;
    int pcm_length = pcm->length;
    int pcm_channels = pcm->channels;
    if(pcm_length != FRAME_LENGTH) {
        printf("NOT support length = %d \n", pcm_length);
        continue; 
    }else if(pcm_samplerate != SAMPLINGRATE) {
        printf("NOT support samplerate = %d \n", pcm_samplerate);
        continue;
    }else if(pcm_channels != CHANNELS_STEREO) {
        printf("NOT support channels = %d \n", pcm_channels);
        continue;
    }
    if(isFirst){
        isFirst = 0;
        printf("length = %d \n", pcm_length);
        printf("channels = %d \n", pcm_channels);
        printf("samplerate = %d \n", pcm_samplerate);
    }


        char *data = getStereoData(&mad_frame.header, &mad_synth.pcm);


// write pcm
		int num_write = fwrite(data, 1, BUFF_SIZE, fp_output);
		if(num_write != BUFF_SIZE) {
					printf("pcm write error \n");
					//break;
		}


        if(frame_count > (num_frames_total + 10)){
            // maybe loaded all the frames
            // margin 10 frames
            break;
        }

    } // while


    // Close
    fclose(fp_input);
    fclose(fp_output);


    // Free MAD structs
    mad_synth_finish(&mad_synth);
    mad_frame_finish(&mad_frame);
    mad_stream_finish(&mad_stream);


	// write wav header
    writeWavHeader(output, CHANNELS_STEREO, SAMPLINGRATE);

    printf("saved: %s \n", output);

    return EXIT_SUCCESS;
}


// Some helper functions, to be cleaned up in the future
int scale(mad_fixed_t sample) {
     /* round */
     sample += (1L << (MAD_F_FRACBITS - 16));
     /* clip */
     if (sample >= MAD_F_ONE)
         sample = MAD_F_ONE - 1;
     else if (sample < -MAD_F_ONE)
         sample = -MAD_F_ONE;
     /* quantize */
     return sample >> (MAD_F_FRACBITS + 1 - 16);
}



/**
 * getStereoData
 */
char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm) {
    int length = pcm->length;
    int channels = pcm->channels;
    register int nsamples = length;
    const mad_fixed_t *left_ch = pcm->samples[0];
    const mad_fixed_t *right_ch = pcm->samples[1];


    if (channels != 2) {
        printf("Mono not supported! \n");
        return NULL;
    }


    // stereo
    char *buff = new char[BUFF_SIZE];

    while (nsamples--) {
            int index = 4 * (length - nsamples);
            signed int sample_left = scale(*left_ch++);
            signed int sample_right = scale(*right_ch++);
            buff[index + 0 ] = ((sample_left >> 0) & 0xff);
            buff[index +1] = ((sample_left >> 8) & 0xff);
            buff[index+2 ] = ((sample_right >> 0) & 0xff);
            buff[index +3] = ((sample_right >> 8) & 0xff);
        } // while

    return buff;
}

