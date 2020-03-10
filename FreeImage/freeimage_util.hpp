/**
 * Freeimage Sample
 * 2020-01-01 K.OHWADA
 */


#include <string> 
#include<iostream>
#include<FreeImage.h>


char* loadImage(std::string filename, int &width, int &height);

bool saveImage(std::string fileName, char *data, int width, int height);

FIBITMAP* loadBitmap(std::string filename);

bool saveBitmap(std::string filename, FIBITMAP* bitmap);

char* convertTo32Bits(FIBITMAP* bitmap, int &width, int &height);

FIBITMAP * convertFromRawBits(char *data, int width, int height);

char* reverseAndSwap(char *src, int width, int height);
