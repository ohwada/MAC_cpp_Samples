/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */


// convrt mp3 to wav
// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


#include "MP3Reader.hpp"

#include "wav_header.h"

#include"parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv) 
{

    MP3Reader reader;

    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];


// append suffix to output file
    string fname = getFileNameWithExt(input);
    string outfile = fname + ".wav";
    char* output = (char*)outfile.c_str();

    // open input
    int ret = reader.open(input);
    if(ret != 0){
        printf("fopen Failed: %s \n", input);
        return 1;
    }

    // open output
    FILE *fp_output = fopen(output, "wb");
	if ( !fp_output ) { 
        printf( "fopen Faild: %s \n", output);
		return 1;
	}


	// write dummy_header header
    writeDummyWavHeader(fp_output);


    // total  frames
    reader.printFileInfo();

    // Decode frame and synthesize loop
    while (1) {

        // Decode frame from the stream
    int ret2 = reader.decode();
        if (ret2 == MP3_DECODE_SKIP) {
                continue;
        } else if (ret2 == MP3_DECODE_END) { 
                break;
        }


    unsigned char* data = reader.getFrameData();
    int size = reader.FRAME_BUFF_SIZE;

// write pcm
		int num_write = fwrite(data, 1, size, fp_output);
		if(num_write != size) {
				printf("pcm write error \n");
				//break;
		}

    } // while

    reader.printDecodedInfo();

    // Close
    reader.close();
    fclose(fp_output);


	// write wav header
    overwriteWavHeader(output, MP3_CHANNELS_STEREO, MP3_SAMPLINGRATE);

    printf("saved: %s \n", output);

    return EXIT_SUCCESS;
}
