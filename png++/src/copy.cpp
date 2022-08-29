/**
 * copy.cpp
 * 2020-02-01 K.OHWADA
 */
 
#include<iostream>
#include <string>

#include "png_util.h"
#include"parse_filename.hpp"

using namespace std;


/**
 * file_copy
 */
bool file_copy(string input, string output)
{

int width;
int height;
unsigned char* data = loadImage2(input, width, height);

    if((width==0)||(height ==0)) {
        cerr << "loadImage Faild: " << input  << endl;
        return false;
    }

if( ! saveImage(output, data, width, height) ){
        cerr << "saveImage Faild: " << output  << endl;
        return false;
}

    return true;
}


/**
 * main
 */
int main(int argc, char **argv)
{

    string input("images/uparrow.png");

    if(argc == 2){
        input = argv[1];
    } else {
        cout << "Usage " <<  argv[0] << " <pngFile> " << endl;
    }

    cout << input << endl;

    string fname = getFileNameWithoutExt(input);
    string output = fname + "_copy.png";

    cout << output << endl;

    if( !file_copy(input, output) ) {
        return EXIT_FAILURE;
    }

   cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

// saved: uparrow_copy.png

