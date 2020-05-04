/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */


// play mp3 file with PulseAudio
// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


#include <pulse/simple.h>
#include <pulse/error.h>

#include "MP3Reader.hpp"


/**
 * main
 */
int main(int argc, char **argv) 
{

    MP3Reader reader;
    int error;

    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }


    char *input = argv[1];


    // Set up PulseAudio 16-bit 44.1kHz stereo output
    const pa_sample_spec ss = { 
        .format = PA_SAMPLE_S16LE, 
        .rate = MP3_SAMPLINGRATE, 
        .channels = MP3_CHANNELS_STEREO };

    pa_simple *device = pa_simple_new(NULL, "MP3 player", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error);
    if (!device) {
        printf("pa_simple_new() Failed: %d \n", error);
        return 1;
    }

    // open input
    int ret = reader.open(input);
    if(ret != 0){
        printf("fopen Failed: %s \n", input);
        return 1;
    }

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
    int size = reader.getFrameDataSize();


        if (pa_simple_write(device, data, size, &error) < 0) {
            printf("pa_simple_write() failed: %s \n", pa_strerror(error));
        }

        // progress info
        reader.printPregress();

    } // while


    // Close
    reader.close();
    fprintf(stderr, "\n"); // add LF to progress

    // Close PulseAudio output
    if (device){
        pa_simple_free(device);
    }

    return EXIT_SUCCESS;
}

