/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include "bitmap.h" 

#include "pixels.h"

using namespace std;


/**
 * createImage
 */
 Image* createImage(char *data, int width, int height)
{

    Image *img = Create_Image(width, height);
    if(!img){
        return NULL;
    }

	img->width = width;
	img->height = height;

    // 24 bit : no alpha
	for(int y=0; y<height; y++){
		for(int x=0; x<width; x++){
            int dst_index = width*y + x;
            int src_index = 3*width*y + 3*x;
			img->data[dst_index].r = data[src_index + 0];
			img->data[dst_index].g = data[src_index + 1];
			img->data[dst_index].b = data[src_index + 2];
		} // x
	} // y

    return img;
}


/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height)
{

    // create image
    Image *img = createImage(data, width, height);
    if(!img){
        return false;
    }

    // write image
    int ret= Write_Bmp ((char *)output.c_str(), img );
	if(ret != 0){
        return false;
    }

    return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "bmp : write" << endl;


    // 512 x 512
    int size = 2;
    int scale = 256;


    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] "  << endl;
    }


    // image size
    int width = size * scale;
    int height = size * scale;

    // output file name
    const char UNDERBAR = '_';

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + ".bmp";

    // create Pixel
    char *data = 
        createColorMatrixPixel24(size, scale);



    // save image
    bool ret = saveImage(output, data, width, height);

	if(!ret){
        cerr << "save Image Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved Image : " << output << endl;


	return EXIT_SUCCESS;
}

