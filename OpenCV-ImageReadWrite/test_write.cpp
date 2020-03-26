/**
 * OpenCV Sample
 * 2020-02-01 K.OHWADA
 */


// writable extensiton
// png, jpg, tif, bmp
//  NOT writable : gif


#include <string> 
#include<iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "pixels.h"

using namespace std;
using namespace cv;


/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height)
{

    //BGR
    Mat m(height, width, CV_8UC4, data);

    // RGBA
    Mat color;
    cvtColor(m, color, COLOR_BGR2RGBA); 

    // save image
    return imwrite(output, color);

}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "OpenCV : write" << endl;


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
        createColorMatrixPixel32(size, scale);

    // save Image
    bool ret = saveImage(output, data, width, height);
    if(!ret) {
                cerr << "saveImage Failed: " << output << endl;
                return EXIT_FAILURE;
    }

    cout << "saved Image: " << output << endl;

	return EXIT_SUCCESS;
}

