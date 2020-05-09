/**
 * libfp_mp3lame Sample
 * 2020-03-01 K.OHWADA
 */


// encode from wav
// reference : https://stackoverflow.com/questions/2495420/is-there-any-lame-c-wrapper-simplifier-working-on-linux-mac-and-win-from-pure


#include <string> 
#include<iostream>

#include <lame/lame.h>

#include"wav_header.h"

#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    const int WAV_SIZE = 8192;
    const int MP3_SIZE = 8192;

    short int wav_buffer[2*WAV_SIZE];
    unsigned char mp3_buffer[MP3_SIZE];

    int read, write;

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <wavFile> " <<  endl;
        return EXIT_FAILURE;
    }



    char *input = argv[1];

// output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".mp3";
    char* output = (char*)outfile.c_str();


    FILE *fp_wav = fopen(input, "rb");
	if ( !fp_wav ) { 
        cout << "fopen Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    FILE *fp_mp3 = fopen(output, "wb");
	if ( !fp_mp3 ) { 
        cout << "fopen Faild: " << output << endl;
        return EXIT_FAILURE;
	}


// read wav header
    int wavChannels;
    int wavBit;
    int wavSize;
    int wavSamplingrate;
    int ret1 = readWavHeader(fp_wav, &wavChannels, &wavBit, &wavSize, &wavSamplingrate);
	if (ret1 != 0){
        cout << "NOT wav format" << endl;
        return EXIT_FAILURE;
	}

	printf("wavChannels: %d \n", wavChannels);
	printf("wavBit: %d \n", wavBit);
	printf("wavSize: %d \n", wavSize);
	printf("wavSamplingrate: %d \n", wavSamplingrate);

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame,  wavSamplingrate);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    while(1) {

            read = fread(wav_buffer, 2*sizeof(short int), WAV_SIZE, fp_wav);
            if (read == 0){
                // file end
                lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
                break;
            }

            write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, MP3_SIZE);
            int wsize = fwrite(mp3_buffer, write, 1, fp_mp3);

    } // while

    // cleanup
    lame_close(lame);
    fclose(fp_mp3);
    fclose(fp_wav);

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

