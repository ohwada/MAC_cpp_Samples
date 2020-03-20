/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/kawasin73/todai-bmp
 */

#include <string> 
#include<iostream>

#include "sobel.h"

#include"parse_filename.hpp"

using namespace std;

void Binarization(Image *img);


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : sobel binary " << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }


   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_sobel_bin.bmp";


// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );

	if(!img){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    double *tmpMap;

    if ((tmpMap = (double *)malloc(sizeof(double) * img->height * img->width)) == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        return EXIT_FAILURE;
    }

    Sobel(img, tmpMap);
    Binarization(img);

	// write image
    int ret= Write_Bmp ((char *)output.c_str(), img );

	if(ret != 0){
        cerr << "save Image Faild: " << output << endl;
        return EXIT_FAILURE;
	}

    cout << "saved Image : " << output << endl;

    free(tmpMap);
    Free_Image(img);

    return EXIT_SUCCESS;
}


/**
 * conv
 */
unsigned char conv(unsigned char v)
{
    if (v < 50)
        return 0;
    else
        return 255;
}


/**
 * Binarization
 */
void Binarization(Image *img)
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
