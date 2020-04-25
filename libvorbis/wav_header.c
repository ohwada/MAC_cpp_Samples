/**
 * wavheader
 * 2020-03-01 K.OHWADA
 */

// reference : https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM

#include "wav_header.h"


#define WAV_HEADER_SIZE 44


// wav header structure 
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
const short WAVH_WBITSPERSAMPLE = 16;
const short WAVH_WFORMATTAG_PCM = 1;

/**
 * writeDummyWavHeader
 */
bool writeDummyWavHeader(FILE *fp) 
{
	char dummy_header[WAV_HEADER_SIZE] = "";	
    int wsize = fwrite(dummy_header, 1, WAV_HEADER_SIZE, fp);
    bool ret = (wsize == WAV_HEADER_SIZE)? true: false;
    return ret;
}


/**
 * overwriteWavHeader
 */
bool overwriteWavHeader(char *filename, int channels, int sampling_rate)
{
    int filesize = getFileSize(filename);
    if(filesize==0){
        return false;
    }

	// write wav header
	FILE *fp = fopen(filename, "rb+");
    bool ret = writeWavHeaderFp(fp, channels, sampling_rate, filesize);
	fclose(fp);
    return ret;
}


/**
 * writeHeaderFp
 */
bool writeWavHeaderFp(FILE *fp, int channels, int sampling_rate, int filesize)
{

    int wavsize = filesize - 8;
    int datasize = filesize - WAV_HEADER_SIZE;
    short nBlockAlign = (short)(WAVH_WBITSPERSAMPLE / 8 * channels);
	int nAvgBytesPerSec = sampling_rate * nBlockAlign;

	// setup header 
	wav_header wavh;
	wavh.RIFF = WAVH_RIFF;
	wavh.WAVE =  WAVH_WAVE;
	wavh.fmt = WAVH_FMT;
    wavh.ov_data = WAVH_OV_DATA;
	wavh.wFormatTag = WAVH_WFORMATTAG_PCM;
	wavh.wFormatLength = WAVH_WFORMATLENGTH;
	wavh.wBitsPerSample = WAVH_WBITSPERSAMPLE;

    wavh.nChannels = channels; // maybe stereo
    wavh.nSamplesPerSec = sampling_rate; // may be 44100
	wavh.size = wavsize;	// total size of wav file
	wavh.ov_datasize = datasize; // size of ov_data

    wavh.nBlockAlign = nBlockAlign;
	wavh.nAvgBytesPerSec = nAvgBytesPerSec;

	// write wav header
	int wsize = fwrite(&wavh, 1, WAV_HEADER_SIZE, fp);
    bool ret = (wsize == WAV_HEADER_SIZE)? true: false;
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
