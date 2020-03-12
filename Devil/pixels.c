/*
 * Image Sample
 * 2020-02-01 K.OHWADA
 */

#include <stdlib.h> 
#include <stdio.h>

#include "pixels.h"


/*
 * Color matrix Pixel
 */
char COLOR_MATRIX_PIXEL_2x2[] = 
{  
    (char)255,   (char)0,   (char)0, // Red
    (char)0, (char)255,   (char)0, // Lime
    (char)0,   (char)0, (char)255, // Blue
    (char)255, (char)255,   (char)0  // Yellow
};


char COLOR_MATRIX_PIXEL_3x3[] = 
{  
    (char)255,   (char)0,   (char)0, // Red
    (char)0, (char)255,   (char)0, // Lime
    (char)0,   (char)0, (char)255, // Blue
    (char)255, (char)0, (char)255,  // Fuchsia
    (char)0,   (char)0,   (char)0,  // Black
    (char)255, (char)255,   (char)0,  // Yellow
    (char)0,   (char)0, (char)128, // Navy
    (char)0, (char)128,   (char)0, // Green
    (char)128,   (char)0,   (char)0 // Maroon
};


char COLOR_MATRIX_PIXEL_4x4[] = 
{ 
    (char)255,   (char)0,   (char)0, // Red
    (char)0, (char)255,   (char)0, // Lime
    (char)255,   (char)255,   (char)255,  // White
    (char)0,   (char)0, (char)255, // Blue
    (char)0, (char)128,   (char)0, // Green
    (char)192,   (char)192, (char)192, // Silver
    (char)0,   (char)255, (char)255, // Aqua
    (char)128,   (char)0, (char)128, // Purple
    (char)128,   (char)0,   (char)0, // Maroon
    (char)128,   (char)128, (char)0, // Olive 
    (char)128,   (char)128, (char)128, // Gray
    (char)0,   (char)0, (char)128, // Navy
    (char)0,   (char)128, (char)128, // Teal
    (char)255, (char)0, (char)255,  // Fuchsia
    (char)0,   (char)0,   (char)0,  // Black
    (char)255, (char)255,   (char)0 // Yellow
};


/**
 * createColorMatrixPixe
 */
char* createColorMatrixPixel(int size, int scale)
{

    char *matrix = COLOR_MATRIX_PIXEL_2x2;

    switch(size){
        case 3:
            matrix = COLOR_MATRIX_PIXEL_3x3;
            break;
        case 4:
            matrix = COLOR_MATRIX_PIXEL_4x4;
            break;
    }

    return scalePixel(matrix, size, size, scale);
}


/**
 * scalePixel
 */
char* scalePixel(char *src, int src_width, int src_height, int scale)
{

    int src_pitch = 3 * src_width;

    int buf_width = scale * src_width;
    int buf_height = scale * src_height;
    int buf_pitch = 4 * buf_width;

    int bufsize = 4 *  buf_width * buf_height;

    char* buf = new char[bufsize];

// All White
    for(int k=0; k<bufsize; k++){
        buf[k] = (char)255;
    }

int x_step = 4 * scale;
int y_step = buf_pitch * scale;

    for(int y = 0;  y<src_height; y++)
    {
        for(int x = 0; x<src_width; x++)
        {
                int src_index = src_pitch * y + 3 * x;
                int  index_xy = y_step  * y + x_step * x;

            char r =  src[src_index + 0]; // R
            char g =  src[src_index + 1]; // G
            char b =  src[src_index + 2]; // B

    for(int j=0; j<scale; j++)
    {
        for(int i=0; i<scale; i++)
        {
                    int buf_index = index_xy + buf_pitch * j +   4 * i;

                    buf[buf_index + 0] = r; // R
                    buf[buf_index + 1] = g; // G
                    buf[buf_index + 2] = b; // B
                    buf[buf_index + 3] = (char)255; // A

                } // for i
            } // for i 
        } // for x
    } // for y

    // dumpPixel(buf, bufsize, 4);

    return buf;

}



/*
 * createCheckerBoardPixel
 */
char* createCheckerBoardPixel(int width, int height)  
{ 

    int pitch = 4 * width;

	int bufsize = 4 * width * height;

	char* buf = new char[bufsize];

  for (int y=0; y<height; y++) {  
    for (int x=0; x<width; x++) { 
// White when the height or width is even 
        int flag = (((x&0x01)==0)^((y&0x01)==0));
        char c = (char)( 255 * flag );
        int index = (pitch * y) + (4 * x); 
        buf[index + 0] = c; // R
        buf[index + 1] = c; // G
        buf[index + 2] = c; // B
        buf[index + 3] = (char)255;  // A 
    }  
  }

    return buf;  
}


/*
 * dumpPixe
 */
void dumpPixel(char* pixel, int size, int byte_per_pixel)
{

    for(int i=0; i<size; i++){
            int byte = (0xff&pixel[i]);
            printf("%d, ", byte);
            if( (i%byte_per_pixel) == 3 ){
                printf("\n");
            }
    }
    printf("\n");
}