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


// global
const int SAMPLINGRATE = 44100; // 44.1 KHz
const int FRAME_LENGTH = 1152; // mp3 frame length
const int BUFF_SIZE  = 4 * FRAME_LENGTH;
const float FRAMES_PER_SEC = (float)SAMPLINGRATE / (float )FRAME_LENGTH ;
const int CHANNELS_STEREO = 2;

struct mad_stream mad_stream;
struct mad_frame mad_frame;
struct mad_synth mad_synth;


// prototype
unsigned char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm);

int scale(mad_fixed_t sample);


/**
 * main
 */
int main(int argc, char **argv) 
{

    int error;
    int num_frames_total; 
	unsigned int frame_count = 0;

    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];


    // Set up PulseAudio 16-bit 44.1kHz stereo output
    const pa_sample_spec ss = { 
        .format = PA_SAMPLE_S16LE, 
        .rate = SAMPLINGRATE, 
        .channels = CHANNELS_STEREO };

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


    // Fetch file size, etc
    struct stat file_stat;
    int fd = fileno(fp);
    int ret = fstat(fd, &file_stat);
    if (ret != 0) {
        printf("fstat Failed: %s \n", input);
        fclose(fp);
        return 1;
    }

    int file_size = (int)file_stat.st_size;
    printf("open: %s (%d bytes) \n",  input, file_size);


    // total  frames
        num_frames_total = file_size / FRAME_LENGTH ;
 
    // Let kernel do all the dirty job of buffering etc, map file contents to memory
    unsigned char *input_stream = (unsigned char *)mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);

    // Copy pointer and length to mad_stream struct
    mad_stream_buffer(&mad_stream, (const unsigned char *)input_stream, file_size);

    // Decode frame and synthesize loop
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

        unsigned char *data = getStereoData(&mad_frame.header, &mad_synth.pcm);

        if (pa_simple_write(device, data, BUFF_SIZE, &error) < 0) {
            printf("pa_simple_write() failed: %s \n", pa_strerror(error));
        }

		frame_count++;
        if(frame_count > (num_frames_total + 10)){
            // maybe loaded all the frames
            // margin 10 frames
            break;
        }

        int percent = (int)(100.0 * (float)frame_count / (float)num_frames_total);
        fprintf(stderr, "\r [ %3d / %3d ] ( %2d %% ) ", 
            frame_count,  num_frames_total,  percent);

    } // while

    // Close
    fclose(fp);
    fprintf(stderr, "\n");

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
    static char stream[BUFF_SIZE];
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
        if (pa_simple_write(device, stream, BUFF_SIZE, &error) < 0) {
            printf("pa_simple_write() failed: %s\n", pa_strerror(error));
            return;
        }
    } else {
        printf("Mono not supported \n");
    }

}


/**
 * getStereoData
 */
unsigned char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm) {
    int length = pcm->length;
    int channels = pcm->channels;
    register int nsamples = length;
    const mad_fixed_t *left_ch = pcm->samples[0];
    const mad_fixed_t *right_ch = pcm->samples[1];


    if (channels != 2) {
        printf("Mono not supported! \n");
        return NULL;
    }


    // stereo
    unsigned char *buff = new unsigned char[BUFF_SIZE];

    while (nsamples--) {
            int index = 4 * (length - nsamples);
            signed int sample_left = scale(*left_ch++);
            signed int sample_right = scale(*right_ch++);
            buff[index + 0 ] = ((sample_left >> 0) & 0xff);
            buff[index +1] = ((sample_left >> 8) & 0xff);
            buff[index+2 ] = ((sample_right >> 0) & 0xff);
            buff[index +3] = ((sample_right >> 8) & 0xff);
        } // while

    return buff;
}

