/**
 * libmad Sample
 * 2020-03-01 K.OHWADA
 */

// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <string> 
#include<iostream>
#include <stdio.h>
#include<unistd.h>
#include <sys/stat.h>


using namespace std;


#define MINIMP3_IMPLEMENTATION
#define MINIMP3_ALLOW_MONO_STEREO_TRANSITION
#include "src/minimp3_ex.h"



// global
const int SAMPLINGRATE = 44100;
const int PCM_BITS = 16;
int io_num;
int fail_io_num = -1;
ALuint buffer;
ALuint source;



/**
 * read16le
 */
static int16_t read16le(const void *p)
{
    const uint8_t *src = (const uint8_t *)p;
    return ((src[0]) << 0) | ((src[1]) << 8);
}


/**
 * preload
 */
static unsigned char *preload(FILE *file, int *data_size)
{

    if (!file){
        *data_size = 0;
        return NULL;
    }

// seek to file end
    if (fseek(file, 0, SEEK_END)){
        *data_size = 0;
        return 0;
    }

    int file_size = (int)ftell(file);

//printf("file_size: %d \n", file_size);

    if (file_size < 0){
        *data_size = 0;
        return NULL;
    }

// seek to file top
    if (fseek(file, 0, SEEK_SET)){
        *data_size = 0;
        return NULL;
    }

// create buffer
    unsigned char *data = new unsigned char[file_size];

// read all data
    int read = fread(data, 1, file_size, file);
    if( read != file_size){
        return NULL;
    }

    *data_size = file_size;
    return data;
}



/**
 * read_cb
 */
static size_t read_cb(void *buf, size_t size, void *user_data)
{
    //printf("%d read_cb(%d)\n", io_num, (int)size);

    if (fail_io_num == io_num++){
        return -1;
    }

    return fread(buf, 1, size, (FILE*)user_data);
}



/**
 * seek_cb
 */
static int seek_cb(uint64_t position, void *user_data)
{
    //printf("%d seek_cb(%d)\n", io_num, (int)position);

    if (fail_io_num == io_num++){
        return -1;
    }

    return fseek((FILE*)user_data, position, SEEK_SET);
}



/**
 * decode_file
 */
static int decode_file(const char *input, const unsigned char *buf_in, int buf_size)
{

    mp3dec_t mp3d;
    mp3dec_io_t io;
    mp3dec_file_info_t info;

    memset(&info, 0, sizeof(info));

    io.read = read_cb;
    io.seek = seek_cb;


    int res = mp3dec_load(&mp3d, input, &info, 0, 0);

    if (res && MP3D_E_DECODE != res)
    {
        printf("error: read function failed, code=%d\n", res);
        return 1;
    }

    int pcm_samplingrate = info.hz;
    int pcm_channels = info.channels;

    printf("mp3dec samplingrate: %d \n", pcm_samplingrate);
    printf("mp3dec channels: %d \n", pcm_channels);
    printf("mp3dec avg_bitrate_kbps: %d \n", info.avg_bitrate_kbps);
    printf("mp3dec layer: %d \n", info.layer);

    int16_t *data = info.buffer;
int data_size = info.samples * sizeof(int16_t);

// fills a buffer with audio data
	alBufferData(buffer, AL_FORMAT_STEREO16, &data[0], data_size, pcm_samplingrate);

    if (data){
        free(data);
    }

    return 0;
}


/**
 * getPlaybackTime
 */
int getPlaybackTime(int file_size)
{
    // calculate roughly
    int time = (float)file_size /  (float)SAMPLINGRATE ;

    return time;
}


/**
 * main
 */
int main(int argc, char *argv[])
{

    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <mp3File> " << endl;
        return EXIT_FAILURE;
    }

    char *input    = argv[1];

    FILE *fp_in = fopen(input, "rb");
    if (!fp_in){
        cout << "fopen Faild: "  << input << endl;
        return EXIT_FAILURE;
    }

    int buf_size;
    unsigned char *buf_in = preload(fp_in, &buf_size);

    if ( !buf_in || (buf_size == 0) ){
        cout << "preload Faild"  << endl;
        fclose(fp_in);
    }

    int time = getPlaybackTime(buf_size);
   printf("File: %d bytes ( %d sec )  \n",  buf_size, time);

// open default device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cerr << "alcOpenDevice Faild" << endl;
        return EXIT_FAILURE;
	}

	ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		cout << "alcCreateContext Faild" << endl;
        return EXIT_FAILURE;
	}

	alcMakeContextCurrent(context);

// generate Buffer and Source
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

    int ret2 = decode_file(input, buf_in, buf_size);
    if(ret2 != 0){
        cout << "decode_file Faild"  << endl;
    }

// play sound data in buffer
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
	sleep(time);
	alSourcePause(source);

    // cleanup
    delete[] buf_in;


    cout << "play end " << endl;


    return EXIT_SUCCESS;
}

