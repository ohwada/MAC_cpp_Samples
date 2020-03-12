/**
 * Freeimage Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>
#include<FreeImage.h>


char* fi_loadImage(std::string filename, int &width, int &height);

bool fi_saveImage(std::string fileName, char *data, int width, int height);

FIBITMAP* fi_loadBitmap(std::string filename);

bool fi_saveBitmap(std::string filename, FIBITMAP* bitmap);

char* fi_convertTo32Bits(FIBITMAP* bitmap, int &width, int &height);

FIBITMAP * fi_convertFromRawBits(char *data, int width, int height);

char* reverseAndSwap(char *src, int width, int height);
