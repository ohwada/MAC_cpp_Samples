/**
 * gray.cpp
 * 2020-02-01 K.OHWADA
 */
 
#include<iostream>
#include <string>

#include "png_util.h"
#include"parse_filename.hpp"

using namespace std;


/**
 *  conv_gray
 */
void conv_gray(char *data,
    int width,
    int height,
    int ch)
{
const unsigned char MAX = 255;

 bool has_alpha = (ch==4)? true : false;

  for(int j = 0; j < height; j++) {
    for(int i = 0; i < width; i++)
    {
        int index = ch * (i + j * width);
        unsigned char ave = ( (unsigned char)data[index] + (unsigned char)data[index+1] + (unsigned char)data[index+2] )/3;

        data[index]  = ave;
        data[index+1] = ave;
        data[index+2]  = ave;
        if( has_alpha){
            data[index+3]  = MAX;
        }
    } // for i
  } // for j
}


/**
 * gray_file
 */
bool gray_file(string input, string output)
{

int width;
int height;
char* data = loadImage2(input, width, height);

    if(!data){
        cerr << "loadImage Faild: " << input  << endl;
        return false;
    }

conv_gray(data, width, height, 4);

if( ! saveImage(output, data, width, height) ){
        cerr << "loadImage Faild: " << output  << endl;
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
    string output = fname + "_gray.png";

    cout << output << endl;

    if( !gray_file(input, output) ) {
        return EXIT_FAILURE;
    }

   cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

// saved: uparrow_copy.png

