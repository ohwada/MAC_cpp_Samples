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
char* loadImage(string input, int *w, int *h);
bool saveImage(string output , char *data, int width, int height, string ext);
void convGrayScale(char *data, int width, int height);


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

    char* data = loadImage(input, &width, &height);
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
char* loadImage(string input, int *w, int *h)
{

    char *filepath = (char *)input.c_str();

     int channels;
    int width ;
    int height ;

// read image
    char* pixels = (char*)stbi_load(filepath, &width, &height, &channels, 0);

    if(!pixels){
        return NULL;
    }

    int bufsize =  3*width*height;
    
    char *buf = new char(bufsize);

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            int src_index = channels*width*y + channels*x;
            int buf_index = 3*width*y + 3*x;

	        char r = pixels[src_index+0];
	        char g = pixels[src_index+1];
	        char b = pixels[src_index+2];

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
bool saveImage(string output , char *data, int width, int height, string ext)
{

    char * filepath = (char * )output.c_str();

    int out;

    if(ext == "png"){
        int stride_in_bytes = 3*width;
        out = stbi_write_png(filepath, width, height, 3, data, stride_in_bytes);
    }else if(ext == "bmp"){
        out = stbi_write_bmp(filepath, width, height, 3, data);
    }else if(ext == "tga"){
        out = stbi_write_tga(filepath,  width, height, 3, data);
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
void convGrayScale(char *data, int width, int height)
{

    for (int  y= 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = 3*width*y + 3*x;

                unsigned char r = data[index+0];
                unsigned char g = data[index+1];
                unsigned char b = data[index+2];

                unsigned char gray  = ( 0.299 * r + 0.587 * g + 0.114 * b ) ;

            data[index+0] = gray;
            data[index+1] = gray;
            data[index+2] = gray;

        } // for x
    }// for y


}
