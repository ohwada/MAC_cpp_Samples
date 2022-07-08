#pragma once
/**
 * wav_to_ogg.hpp
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string> 
#include"encoder.h"

// prototype
int wav_to_ogg(std::string input, std::string output);
std::string add_ogg_ext(std::string fname);


/**
 * wav_to_ogg
 */
int wav_to_ogg(std::string str_input, std::string str_output) 
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

    int ret = encode(fpin, fpout);
    if(ret == 0){
        printf("save to: %s \n \n", output);
    }

    fclose(fpin);
    fclose(fpout);

	return 0;
}


/**
 *  add_ogg_ext
 */
std::string  add_ogg_ext(std::string fname)
{
    std::string ext(".ogg");
    std::string ret = fname + ext;
    return ret;
}

