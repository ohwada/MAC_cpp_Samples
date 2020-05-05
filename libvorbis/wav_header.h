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
#define WAVH_SAMPLINGRATE_DEFAULT 44100

int readWavHeader(FILE* fp, int *channels, int* bit, int *size, int* samplingrate);

int convInt(unsigned char* header, int start);

short convShort(unsigned char* header, int start);

bool writeDummyWavHeader(FILE *fp);
 
bool overwriteWavHeader(char *filename, int channels, int samplingrate);

bool writeWavHeaderFp(FILE *fp, int channels, int samplingrate, int filesize);

int getFileSize(char *filename);

#endif /* WAVHEADER_H */
