/**
 * stb Sample
 * 2020-02-01 K.OHWADA
 */


// convert to gray scall 

#include <string> 
#include<iostream>

#include"parse_filename.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

// prototype
uint8_t* loadImage(string input, int *w, int *h);
bool saveImage(string output , uint8_t *data, int width, int height, string ext);
void convGrayScale(uint8_t *data, int width, int height);


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "stb : gray" << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];


    string fname = getFileNameWithoutExt(input);
    string ext = getFileNameExt(input);
    string output = fname +"_gray." + ext;

    int width;
    int height;

    uint8_t* data = loadImage(input, &width, &height);
    if(!data){
        cout << "load faild: " << input << endl;
        return EXIT_FAILURE;
    }   

    cout << "loaded: " << input << " (" << width << " x " << height << " )" << endl;

     convGrayScale(data, width, height);
 

    // save image
    bool ret = saveImage(output, data, width, height, ext);

	if(!ret){
        cerr << "save  Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved : " << output << endl;

	return EXIT_SUCCESS;
}


/**
 * loadImage
 */
uint8_t* loadImage(string input, int *w, int *h)
{

    char *filepath = (char *)input.c_str();

     int channels;
    int width ;
    int height ;

// read image
    uint8_t* pixels = (uint8_t*)stbi_load(filepath, &width, &height, &channels, 0);

    if(!pixels){
        return NULL;
    }

    int bufsize =  3*width*height;
    
    uint8_t *buf = new uint8_t(bufsize);

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            int src_index = channels*width*y + channels*x;
            int buf_index = 3*width*y + 3*x;

	        uint8_t r = pixels[src_index+0];
	        uint8_t g = pixels[src_index+1];
	        uint8_t b = pixels[src_index+2];

            buf[buf_index + 0] = r;
           buf[buf_index + 1] = g;
           buf[buf_index + 2] = b;

        } // x
    } // y

    *w = width;
    *h = height;

    return buf;
}


/**
 * saveImage
 */
bool saveImage(string output , uint8_t *data, int width, int height, string ext)
{

    const int COMP = 3;
    const int JPEG_QUALITY = 100;

    char * filepath = (char * )output.c_str();

    int out;

    if(ext == "png"){
        int stride_in_bytes = 3*width;
        out = stbi_write_png(filepath, width, height, COMP, data, stride_in_bytes);
    }else if(ext == "bmp"){
        out = stbi_write_bmp(filepath, width, height, COMP, data);
    }else if(ext == "tga"){
        out = stbi_write_tga(filepath,  width, height, COMP, data);
    }else if(ext == "jpg"){
        out = stbi_write_jpg(filepath,  width, height, COMP, data, JPEG_QUALITY );
    }else{
        cout << "NOT support extension: "<< ext << endl;
        return false;
    }

    bool ret = (out>0)? true: false;

    return ret;
}


/**
 *  convGrayScale
 */
void convGrayScale(uint8_t *data, int width, int height)
{

    for (int  y= 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = 3*width*y + 3*x;

                 uint8_t r = data[index+0];
                 uint8_t g = data[index+1];
                 uint8_t b = data[index+2];

// https://www.tutorialspoint.com/dip/grayscale_to_rgb_conversion.htm
                uint8_t gray  = ( 0.30 * r + 0.59 * g + 0.11 * b ) ;

            data[index+0] = gray;
            data[index+1] = gray;
            data[index+2] = gray;

        } // for x
    }// for y


}
