/**
 * libvorbis Sample
 * 2020-03-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>  
#include <sys/stat.h>

void writeDummyWavHeader(FILE *fp);
 
void writeWavHeader(char *filename, int channels, int sampling_rate);

int getFileSize(char *filename);

