/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include "bmp.h"

#include "image.h"

#include "pixels.h"

using namespace std;


/**
 * createImage
 */
image_t* createImage(char *data, int width, int height, bool is_alpha)
{
    uint8_t type = is_alpha ? COLOR_TYPE_RGBA : COLOR_TYPE_RGB;

    image_t * img = allocate_image(width, height, type);

    if(!img){
        return NULL;
    }


	for(int y=0; y<height; y++){
		for(int x=0; x<width; x++){
            int src_index = 3*width*y + 3*x;
            char r = data[src_index + 0]; // R
			char g = data[src_index + 1]; // G
			char b = data[src_index + 2]; // B
            char a = (char)255; // A
            img->map[y][x].c.r = r; // R
			img->map[y][x].c.g = g; // G
			img->map[y][x].c.b = b; // B
            if(is_alpha){
			    img->map[y][x].c.a = a; // A
            }

		} // x
	} // y

    return img;
}


/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height, bool is_alpha)
{

    // create image
    image_t  *img = createImage(data, width, height, is_alpha);
    if(!img){
        return false;
    }

    // write image
    int COMPRESS = 0;
    result_t ret = write_bmp_file((char *)output.c_str(), img, COMPRESS );
	if(ret != SUCCESS){
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
    int alpha = 0;

    if (argc > 3) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
        alpha = atoi(argv[3]);
    } else if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] [alpha]  "  << endl;
    }


    // image size
    int width = size * scale;
    int height = size * scale;

    bool is_alpha = (alpha == 1)? true: false;
    string str_bits = is_alpha? "b32" : "b24";

    // output file name
    const char UNDERBAR = '_';

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + UNDERBAR + str_bits + ".bmp";

    // create Pixel
    char *data = 
        createColorMatrixPixel24(size, scale);

    // save image
    bool ret = saveImage(output, data, width, height, is_alpha );

	if(!ret){
        cerr << "save Image Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved Image : " << output << endl;


	return EXIT_SUCCESS;
}

