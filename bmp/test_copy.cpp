/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/kawasin73/todai-bmp
 */

#include <string> 
#include<iostream>

#include"bitmap.h"

#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : copy" << endl;

    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output = fname + "_copy.bmp";


// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );

	if(!img){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
	}

    // file info
	int width = img->width;
	int height = img->height;

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;


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

