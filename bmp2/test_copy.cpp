/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/kawasin73/todai-bmp
 */

#include <string> 
#include<iostream>

#include "bmp.h"

#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

    cout << "bmp : copy" << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];

    string fname = getFileNameWithoutExt(input);

    string output_copy = fname + "_copy.bmp";
    string output_gray = fname + "_gray.bmp";

// read image
      image_t *img = read_bmp_file(input.c_str());

	if(!img){
        cerr << "read_bmp_file Faild: " << input << endl;
        return EXIT_FAILURE;
	}

    cout << "read_bmp_file: " << input  << endl;

    dump_image_info(img);


	// write image
    int COMPRESS = 0;
          result_t ret1 = write_bmp_file(output_copy.c_str(), img, COMPRESS);
	if(ret1 != SUCCESS){
        cout << "write_bmp_file faild: "  << endl;
        return EXIT_FAILURE;
    }

    cout << "saved Image : " << output_copy << endl;

image_t *gray = image_rgb_to_gray(img);

	// write image
          result_t ret2 = write_bmp_file(output_gray.c_str(), gray, COMPRESS);
	if(ret2 != SUCCESS){
        cout << "write_bmp_file faild: "  << endl;
        return EXIT_FAILURE;
    }

    cout << "saved Image : " << output_gray << endl;

    return EXIT_SUCCESS;

}

