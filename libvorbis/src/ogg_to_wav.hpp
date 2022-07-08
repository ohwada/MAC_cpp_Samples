#pragma once
/**
 * ogg_to_wav.hpp
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string> 
#include"decoder.h"
#include "wav_header.h"

// prototype
int ogg_to_wav(std::string input, std::string output);
std::string add_wav_ext(std::string fname);


/**
 * ogg_to_wav
 */
int ogg_to_wav(std::string str_input, std::string str_output) 
{
    char *input = (char *)str_input.c_str();
    char *output = (char *)str_output.c_str();

    // open input
    FILE *fpin = fopen(input, "rb");
	if ( !fpin) { 
        fprintf(stderr, "cannot open: %s \n", input);
        return 1;
	}

    // open output
    FILE *fpout = fopen(output, "wb");
	if ( !fpout ) { 
        fprintf(stderr, "cannot open: %s \n", output);
        return 1;
	}

bool ret1 = writeDummyWavHeader(fpout);
	if ( !ret1 ) { 
        fprintf(stderr, "cannot write: %s \n", output);
        return 1;
	}

    int channels;
    int rate;
    int ret2 = decode(fpin, fpout, &channels, &rate);
    if(ret2 == 0){
        printf("save to: %s \n \n", output);
    }

    fclose(fpin);
    fclose(fpout);


	// write wav header
    overwriteWavHeader(output, channels, 
    WAVH_BITSPERSAMPLE16, rate);

	return 0;
}


/**
 *  add_wav_ext
 */
std::string  add_wav_ext(std::string fname)
{
    std::string ext(".wav");
    std::string ret = fname + ext;
    return ret;
}

