/*
 * Image Pixel Sample
 * 2020-02-01 K.OHWADA
 */

char* createColorMatrixPixel24(int size, int scale);

char* createColorMatrixPixel32(int size, int scale);

char* createColorMatrixPixel(int size, int scale, bool is_alpha);

char* scalePixel(char *src, int width, int height, int scale, bool is_alpha);

char* createCheckerBoardPixel24(int width, int height) ;

char* createCheckerBoardPixel32(int width, int height) ;

char* createCheckerBoardPixel(int width, int height, bool is_alpha);
 
void dumpPixel(char* pixel, int size,  int byte_per_pixel);


