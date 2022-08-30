/**
 *  gray.c
 * 2022-06-01 K.OHWADA
 */

  // convert to Grayscale
// reference : https://daeudaeu.com/libpng/#i-3

#include <stdio.h> 
#include "png_util.h"
#include "c_parse_filename.h"


/**
 *  conv_gray
 */
void conv_gray( unsigned char *data,
    int width,
    int height,
    int ch)
{
const unsigned char MAX = 255;

 bool has_alpha = (ch==4)? true : false;

  for(int j = 0; j < height; j++) {
    for(int i = 0; i < width; i++)
    {
        int index = ch * (i + j * width);
        unsigned char ave = ( data[index] + data[index+1] + data[index+2] )/3;

        data[index]  = ave;
        data[index+1] = ave;
        data[index+2]  = ave;
        if( has_alpha){
            data[index+3]  = MAX;
        }
    } // for i
  } // for j
}


/**
 *  gray_file
 */
bool gray_file(char *input, char *output)
{

BITMAPDATA_t bitmap;

  if( !pngFileReadDecode(&bitmap, input) ){
    printf("pngFileReadDecode error\n");
    return false;
  }

int width = bitmap.width;
int height = bitmap.height;
int ch  = bitmap.ch;

  printf("width = %d \n",  width);
  printf("height = %d \n",  height);
  printf("ch = %d \n", ch);


    conv_gray( bitmap.data, width, height, ch);

  if( !pngFileEncodeWrite(&bitmap, output) ){
    printf("pngFileEncodeWrite error\n");
    freeBitmapData(&bitmap);
    return false;
  }

  freeBitmapData(&bitmap);

  return true;
}


/**
 *  main
 */
int main(int argc, char *argv[])
{
    const int BUFSIZE = 256;
    char output[BUFSIZE];

    char* input = "images/uparrow.png";

    if(argc == 2){
        input = argv[1];
    } else {
        printf("Usage %s <pngFile> \n",  argv[0]);
    }

    printf("%s \n",  input);

    char* fname = get_filename_without_ext(input);
    strcpy(output, fname);
    strcat(output, "_gray.png");
    printf("%s \n",  output);

    if( !gray_file(input, output) ) {
            return EXIT_FAILURE;
    }

    printf("saved: %s \n", output);

    return EXIT_SUCCESS;
}
