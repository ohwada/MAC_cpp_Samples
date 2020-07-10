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
 * createColorMatrixPixel24
 */
char* createColorMatrixPixel24(int size, int scale)
{
    return createColorMatrixPixel(size, scale, false);
}


/**
 * createColorMatrixPixel32
 */
char* createColorMatrixPixel32(int size, int scale)
{
    return createColorMatrixPixel(size, scale, true);
}


/**
 * createColorMatrixPixel
 */
char* createColorMatrixPixel(int size, int scale, bool is_alpha)
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

    return scalePixel(matrix, size, size, scale, is_alpha);
}


/**
 * scalePixel
 */
char* scalePixel(char *src, int src_width, int src_height, int scale, bool is_alpha)
{

const int SRC_BYTES = 3;
    int src_pitch = SRC_BYTES * src_width;

    int buf_width = scale * src_width;
    int buf_height = scale * src_height;

    int buf_bytes = is_alpha ? 4 : 3;
    int buf_pitch = buf_bytes * buf_width;
    int bufsize = buf_bytes *  buf_width * buf_height;

    char* buf = new char[bufsize];

// All White
    for(int k=0; k<bufsize; k++){
        buf[k] = (char)255;
    }

int x_step = buf_bytes * scale;
int y_step = buf_pitch * scale;

    for(int y = 0;  y<src_height; y++)
    {
        for(int x = 0; x<src_width; x++)
        {
                int src_index = src_pitch * y + SRC_BYTES * x;
                int  index_xy = y_step  * y + x_step * x;

            char r =  src[src_index + 0]; // R
            char g =  src[src_index + 1]; // G
            char b =  src[src_index + 2]; // B
            char a = (char)255; // A

    for(int j=0; j<scale; j++)
    {
        for(int i=0; i<scale; i++)
        {
                    int buf_index = index_xy + buf_pitch * j +   buf_bytes * i;

                    buf[buf_index + 0] = r; // R
                    buf[buf_index + 1] = g; // G
                    buf[buf_index + 2] = b; // B
                    if(is_alpha){
                        buf[buf_index + 3] = a; // A
                    }
                } // for i
            } // for i 
        } // for x
    } // for y

    // dumpPixel(buf, bufsize, 4);

    return buf;

}


/*
 * createCheckerBoardPixel24
 */
char* createCheckerBoardPixel24(int width, int height)  
{
    return createCheckerBoardPixel(width, height, false);
}

/*
 * createCheckerBoardPixel32
 */
char* createCheckerBoardPixel32(int width, int height)
{  
    return createCheckerBoardPixel(width, height, true);
}

/*
 * createCheckerBoardPixel
 */
char* createCheckerBoardPixel(int width, int height, bool is_alpha)  
{ 

    int bytes = is_alpha ? 4 : 3;

    int pitch = bytes * width;

	int bufsize = bytes * width * height;

	char* buf = new char[bufsize];

  for (int y=0; y<height; y++) {  
    for (int x=0; x<width; x++) { 
// White when the height or width is even 
        int flag = (((x&0x01)==0)^((y&0x01)==0));
        char c = (char)( 255 * flag );
        int index = (pitch * y) + ( bytes * x); 
        buf[index + 0] = c; // R
        buf[index + 1] = c; // G
        buf[index + 2] = c; // B
        if(is_alpha){
            buf[index + 3] = (char)255;  // A
        } 
    }  
  }

    return buf;  
}


/*
 * dumpPixel
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