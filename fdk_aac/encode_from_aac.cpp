/**
 * fdk aac Sample
 * 2020-03-01 K.OHWADA
 */

// encode from aac
// original : https://github.com/akanchi/aac-example

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AacEncoder.hpp"

#include "wav_header.h"

#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

	const int AAC_BITRATE = 128000;
	const int WAV_BITS_16 = 16;


	AacEncoder encoder;



    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <wavFile> "  << endl;
        return EXIT_FAILURE;
    }


   char* input = argv[1];


// output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".aac";
    char* output = (char*)outfile.c_str();


// open input
    FILE *fp_in = fopen(input, "rb");
    if (!fp_in) {
        cout << "fopen Faild: " << input << endl;
        return EXIT_FAILURE;
    }

// read wav header
    int wavChannels;
    int wavBit;
    int wavSize;
    int wavSamplingrate;

    int ret1= readWavHeader(fp_in, &wavChannels, &wavBit, &wavSize, &wavSamplingrate);
    if (ret1 != 0) {
        cout << "NOT wav format" << endl;
        return EXIT_FAILURE;
    }

	cout << "channels: " << wavChannels << endl; 
	cout << "sample_rate: " << wavSamplingrate << endl; 
	cout << "bits per sample: " << wavBit << endl; 

	if (wavBit != WAV_BITS_16) {
        cout << "NOT support bits " << endl;
        return EXIT_FAILURE;
	}

// open aac
	ofstream out_aac(output, ios::binary);

    int ret2 = encoder.aacenc_init(2, wavChannels, wavSamplingrate, AAC_BITRATE);
    if( ret2 != AACENC_OK) {
            cout << "aacenc_init Faild" << endl;
            return EXIT_FAILURE;
	}


// create pcm buffer
	int pcmSize = wavChannels * 2 * encoder.aacenc_frame_size();


	std::vector<char> pcm_buf(pcmSize, 0);

	int nbSamples = encoder.aacenc_frame_size();
	
// create aac buffer
	int nbAac = encoder.aacenc_max_output_buffer_size();


	std::vector<char> aac_buf(nbAac, 0);

	while (1) {
		int aacSize = aac_buf.size();

// read wav
	    int read = fread((unsigned char *)&pcm_buf[0], 1, pcm_buf.size(), fp_in);


        if (read <= 0){
            // read all data
            break;
        }

		//if ((err = encoder.aacenc_encode(&pcm_buf[0], read, nbSamples, &aac_buf[0], aacSize)) != AACENC_OK) {
        int err = encoder.aacenc_encode(&pcm_buf[0], read, nbSamples, &aac_buf[0], aacSize);
		if ((err != AACENC_OK)&&(err != FDKAAC_ENC_ERR_LEN)) {
			cout << "aacenc_encode error code: " << err << endl;
		}

		if (aacSize > 0) {
			out_aac.write(aac_buf.data(), aacSize);
		}

	} // while

	// close
    fclose(fp_in);
	out_aac.close();

     cout << "saved:" << output << endl;

    return EXIT_SUCCESS;
}

