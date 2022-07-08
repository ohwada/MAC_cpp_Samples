/**
 * conv_ogg_to_wav.cpp
 * 2022-06-01 K.OHWADA
 */


// g++ conv_ogg_to_wav.cpp -o decode `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`

#include <iostream> 
#include <string> 
#include"ogg_to_wav.hpp"
#include"parse_filename.hpp"

using namespace std;

/**
 * main
 */
int main(int argc, char** argv) 
{

    if (argc != 2) {
        cout << "Usage: " <<  argv[0] << " <oggFile> " << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];	

    cout << "input: " << input << endl;

    string fname = getFileNameWithExt(input);
    string output = add_wav_ext(fname);

    cout << "output: " << output << endl;

    ogg_to_wav(input, output);
  
	return EXIT_SUCCESS;
}
