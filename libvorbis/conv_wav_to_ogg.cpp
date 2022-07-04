/**
 * cov_wav_to_ogg.cpp
 * 2020-03-01 K.OHWADA
 */


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
    string output = addExtOgg(fname);
 
    int ret = convWavToOgg(input, output);

	if(ret == ENCODE_SUCCESS) {
    cout <<"saved: " << output << endl;
	} else if(ret == ENCODE_ERR_INPUT) {
        cout << "fopen Faild : " << input << endl;
	} else if(ret == ENCODE_ERR_OUTPUT) {
        cout << "fopen Faild : " << output << endl;
	} else if (ret == ENCODE_ERR_FORMAT ){
        cout << "NOT wav format" << endl;
	} else if(ret == ENCODE_ERR_INIT){
        cout << "vorbis_encode_init_vbr Faild" << endl;
    }

	return EXIT_SUCCESS;
}

