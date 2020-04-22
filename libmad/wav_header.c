/**
 * libmad Sample
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


/**
 * writeDummyWavHeader
 */
void writeDummyWavHeader(FILE *fp) 
{
	char dummy_header[WAV_HEADER_SIZE] = "";	
    fwrite(dummy_header, 1, WAV_HEADER_SIZE, fp);
}


/**
 * writeHeader
 */
void writeWavHeader(char *filename, int channels, int sampling_rate)
{
    int filesize = getFileSize(filename);

    int wavsize = filesize - 8;
    int datasize = filesize - WAV_HEADER_SIZE;

	// setup header 
	wav_header wavh;
	wavh.RIFF = 0x46464952;						// "RIFF"
	wavh.WAVE =  0x45564157;					// "WAVE"
	wavh.fmt = 0x20746D66;						// "'fmt"
    wavh.ov_data = 0x61746164;						// "ov_data"
	wavh.wFormatTag = 1; // PCM
	wavh.wBitsPerSample = 16;
	wavh.wFormatLength = 16;
	
    wavh.nChannels = channels; // maybe stereo
    wavh.nSamplesPerSec = sampling_rate; // may be 44100
	wavh.size = wavsize;	// total size of wav file
	wavh.ov_datasize = datasize; // size of ov_data

	wavh.nBlockAlign = (short)(wavh.wBitsPerSample / 8 * wavh.nChannels);
	wavh.nAvgBytesPerSec = wavh.nSamplesPerSec * wavh.nBlockAlign;

	// write wav header
	FILE *fp = fopen(filename, "rb+");
	fwrite(&wavh, 1, WAV_HEADER_SIZE, fp);
	fclose(fp);
}


/**
 * getFileSize
 */
int getFileSize(char *filename)
{
	struct stat file_stat;
	FILE *fp = fopen(filename, "rb");
    int iflde = fileno(fp);
	fstat(iflde, &file_stat);
	fclose(fp);
    int size = (int)file_stat.st_size;
    return size;
}
