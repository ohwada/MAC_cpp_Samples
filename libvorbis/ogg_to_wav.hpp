#pragma once
/**
 * ogg_to_wav.hpp
 * 2020-03-01 K.OHWADA
 */


//DECODEert ogg to wav
// reference : https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM

#include <string> 

#include "ogg_reader.hpp"

#include "wav_header.h"

#include"file_list.hpp"

const int DECODE_SUCCESS = 0;
const int DECODE_ERR_INPUT = 1;
const int DECODE_ERR_OUTPUT = 2;
const int DECODE_ERR_FORMAT = 3;
const int DECODE_ERR_WRITE = 4;

// prototype
int convOggToWav(std::string input, std::string output);
int ogg_to_wav(char *input, char *output);
std::string addExtWav( std::string file);


/**
 * convOggToWav
 */
int convOggToWav(std::string input, std::string output)
{
    return ogg_to_wav( (char *)input.c_str(), 
(char *)output.c_str() );
}


/**
 * ogg_to_wav
 */
int ogg_to_wav(char *input, char *output)
{
    OggReader reader;

    int ret1 = reader.open(input);
    if(ret1 == OGG_ERR_FOPEN){
        return DECODE_ERR_INPUT;
    } else if(ret1 == OGG_ERR_OVOPEN){
        return DECODE_ERR_FORMAT;
    }

    reader.printFileInfo();

    // open output
    FILE *fp_output = fopen(output, "wb");
	if ( !fp_output ) { 

        return DECODE_ERR_OUTPUT;
	}

	// write dummy_header header
    writeDummyWavHeader(fp_output);


// endless loop
// exit the loop, when read all the ov_data
    bool is_err = false;
    int isFirst = 1; // show debug message at once 
    while(1) 
    {

        int ret2 = reader.read();
        if(ret2 == OGG_READER_END){
            break;
        }

        if(isFirst){
            isFirst = 0;
            reader.printOvInfo();
        }

        // write pcm
        char *data = reader.getBuffer();
		int num_write = fwrite(data, 1, OGG_READER_BUFF_SIZE, fp_output);
		if(num_write != OGG_READER_BUFF_SIZE) {
					 is_err = true;
					//break;
		}

    } //  while


// close
    reader.close();
    fclose(fp_output);

	// write wav header
    overwriteWavHeader(output, OGG_READER_CHANNELS_STEREO, 
    WAVH_BITSPERSAMPLE16, 
    OGG_READER_SAMPLINGRATE);

    if(is_err){
        return DECODE_ERR_WRITE;
    }

    return DECODE_SUCCESS;
}


/**
 * addExtWav
 */
std::string addExtWav( std::string file)
{
    std::string wav = file + std::string(".wav");
    return wav;
}
