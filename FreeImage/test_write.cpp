/**
 * Freeimage Sample
 * 2020-02-01 K.OHWADA
 */


// writable extensiton
// png, tif, bmp
//  NOT writable : jpg, gif


#include <string> 
#include<iostream>

#include "freeimage_util.hpp"

#include "pixels.h"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "FreeImage : write" << endl;


    // 512 x 512
    int size = 2;
    int scale = 256;

    string ext = "png";

    if (argc > 3) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
        ext = argv[3];
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] [outputFileExtension]"  << endl;
    }

    // image size
    int width = size * scale;
    int height = size * scale;

    // output file name
    const char DOT = '.';
    const char UNDERBAR = '_';

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + DOT + ext;


    // create Pixel
    char *data = 
        createColorMatrixPixel(size, scale);

    // save Image
    bool ret = fi_saveImage(output, data, width, height);
    if(!ret) {
                cerr << "SaveImage Failed: " << output << endl;
                return EXIT_FAILURE;
    }

    cout << "saved Image: " << output << endl;

	return EXIT_SUCCESS;
}

