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


void Posterization(Image *img);


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : post" << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }


   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_post.bmp";


// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );

	if(!img){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
	}

    Posterization(img);

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
 * conv
 */
unsigned char conv(unsigned char v)
{
    if (v < 64)
    {
        return 0;
    }
    else if (v < 128)
    {
        return 85;
    }
    else if (v < 192)
    {
        return 170;
    }
    else
    {
        return 255;
    }
}


/**
 * Posterization
 */
void Posterization(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char gray;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            gray = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;
            img->data[index].r = img->data[index].g = img->data[index].b = conv(gray);
        }
    }
}
