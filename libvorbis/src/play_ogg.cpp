/**
 * play_ogg.cpp
 * 2022-06-01 K.OHWADA
 */

// play ogg file with OpenAL
 
// 4473 Done

// g++ play_ogg.cpp -std=c++11  -o play  `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`  -framework OpenAL 


#include<iostream>
#include "play_ogg.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{
     
    if(argc < 2) {
        cout << "Usage: " << argv[0]  << " <oggFile> " << endl;
        return EXIT_FAILURE;
    }

    char* file = argv[1];

        cout << "file: " <<  file << endl;

        play_ogg(file) ;

	return EXIT_SUCCESS;
}

