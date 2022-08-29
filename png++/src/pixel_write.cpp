/**
 * pixel_write.cpp
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include <string> 

#include "png_util.h"
#include "pixels.h"

using namespace std;

/**
 * pixel_write
 */
bool pixel_write(int size,  int scale,  string output)
{

    // image size
    int width = size * scale;
    int height = size * scale;

    // create Pixel
    unsigned char *data = 
        createColorMatrixPixel32(size, scale);

    // save image
    bool ret = saveImage(output, data, width, height);
    if(!ret){
            cerr << "saved Image Faild: " << output << endl;
            return false;
    }


	return true;
}



/**
 * main
 */
int main(int argc, char** argv)
{

    // 512 x 512
    int size = 2;
    int scale = 256;

    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] "  << endl;
    }

    // output file name
    string output = string("pixel_") + to_string(size) + string("_")  + to_string(scale) + string(".png");

    cout << output << endl;

    if( !pixel_write(size,  scale,  output) ) {
            return EXIT_FAILURE;
    }

        cout << "saved: " << output << endl;

	return EXIT_SUCCESS;
}
