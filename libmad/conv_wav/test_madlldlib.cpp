/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 * original : https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM
 */


/****************************************************************************
 * test                                               (c) 2004 J. A. Robson
 * 
 * test.cpp -- Primary example to using the madlldlib.dll interface
 *
 * This is an extremely simple example that defines a callback, handles a 
 * few command line parameters (i.e. file to convert, output format), and
 * calls the DLL's main function CbMpegAudioDecoder() to process the MP3 
 * file. See the inline comments for details. For more details about 
 * CbMpegAudioDecoder, see comments in madlldlib.cpp.
 *
 * To compile, see 'Makefile' comments.
 ****************************************************************************/
#include <string> 
#include<iostream>

#include "madlldlib.h"
#include"parse_filename.hpp"

using namespace std;


/*
 * The callback function is used for reporting purposes and
 * garnering information about the source MP3 file. This callback 
 * simply prints information to STDOUT, but it usually would be 
 * used to increment a counter, calculate a percentage, or advance
 * a status bar.
 */
void __stdcall mycb (unsigned long fcnt, unsigned long bcnt, struct mad_header *mhdr) {

	/*
	 * If this is the first iteration (frame count is one)
	 * then print out the MP3 layer information. Using this logic
	 * one can retrieve information about the MP3 file, such as 
	 * channels, layer, etc., that might be useful to the calling
	 * code.
	 */	
	if (fcnt == 1) {
		printf("frame:%d, bytes:%d, layer:%d, mode:%d\n",
				fcnt,
				bcnt,
				mhdr->layer, 
				mhdr->mode);
	}
	else {
		//printf("frame:%d, tot. bytes:%d\n",fcnt,bcnt);
	}
	
}


/* 
 * Program entry point
 * note: argv error checking is minimal (to say the least) 
 */
int main(int argc, char **argv) {
	

	/* status/error reporting */
	char statmsg[256];
	int status;

	/* if not the exact number of command 
	 * line parameters, quit */
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <mp3File> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];	


	/* append suffix to output file */
    string fname = getFileNameWithExt(input);
    string output = fname + ".wav";


	/* call the decoding function with input file,
	 * output file, and callback (defined above). 
	 *
	 * Note on return values: CbMpegAudioDecoder() 
	 * returns 0 if successful, non-zero if it has 
	 * problems opening/reading the files passed. 
	 * libmad, the library concerned with the actual 
	 * MP3 decoding, passes detailed error information 
	 * specific to the MP3 conversion, which gets 
	 * set into the string statmsg. 
	 * (CbMpegAudioDecoder() returns a non-zero 
	 * status at this time as well.) So the upshot 
	 * of this is that both indicators handle 
	 * slightly overlapping but different events,
	 * and are hence both useful. */
	
	/* output as WAV */
    status = CbMpegAudioDecoder(input.c_str(), output.c_str(), 1, statmsg, mycb);

	printf("status = %d \n", status);

	/* relay any errors */	
	if (statmsg){
		printf("%s", statmsg);		
	}

    return EXIT_SUCCESS;
}

