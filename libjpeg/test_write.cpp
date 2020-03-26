/**
 * libjpeg Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include "jpeg.h"

#include "pixels.h"

using namespace std;


/**
 * saveImage
 */
bool saveImage(string output, char *data, int width, int height, int quality)
{

    try
    {
        using namespace marengo::jpeg;

        // create image
        Image img( width, height );

        for (int y = 0; y < height; ++y )
        {
            for (int x = 0; x < width; ++x )
            {

                int index = 4*width*y + 4*x;

                    // order R, G, B.
                    vector<uint8_t> vec(3);
                    vec[0] = data[index+0]; // R
                    vec[1] = data[index+1]; // G
                    vec[2] = data[index+2]; // B
                    img.setPixel( x, y, vec );

            } // x
        } // y

        img.save(output, quality);

    }
    catch( const std::exception& e )
    {
        cerr << "Faild: " << e.what() << endl;
        return false;
    }

    return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    const int JPEG_QUALITY = 90;

    cout << "libjpeg : write" << endl;


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

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + ".jpg";


    // create Pixel
    char *data = 
        createColorMatrixPixel32(size, scale);


    // save image
    bool ret = saveImage(output, data, width,height, JPEG_QUALITY);

    if(ret){    
            cout << "saved Image : " << output << endl;
    } else {
            cerr << "save Image Faild: " << output << endl;
            return EXIT_FAILURE;
    }


	return EXIT_SUCCESS;
}

