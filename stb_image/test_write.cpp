/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */

// supprt format : png, bmp, tga
// NOT supprt : jpg

#include <string> 
#include<iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "pixels.h"

using namespace std;


/**
 * saveImage
 */
bool saveImage(string output , char *data, int width, int height, string ext)
{

    const int COMP = 4;
    const int JPEG_QUALITY = 100;
    const char * filename = (const char * )output.c_str();

    int out;

    if(ext == "png"){
        int stride_in_bytes = 4*width;
        out = stbi_write_png(filename, width, height, COMP, data, stride_in_bytes);
    }else if(ext == "bmp"){
        out = stbi_write_bmp(filename, width, height, COMP, data);
    }else if(ext == "tga"){
        out = stbi_write_tga(filename,  width, height, COMP, data);
    }else if(ext == "jpg"){
        out = stbi_write_jpg(filename,  width, height, COMP, data,   JPEG_QUALITY);
    }else{
        cout << "NOT support extension: "<< ext << endl;
        return false;
    }

    bool ret = (out>0)? true: false;

    return ret;
}

/**
 * createOutputFileName
 */
string createOutputFileName(int size, int scale, string ext)
{

    const char UNDERBAR = '_';
    const char DOT = '.';

    string output = "test_" + to_string(size) + UNDERBAR + to_string(scale) + DOT + ext;

    return output;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "stb : write" << endl;


    // 512 x 512
    int size = 2;
    int scale = 256;
string ext = "png";

    if (argc > 3) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
        ext = argv[3];
    }else if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] [output extension] "  << endl;
    }

    // image size
    int width = size * scale;
    int height = size * scale;

    // output file name
    string output = createOutputFileName(size, scale, ext);

    // create Pixel
    char *data = 
        createColorMatrixPixel32(size, scale);


    // save image
    bool ret = saveImage(output, data, width, height, ext);

	if(!ret){
        cerr << "save Image Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved Image : " << output << endl;


	return EXIT_SUCCESS;
}

