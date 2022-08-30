/**
 * pixel_write.c
 * 2022-06-01 K.OHWADA
 */


#include<stdio.h>
#include<stdlib.h>
#include <string.h> 
#include "png_util.h"
#include "pixels.h"


/**
 * pixel_write
 */
bool pixel_write( int size, int scale, char *output)
{
// image size
    int width = size * scale;
    int height = size * scale;

// create Pixel
    char *data = 
        createColorMatrixPixel32(size, scale);

  BITMAPDATA_t bitmap;
    bitmap.data = (unsigned char *)data;
    bitmap.width = width;
    bitmap.height = height;
    bitmap.ch = 4;

    // save image
  if( !pngFileEncodeWrite(&bitmap, output) ){
    printf("pngFileEncodeWrite error\n");
    freeBitmapData(&bitmap);
    return false;
  }

  freeBitmapData(&bitmap);

	return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{
    const int BUFSIZE = 256;
  char output[BUFSIZE];

    // 512 x 512
    int size = 2;
    int scale = 256;

    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        printf("Usage: %s [size] [scale] \n", argv[0] );
    }

    // output file name
    snprintf(output, BUFSIZE-1, "pixel_%d_%d.png", size, scale);

if( !pixel_write(size, scale, output) ){
            return EXIT_FAILURE;
}
    printf("saved: %s \n", output);

    return EXIT_SUCCESS;
}

