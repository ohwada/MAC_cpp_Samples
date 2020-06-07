/**
 * stb sample
 * 2020-03-01 K.OHWADA
 */

// convert ogg file to wav file
// reference : https://github.com/nothings/stb/blob/master/tests/test_vorbis.c

#include <string> 
#include<iostream>

#include "wav_header.h"

#include "parse_filename.hpp"

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

#define STB_DEFINE
#include "stb.h"

using namespace std;

extern void stb_vorbis_dumpmem(void);


/**
 * main
 */
int main(int argc, char **argv)
{
  
    const int BITS_PER_SAMPLE = 16;

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <oggFile> "  << endl;
        return EXIT_FAILURE;
    }

    char* file_input = (char *)argv[1];
    
    string fname = getFileNameWithExt(file_input);

    string fname_out = fname + ".wav";
    char* output = (char *)fname_out.c_str();

    size_t memlen;
    unsigned char *mem = stb_fileu(file_input, &memlen);

   int chan, samplerate;
   short *data;
   int samples = stb_vorbis_decode_memory(mem, memlen, &chan, &samplerate, &data);

    cout << "samples: " << samples << endl;
    cout << "chan: " << chan << endl;
    cout << "samplerate: " << samplerate << endl;

    int size = 2 * chan * samples;

    FILE* fp = fopen(output, "wb");
    writeDummyWavHeader(fp);
    fwrite(data, 1, size, fp);
    fclose(fp);
    overwriteWavHeader(output, chan, BITS_PER_SAMPLE, samplerate);

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}

