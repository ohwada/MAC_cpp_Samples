/**
 * png_square.h
 * 2022-06-01 K.OHWADA
 */

#include<stdio.h>
#include <string.h> 
#include "png_util.h"

// prototype
unsigned int min(unsigned int a, unsigned int b);
unsigned int max(unsigned int a, unsigned int b);
bool square( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char r, unsigned int g, unsigned char b, unsigned char a);
void bgcolor( int width, int height,
unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void create_image( int width, int height);
void create_image_bgcolor( int width, int height,
unsigned char r, unsigned char g,unsigned char b, unsigned char a);
bool save_image(char *filepath);


const unsigned char CMAX = 255;
const int CH = 4;

// global
unsigned char *image;

int img_width;
int img_height;


/**
 * min
 */
unsigned int min(unsigned int a, unsigned int b)
{
   return (a<b)?a:b;
}


/**
 * max
 */
unsigned int max(unsigned int a, unsigned int b)
{
   return (a>b)?a:b;
}


/**
 * square
 */
bool square( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char r, unsigned int g, unsigned char b, unsigned char a)
{
    int xmin = min(x1, x2);
    int xmax = max(x1, x2);
    int ymin = min(y1, y2);
    int ymax = max(y1, y2);

    if(xmax > img_width){
        printf("xmax(%d) must be samller than width(%d) \n", xmax, img_width);
        return false;
    }

   if(ymax > img_height){
        printf("ymax(%d) must be samller than height(%d) \n", ymax, img_height);
        return false;
    }

    for(int j=ymin; j<=ymax; j++){
    for(int i=xmin; i<=xmax; i++){
        int index = j*CH*img_width + CH*i;
        image[index] = r;
        image[index+1] = g;
        image[index+2] = b;
        image[index +3] = a;
    } // for i
    } // for j

    return true;
}


/**
 * bgcolor
 */
void bgcolor( int width, int height,
unsigned char r, 
unsigned char g, 
unsigned char b, 
unsigned char a)
{
 for(int j=0; j<=height; j++){
    for(int i=0; i<=width; i++){
int index = j*CH*width + CH*i;
        image[index] = r;
       image[index+1] = g;
       image[index+2] = b;
       image[index +3] = a;
    } // for i
    } // for j
}


/**
 * create_image
 */
void create_image( int width, int height)
{
int num =  width * height * CH;
image = (unsigned char *)calloc(num, sizeof(unsigned char));
img_width = width;
img_height = height;
}


/**
 * create_image
 */
void create_image_bgcolor( int width, int height,
unsigned char r, 
unsigned char g, 
unsigned char b, 
unsigned char a)
{
    create_image( width, height);
    bgcolor(width, height, r, g, b, a);
}


/**
 *  save_image
 */
bool save_image(char *filepath)
{
    BITMAPDATA_t bitmap;

    bitmap.data = image;
    bitmap.width = img_width;
    bitmap.height = img_height;
    bitmap.ch = CH;

    // save image
  if( !pngFileEncodeWrite(&bitmap, filepath) ){
    printf("pngFileEncodeWrite error\n");
    return false;
  }
    return true;
}
