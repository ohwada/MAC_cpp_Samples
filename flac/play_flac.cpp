/**
 * flac Sample
 * 2020-03-01 K.OHWADA
 */


// play flac file
// original : https://github.com/xiph/flac/tree/master/examples


// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <string> 
#include<iostream>
#include<unistd.h>

#include <FLAC++/decoder.h>

#include "FlacReader.hpp"

#include"parse_filename.hpp"

using namespace std;


// prototype
static FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data);
static void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data);
static void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data);


// global
 FlacReader  reader;

ALuint al_source;
ALuint al_buffer;
int num_frames_total;
int num_frames_about_10_secs;
int frame_count = 0;
bool isFirst = true;



/**
 * main
 */
int main(int argc, char **argv)
{

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <flacFile> " <<  endl;
        return EXIT_FAILURE;
    }

    char *input = argv[1];


// file size
    int file_size = reader.getFileSize(input);
    cout << "file_size: " << file_size  << " bytes " << endl;

    // number of 10 seconds frames
    num_frames_about_10_secs = 10 * reader.FRAMES_PER_SEC;

    ALCdevice* device = alcOpenDevice(NULL);
	if (!device){
        cout << "alcOpenDevice Faild" << endl;
        return EXIT_FAILURE;
	}

    ALCcontext* context = alcCreateContext(device, NULL);
	if (!context){
        cout << "alcCreateContext Faild" << endl;
        return EXIT_FAILURE;
	}

    alcMakeContextCurrent(context);
    alGenSources(1, &al_source);


int ret1 = reader.open(input, 
        write_callback,
        metadata_callback, 
        error_callback );

	if(ret1 != 0) {
        cout << "open Faild: " << input << endl;
        return EXIT_FAILURE;
	}


    bool ok = reader.end_of_stream();
    reader.printResult(ok);

    reader.close();

    return EXIT_SUCCESS;
}


/**
 * write_callback
 */
FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const pcm_buffer[], void *client_data)
{

    int ret1 = reader.proc_write_callback(decoder, frame, pcm_buffer, client_data);

    if(ret1 == FLAC_READER_ABORT){
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }

    unsigned char* data = reader.getPcmData();
    int datasize = reader.getPcmDataSize();


    ALint state;
    ALint  num;

        alGetSourcei(al_source, AL_BUFFERS_QUEUED, &num);
        if (num < num_frames_about_10_secs) {
            // wait for the first 10 seconds
            alGenBuffers(1, &al_buffer);

        } else {
            // it seems to finish reading frames of the first 10 seconds
            alGetSourcei(al_source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    // play in not
                    alSourcePlay(al_source);
                    fprintf(stderr, "\n alSourcePlay \n");
                }

                // wait for the buffer to be processed
                while (alGetSourcei(al_source, AL_BUFFERS_PROCESSED, &num), num == 0) {
                    sleep(1);
                }

                // remove buffer fron queue
                alSourceUnqueueBuffers(al_source, 1, &al_buffer);

        } // if num

        alBufferData(al_buffer,  AL_FORMAT_STEREO16,  data, datasize,  FLAC_READER_SAMPLINGRATE);

        alSourceQueueBuffers(al_source, 1, &al_buffer);

        reader.printProgess();

	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}


/**
 * metadata_callback
 */
void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{
    reader.proc_metadata_callback(decoder, metadata, client_data);
}


/**
 * error_callback
 */
void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
    reader.proc_error_callback( decoder, status, client_data);
}

