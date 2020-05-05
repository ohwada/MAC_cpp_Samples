/**
 * libvorbis Sample
 * 2020-03-01 K.OHWADA
 */


// convert ogg to wav
// reference : https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM

#include <string> 
#include<iostream>

#include "OggReader.hpp"

#include "wav_header.h"

#include"parse_filename.hpp"

using namespace std;



/**
 * main
 */
int main(int argc, char** argv) 
{

OggReader reader;

    if(argc < 2) {
        cout << "Usage: " << argv[0]  << " <oggFile> " << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];	


// append suffix to output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    char* output = (char*)outfile.c_str();

    int ret1 = reader.open(input);
    if(ret1 != 0){
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    reader.printFileInfo();

    // open output
    FILE *fp_output = fopen(output, "wb");
	if ( !fp_output ) { 
        cout << "fopen Faild: " << output << endl;
        return EXIT_FAILURE;
	}


	// write dummy_header header
    writeDummyWavHeader(fp_output);





// endless loop
// exit the loop, when read all the ov_data
    int isFirst = 1; // show debug message at once 
    while(1) 
    {

        int ret2 = reader.read();
        if(ret2 == OGG_READER_END){
            break;
        }

        if(isFirst){
            isFirst = 0;
            reader.printOvInfo();
        }

        // write pcm
        char *data = reader.getBuffer();
		int num_write = fwrite(data, 1, OGG_READER_BUFF_SIZE, fp_output);
		if(num_write != OGG_READER_BUFF_SIZE) {
					cout << "pcm write error" << endl;
					//break;
		}

    } //  while


// close
    reader.close();
    fclose(fp_output);

	// write wav header
    overwriteWavHeader(output, OGG_READER_CHANNELS_STEREO, OGG_READER_SAMPLINGRATE);

   cout << "saved: " << output << endl;

	return EXIT_SUCCESS;
}

