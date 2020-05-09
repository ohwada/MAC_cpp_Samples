/**
 * fdk aac Sample
 * 2020-03-01 K.OHWADA
 */

// convert aac to wav
// original : https://github.com/akanchi/aac-example
/**
* @see ISO/IEC 13818-7 Information technology — Generic coding of moving pictures and associated audio information 
		— Part 7:Advanced Audio Coding (AAC)
6.2.1
6.2.2
*/

#include <string>
#include <iostream>

#include "AacReader.hpp"

#include "wav_header.h"

#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

	AacReader reader;

    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <aacFile> "  << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];

// output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    char* output = (char*)outfile.c_str();


	FILE* fp_out = fopen(output, "wb");
	if(!fp_out) {
        cout << "fopen Faild: " << output << endl;
        return EXIT_FAILURE;
	}

	// write dummy_header header
    writeDummyWavHeader(fp_out);

// read input
	int ret1 = reader.readFile(input);
    if(ret1 != 0){
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
    }


// endless loop
    while (1) {

	    int ret = reader.decodeAac();
    	if (ret == AAC_READER_END) {
    		break;
    	}else if (ret == AAC_READER_CONTINUE) {
			continue;
    	}

// write pcm
	    char* data = reader.getPcmData();
	    int data_size = reader.getPcmDataSize();


		int wsize = fwrite(data, 1, data_size, fp_out);
		if(wsize != data_size) {
				cout << "pcm write error" << endl;
		}

    } // while


    // Close
    fclose(fp_out);
     reader.freeBuffer();
	reader.printDecodeInfo();

	// write wav header
	int samplerate = reader.getSampleRate();
	int channels = reader.getChannels();

    overwriteWavHeader(output, channels, samplerate);

     cout << "saved:" << output << endl;

    return EXIT_SUCCESS;
}

