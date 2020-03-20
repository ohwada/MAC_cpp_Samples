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


void ThermoScale(Image *img);

/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : thermo " << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }


   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_thermo.bmp";


// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );

	if(!img){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    ThermoScale(img);


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
 * thermoR
 */
unsigned char thermoR(unsigned char v)
{
    if (v < 128)
    {
        return 0;
    }
    else if (v < 192)
    {
        return (v - 128) * 4;
    }
    else
    {
        return 255;
    }
}


/**
 * thermoG
 */
unsigned char thermoG(unsigned char v)
{
    if (v < 64)
    {
        return (v - 64) * 4;
    }
    else if (v < 192)
    {
        return 255;
    }
    else
    {
        return (255 - v) * 4;
    }
}


/**
 * thermoB
 */
unsigned char thermoB(unsigned char v)
{
    if (v <= 64)
    {
        return 255;
    }
    else if (v < 128)
    {
        return (127 - v) * 4;
    }
    else
    {
        return 0;
    }
}


/**
 * ThermoScale
 */
void ThermoScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char gray;
    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = i * img->width + j;
            gray = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;

            img->data[index].r = thermoR(gray);
            img->data[index].g = thermoG(gray);
            img->data[index].b = thermoB(gray);
        }
    }
}
