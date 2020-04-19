/**
 * PulseAudio Sample
 * 2020-03-01 K.OHWADA
 */


// play mp3 file
// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mad.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define FRAME_SIZE 1152
#define STREAM_SIZE (1152*4)

int ret = 1;
struct mad_stream mad_stream;
struct mad_frame mad_frame;
struct mad_synth mad_synth;


void output(pa_simple *device, struct mad_header const *header, struct mad_pcm *pcm);


/**
 * main
 */
int main(int argc, char **argv) 
{

    int error;
    int max_frame; 

    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];

    // Set up PulseAudio 16-bit 44.1kHz stereo output
    const pa_sample_spec ss = { .format = PA_SAMPLE_S16LE, .rate = 44100, .channels = 2 };

    pa_simple *device = pa_simple_new(NULL, "MP3 player", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error);
    if (!device) {
        printf("pa_simple_new() Failed: %d \n", error);
        return 1;
    }

    // Initialize MAD library
    mad_stream_init(&mad_stream);
    mad_synth_init(&mad_synth);
    mad_frame_init(&mad_frame);



    // File pointer
    FILE *fp = fopen(input, "rb");
    if (!fp) {
        printf("fopen Failed: %s \n", input);
        return 1;
    }

    printf("fopen: %s \n", input);

    int fd = fileno(fp);

    // Fetch file size, etc
    struct stat metadata;
    if (fstat(fd, &metadata) >= 0) {
        int file_size = (int)metadata.st_size;

        // margin 10 frames
        max_frame = ( file_size / FRAME_SIZE ) + 10  ;
 
        printf("File size %d bytes \n", file_size);
    } else {
        printf("Failed to stat %s \n", input);
        fclose(fp);
        return 1;
    }

    // Let kernel do all the dirty job of buffering etc, map file contents to memory
    char *input_stream = mmap(0, metadata.st_size, PROT_READ, MAP_SHARED, fd, 0);

    // Copy pointer and length to mad_stream struct
    mad_stream_buffer(&mad_stream, (const unsigned char *)input_stream, metadata.st_size);

    // Decode frame and synthesize loop
    int cnt = 0;
    while (1) {

        // Decode frame from the stream
        if (mad_frame_decode(&mad_frame, &mad_stream)) {
            enum mad_error stream_error = mad_stream.error;
            if (MAD_RECOVERABLE(stream_error)) {
                continue;
            } else if (stream_error == MAD_ERROR_BUFLEN) {
                continue;
            } else {
                break;
            }
        }

        // Synthesize PCM data of frame
        mad_synth_frame(&mad_synth, &mad_frame);
        output(device, &mad_frame.header, &mad_synth.pcm);

        cnt++;
        if(cnt > max_frame){
            // maybe loaded all the frames
            break;
        }

    } // while

    // Close
    fclose(fp);
    printf("fclose \n");

    // Free MAD structs
    mad_synth_finish(&mad_synth);
    mad_frame_finish(&mad_frame);
    mad_stream_finish(&mad_stream);

    // Close PulseAudio output
    if (device){
        pa_simple_free(device);
    }

    return EXIT_SUCCESS;
}


// Some helper functions, to be cleaned up in the future
int scale(mad_fixed_t sample) {
     /* round */
     sample += (1L << (MAD_F_FRACBITS - 16));
     /* clip */
     if (sample >= MAD_F_ONE)
         sample = MAD_F_ONE - 1;
     else if (sample < -MAD_F_ONE)
         sample = -MAD_F_ONE;
     /* quantize */
     return sample >> (MAD_F_FRACBITS + 1 - 16);
}


/**
 * output
 */
void output(pa_simple *device, struct mad_header const *header, struct mad_pcm *pcm) {

    register int nsamples = pcm->length;
    mad_fixed_t const *left_ch = pcm->samples[0], *right_ch = pcm->samples[1];
    static char stream[STREAM_SIZE];
    int error;

    if (pcm->channels == 2) {
        while (nsamples--) {
            signed int sample;
            sample = scale(*left_ch++);
            stream[(pcm->length-nsamples)*4 ] = ((sample >> 0) & 0xff);
            stream[(pcm->length-nsamples)*4 +1] = ((sample >> 8) & 0xff);
            sample = scale(*right_ch++);
            stream[(pcm->length-nsamples)*4+2 ] = ((sample >> 0) & 0xff);
            stream[(pcm->length-nsamples)*4 +3] = ((sample >> 8) & 0xff);
        }
        if (pa_simple_write(device, stream, STREAM_SIZE, &error) < 0) {
            printf("pa_simple_write() failed: %s\n", pa_strerror(error));
            return;
        }
    } else {
        printf("Mono not supported \n");
    }

}


// gcc -o player player.c -lpulse -lpulse-simple -lmad -g


