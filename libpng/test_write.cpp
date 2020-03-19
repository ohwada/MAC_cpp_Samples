/**
 * libpng Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>
#include <ostream>

#include <png.hpp>

#include "pixels.h"

using namespace std;


/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height)
{
    try
    {

        png::image< png::rgba_pixel > image(width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {

                    int index = 4*width*y + 4*x;
                    char r = data[index +0];
                    char g = data[index +1];
                    char b = data[index +2];
                    char a = data[index +3];
                    png::rgba_pixel pix(r, g, b, a);
                    image.set_pixel(x, y, pix);

            } // x
        }// y

        image.write(output);

    }
    catch (std::exception const& error)
    {
        cerr << "save image Faild: " << error.what() << endl;
        return false;
    }

    return true;
}


/**
 * createOutputFileName
 */
string createOutputFileName(int size, int scale)
{

    const char DOT = '.';
    const char UNDERBAR = '_';
    const string EXT = "png";

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + DOT + EXT;

    return output;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "libpng : write" << endl;


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
    string output = createOutputFileName(size, scale);

    // create Pixel
    char *data = 
        createColorMatrixPixel(size, scale);

    // save image
    bool ret = saveImage(output, data, width, height);
    if(ret){
            cout << "saved Image: " << output << endl;
    }else{
            cerr << "saved Image Faild: " << output << endl;
            return EXIT_FAILURE;
    }


	return EXIT_SUCCESS;
}

