/**
 * copy.c
 * 2022-06-01 K.OHWADA
 */

#include<stdio.h>
#include <string.h> 
#include "png_util.h"
#include "c_parse_filename.h"


/**
 * file_copy
 */
bool file_copy(char *input, char *output)
{
  BITMAPDATA_t bitmap;

  if( !pngFileReadDecode(&bitmap, input) ){
    printf("pngFileReadDecode error\n");
    return false;
  }


  if( !pngFileEncodeWrite(&bitmap, output) ){
        printf("pngFileEncodeWrite error\n");
        return false;
    }

    freeBitmapData(&bitmap);

    return true;
}


/**
 * main
 */
int main(int argc, char **argv)
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
    strcat(output, "_copy.png");
    printf("%s \n",  output);

    if( !file_copy(input, output) ) {
        return EXIT_FAILURE;
    }

    printf("saved: %s \n", output);

        return EXIT_SUCCESS;
}


// saved: uparrow_copy.png 

