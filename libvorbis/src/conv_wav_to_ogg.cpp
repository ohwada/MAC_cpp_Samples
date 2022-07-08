/**
 * conv_wav_to_ogg.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ conv_wav_to_ogg.cpp -o encode `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`   -lvorbisenc


#include<iostream>
#include "wav_to_ogg.hpp"
#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{

    if(argc < 2) {
        cout << "Usage:" << argv[0] <<  " <wavFile> " << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];


// output file
    string fname = getFileNameWithExt(input);
    string output = add_ogg_ext(fname);
 
    wav_to_ogg(input, output);


	return EXIT_SUCCESS;
}

