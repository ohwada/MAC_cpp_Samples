/**
 * OpenAL Sample
 * 2020-03-01 K.OHWADA
 */


// play mp3 file
// reference : https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <mad.h>

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
char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm);

int scale(mad_fixed_t sample);


/**
 * main
 */
int main(int argc, char **argv) 
{

    int error;
    int num_frames_total; 

    ALuint source;
    ALuint buffer;
    ALint state;
    ALint  num;

	mad_timer_t mad_timer;
	unsigned int frame_count = 0;

    // Parse command-line arguments
    if (argc != 2) {
        printf( "Usage: %s <mp3File> \n", argv[0]);
        return 1;
    }

    // Filename pointer
    char *input = argv[1];


    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        printf("alcOpenDevice Faild \n");
		return 1;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        printf("aalcCreateContext  Faild \n");
		return 1;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &source);

    // Initialize MAD library
    mad_stream_init(&mad_stream);
    mad_synth_init(&mad_synth);
    mad_frame_init(&mad_frame);
	mad_timer_reset(&mad_timer);


    // File pointer
    FILE *fp = fopen(input, "rb");
    if (!fp) {
        printf("fopen Failed: %s \n", input);
        return 1;
    }


    // Fetch file size, etc
    struct stat file_stat;
    int fd = fileno(fp);
    int ret = fstat(fd, & file_stat);
    if (ret != 0) {
        printf("fstat Failed: %s \n", input);
        fclose(fp);
        return 1;
    }

    int file_size = (int)file_stat.st_size;
    printf("open: %s (%d bytes) \n",  input, file_size);

    // Let kernel do all the dirty job of buffering etc, map file contents to memory
    unsigned char *input_stream = (unsigned char *)mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);

    // Copy pointer and length to mad_stream struct
    mad_stream_buffer(&mad_stream, input_stream, file_size);


    // total  frames
    num_frames_total = ( file_size / FRAME_LENGTH ) ;

    // number of 10 seconds frames
    int num_frames_about_10_secs = 10 * FRAMES_PER_SEC;

// estimated playback time
    int playback_time = (int)( (float)num_frames_total / FRAMES_PER_SEC );

    printf("total: %d frames \n",  num_frames_total);
    printf("playback_time: %d sec \n",  playback_time);





    // Decode frame and synthesize loop
    int isFirst = 1;

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

		frame_count++;
		mad_timer_add(&mad_timer, mad_frame.header.duration);

        // Synthesize PCM data of frame
        mad_synth_frame(&mad_synth, &mad_frame);
        //output(device, &mad_frame.header, &mad_synth.pcm);

    struct mad_pcm *pcm = &mad_synth.pcm;
    int pcm_samplerate = pcm->samplerate;
    int pcm_length = pcm->length;
    int pcm_channels = pcm->channels;
    if(pcm_length != FRAME_LENGTH) {
        printf("NOT support length = %d \n", pcm_length);
        continue; 
    }else if(pcm_samplerate != SAMPLINGRATE) {
        printf("NOT support samplerate = %d \n", pcm_samplerate);
        continue;
    }else if(pcm_channels != CHANNELS_STEREO) {
        printf("NOT support channels = %d \n", pcm_channels);
        continue;
    }
    if(isFirst){
        isFirst = 0;
        printf("length = %d \n", pcm_length);
        printf("channels = %d \n", pcm_channels);
        printf("samplerate = %d \n", pcm_samplerate);
    }


           char *data = getStereoData(&mad_frame.header, &mad_synth.pcm);


        alGetSourcei(source, AL_BUFFERS_QUEUED, &num);
        if (num < num_frames_about_10_secs) {
            // wait for the first 10 seconds
            alGenBuffers(1, &buffer);

        } else {
            // it seems to finish reading frames of the first 10 seconds
            alGetSourcei(source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    // play in not
                    alSourcePlay(source);
                    fprintf(stderr, "\n alSourcePlay \n");
                }

                // wait for the buffer to be processed
                while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(source, 1, &buffer);

        } // if num


        alBufferData(buffer,  AL_FORMAT_STEREO16,  data, BUFF_SIZE,  SAMPLINGRATE);

        alSourceQueueBuffers(source, 1, &buffer);

        if(frame_count > (num_frames_total + 10)){
            // maybe loaded all the frames
            // margin 10 frames
            break;
        }

        // progress info
        int remain_frames = num_frames_total -  frame_count;
        if(remain_frames < 0){
            remain_frames = 0;
        }

        float remain_sec = (float)remain_frames / FRAMES_PER_SEC;
        fprintf(stderr, "\r [ %3d / %3d ] ( %3d sec)", 
            frame_count, num_frames_total, (int)remain_sec);

    } // while


    // Close
    fclose(fp);


    // decode info
	char	timer_dest[80];
    const char  *TIMER_FORMAT = "%lu: %02lu.%03u";
	mad_timer_string(mad_timer, 
                timer_dest, 
                TIMER_FORMAT,
				MAD_UNITS_MINUTES, MAD_UNITS_MILLISECONDS, 
                0 );
    fprintf(stderr, "\n");
	printf("%d frames ( %s ) \n",
				frame_count, timer_dest);


// play if not
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source);
        printf("alSourcePlay \n");
    }


// wait to finish
    state = AL_PLAYING;
    while (1)
    {

        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING){
            // finish
            break;
        }

        ALenum err = alGetError(); 
        if(err != AL_NO_ERROR){
             printf("play Faild: %d \n", err);
            break;
        }


        sleep(1);

  } // while





// remove queueing buffers
    ALint num_processed;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_processed);
    for(int i=0; i<num_processed; i++){
        alSourceUnqueueBuffers(source, 1, &buffer);
        alDeleteBuffers(1, &buffer);
    }


    // Free MAD structs
    mad_synth_finish(&mad_synth);
    mad_frame_finish(&mad_frame);
    mad_stream_finish(&mad_stream);


// cleanup
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);


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
 * getStereoData
 */
char* getStereoData(struct mad_header const *header, struct mad_pcm *pcm) {
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
    char *buff = new char[BUFF_SIZE];

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

