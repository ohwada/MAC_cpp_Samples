/**
 * wavheader
 * 2020-03-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>  
#include <sys/stat.h>

bool writeDummyWavHeader(FILE *fp);
 
bool overwriteWavHeader(char *filename, int channels, int sampling_rate);

bool writeWavHeaderFp(FILE *fp, int channels, int sampling_rate, int filesize);

int getFileSize(char *filename);

