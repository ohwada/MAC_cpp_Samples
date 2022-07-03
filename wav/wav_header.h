#pragma once
/**
 * wavheader
 * 2020-03-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>  
#include <sys/stat.h>

#ifndef __WAVHEADER_H__
#define __WAVHEADER_H__

#define WAVH_HEADER_SIZE 44
#define WAVH_CHANNELS_MONO 1
#define WAVH_CHANNELS_STEREO 2
#define WAVH_SAMPLINGRATE_CD 44100
#define  WAVH_BITSPERSAMPLE8 8
#define  WAVH_BITSPERSAMPLE16 16

// prototype
int readWavHeader(FILE* fp, int *channels, int* bits, int *size, int* samplingrate);
int convInt(unsigned char* header, int start);
short convShort(unsigned char* header, int start);
bool writeDummyWavHeader(FILE *fp);
bool overwriteWavHeader(char *filename, int channels, int bits, int samplingrate);
bool writeWavHeaderFp(FILE *fp, int channels, int bits, int samplingrate, int filesize);
int getFileSize(char *filename);


/**
 * wav header structure 
 */
typedef struct tag_wav_header {	
		int RIFF;                // 'R','I','F','F'                
		int size;                   // size of wave file from here on
		int WAVE;             // 'W','A','V','E'
		int fmt;			 //'f','m','t',' '
		int   wFormatLength;          // The length of the TAG format    
		short    wFormatTag;             // should be 1 for PCM type ov_data  
		short    nChannels;              // should be 1 for MONO type ov_data
		int   nSamplesPerSec;         // should be 11025, 22050, 44100  
		int   nAvgBytesPerSec;        // Average Data Rate              
		short    nBlockAlign;            // 1 for 8 bit ov_data, 2 for 16 bit
		short    wBitsPerSample;         // 8 for 8 bit ov_data, 16 for 16 bit
		int ov_data;                // 'd','a','t','a'                        
		int   ov_datasize;               // size of ov_data from here on              
} wav_header ;

const int WAVH_RIFF = 0x46464952; // "RIFF"
const int 	WAVH_WAVE =  0x45564157; // "WAVE"
const int WAVH_FMT = 0x20746D66; // "'fmt"
const int WAVH_OV_DATA = 0x61746164;	 // "ov_data"
const int WAVH_WFORMATLENGTH = 16;
const short WAVH_WFORMATTAG_PCM = 1;


/**
 * readWavHeader
 */
int readWavHeader(FILE* fp, int *channels, int* bits, int *size, int* samplingrate)
{

	unsigned char header[WAVH_HEADER_SIZE];	

    // read header
	int rsize = fread(header, 1, WAVH_HEADER_SIZE, fp);
	if(rsize != WAVH_HEADER_SIZE){
		return 1;
	}

	int riff = convInt(header, 0);
	if(riff != WAVH_RIFF){
		printf("NOT match riff \n");
		return 2;
	}

	int dataSize = convInt(header, 4);
	//printf("dataSize: %d \n", dataSize);

	int wave = convInt(header, 8);
	if(wave != WAVH_WAVE){
		printf("NOT match wave \n");
		return 3;
	}



	int fmt = convInt(header, 12);
	if(fmt != WAVH_FMT){
		printf("NOT match fmt \n");
		return 4;
	}

    int wFormatLength = convInt(header, 16);
	//printf("wFormatLength: %d \n", wFormatLength);

    short pcm = convShort(header, 20);
	if(pcm != WAVH_WFORMATTAG_PCM){
			return 5;
	}

	short wavchannels = (int)convShort(header, 22);

	int samplesPerSec = convInt(header, 24);

    int byteParSec = convInt(header, 28);
	// printf("byteParSec: %d \n", byteParSec);

    short blockAlign = (int)convShort(header, 32);
	// printf("blockAlign: %d \n", blockAlign);

    short bitsParSample = (int)convShort(header, 34);

    int ov_data = convInt(header, 36);
    if(ov_data != WAVH_OV_DATA){
		printf("NOT match data \n");
	    return 6;
    }

    int ov_datasize = convInt(header, 40);

		*channels = (int)wavchannels;
		*bits = (int)bitsParSample;
		*samplingrate = samplesPerSec;
		*size = ov_datasize;

	return 0;
}


/**
 * convInt
 */
int convInt(unsigned char* header, int start)
{
	int ret = (header[start+3] << 24) | (header[start+2] << 16) | (header[start+1] << 8) | (header[start+0]);
	return ret;
}


/**
 * convShort
 */
short convShort(unsigned char* header, int start)
{
	int ret = (header[start+1] << 8) | (header[start+0]);
	return ret;
}


/**
 * writeDummyWavHeader
 */
bool writeDummyWavHeader(FILE *fp) 
{
	char dummy_header[WAVH_HEADER_SIZE] = "";	
    int wsize = fwrite(dummy_header, 1, WAVH_HEADER_SIZE, fp);
    bool ret = (wsize == WAVH_HEADER_SIZE)? true: false;
    return ret;
}


/**
 * overwriteWavHeader
 */
bool overwriteWavHeader(char *filename, int channels, int bits, int samplingrate)
{
    int filesize = getFileSize(filename);
    if(filesize==0){
        return false;
    }

	// write wav header
	FILE *fp = fopen(filename, "rb+");
    bool ret = writeWavHeaderFp(fp, channels, bits, samplingrate, filesize);
	fclose(fp);
    return ret;
}


/**
 * writeHeaderFp
 */
bool writeWavHeaderFp(FILE *fp, int channels, int bits, int samplingrate, int filesize)
{

    int wavsize = filesize - 8;
    int datasize = filesize - WAVH_HEADER_SIZE;
    short nBlockAlign = (short)(bits / 8 * channels);
	int nAvgBytesPerSec = samplingrate * nBlockAlign;

	// setup header 
	wav_header wavh;
	wavh.RIFF = WAVH_RIFF;
	wavh.WAVE =  WAVH_WAVE;
	wavh.fmt = WAVH_FMT;
    wavh.ov_data = WAVH_OV_DATA;
	wavh.wFormatTag = WAVH_WFORMATTAG_PCM;
	wavh.wFormatLength = WAVH_WFORMATLENGTH;
	wavh.wBitsPerSample = bits;

    wavh.nChannels = channels; // maybe stereo
    wavh.nSamplesPerSec = samplingrate; // may be 44100
	wavh.size = wavsize;	// total size of wav file
	wavh.ov_datasize = datasize; // size of ov_data

    wavh.nBlockAlign = nBlockAlign;
	wavh.nAvgBytesPerSec = nAvgBytesPerSec;

	// write wav header
	int wsize = fwrite(&wavh, 1, WAVH_HEADER_SIZE, fp);
    bool ret = (wsize == WAVH_HEADER_SIZE)? true: false;
    return ret;
}


/**
 * getFileSize
 */
int getFileSize(char *filename)
{
	struct stat file_stat;
	FILE *fp = fopen(filename, "rb");
    if(!fp){
        return 0;
    }

    int iflde = fileno(fp);
	fstat(iflde, &file_stat);
	fclose(fp);
    int size = (int)file_stat.st_size;
    return size;
}

#endif /* WAVHEADER_H */
