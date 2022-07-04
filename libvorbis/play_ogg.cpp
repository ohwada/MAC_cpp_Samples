/**
 * play_ogg.cpp
 * 2020-03-01 K.OHWADA
 */


// play ogg file with OpenAL
// reference : https://w.atwiki.jp/opengl/pages/172.html

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

    bool ret =playSound(file) ;
if( !ret){
        return EXIT_FAILURE;
    }
 
	return EXIT_SUCCESS;
}

