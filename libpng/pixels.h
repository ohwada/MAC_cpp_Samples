/*
 * Image Pixel Sample
 * 2020-02-01 K.OHWADA
 */


char* createColorMatrixPixel(int size, int scale);

char* scalePixel(char *src, int width, int height, int scale);

char* createCheckerBoardPixel(int width, int height);
 
void dumpPixel(char* pixel, int size,  int byte_per_pixel);


