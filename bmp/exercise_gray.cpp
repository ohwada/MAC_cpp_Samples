/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/kawasin73/todai-bmp
 */

#include <string> 
#include<iostream>

#include "bitmap.h"

#include"parse_filename.hpp"

using namespace std;

// prototype
void GrayScale(Image *img);


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : gray " << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_gray.bmp";


// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );

	if(!img){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    GrayScale(img);


	// write image
    int ret= Write_Bmp ((char *)output.c_str(), img );

	if(ret != 0){
        cerr << "save Image Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved Image : " << output << endl;

    Free_Image(img);

    return EXIT_SUCCESS;
}


/**
 *  GrayScale
 */
void GrayScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char color;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            color = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;
            img->data[index].r = img->data[index].g = img->data[index].b = color;
        } // for j
    }// for i
}
