/**
 * dds Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include "nv_dds.h"

#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    nv_dds::CDDSImage ddsImage;

    cout << "dds : copy " << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    string fname = getFileNameWithoutExt(input);

    string output = fname + "_copy.dds";


// load image
    ddsImage.load(input);


// file info
    int width = ddsImage.get_width();
    int height = ddsImage.get_height();

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;


    ddsImage.save(output);

    cout << "saved image: " << output << endl;

	return EXIT_SUCCESS;
}



