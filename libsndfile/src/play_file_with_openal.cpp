/**
 * libsndfile sample
 * 2020-03-01 K.OHWADA
 */

//play file with openAL
// reference : https://gist.githubusercontent.com/take-cheeze/4233185/raw/7597479f0b2d20795557e1c730d4db9172ee28e6/libsndfile_test.cxx


// macOS
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <sndfile.h>

#include <stdlib.h>
#include<unistd.h>

#include <iostream>
#include <vector>


using namespace std;

		

/**
 * main
 */
int main(int argc, char **argv) 
{

	const int BUFLEN = 4096;

	uint16_t* read_buffer = new uint16_t[BUFLEN];


	if(argc !=2){
		cout << "Usage: " << argv[0] << " <audioFile>" << endl;
        return EXIT_FAILURE;
	}

	char *input = argv[1];


	ALCdevice *device = alcOpenDevice(NULL);
	if (!device){
		cout <<  "alcOpenDevice Faild" << endl;
        return EXIT_FAILURE;
	}


	ALCcontext *context = alcCreateContext(device, NULL);
	if (!context){
		cout << "alcCreateContext Faild" << endl;
        return EXIT_FAILURE;
	}

	alcMakeContextCurrent(context);

	ALuint buffer, source;
	alGenSources(1, &source);
	alGenBuffers(1, &buffer);


	SF_INFO info;
	SNDFILE* file = sf_open(input, SFM_READ, &info);

	if(!file){
		cout << "sf_open failed: " << input << endl;
        return EXIT_FAILURE;
	}


	cout << "channels: " << info.channels << endl;
	cout << "samplerate:  " << info.samplerate << endl;	
	cout << "frames:  " << info.frames << endl;


	vector<uint16_t> data;
	while(true) {

			size_t  read_size = sf_read_short(file, (short *)read_buffer, BUFLEN);
			if(read_size ==0){
				break;
			}
		  // cout << "read_size: " << read_size << endl;

			for(int j=0; j < read_size; j++) {
				data.push_back(read_buffer[j]);
			} // for

	} // while


	ALenum format = info.channels == 1? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	int data_size = data.size();
	int buf_size =  data_size * sizeof(uint16_t);
	float playtime = (data_size / info.channels) / info.samplerate;

	cout << "data_size " << data_size << endl;
	cout << "playtime " << playtime <<  " sec" << endl;

	alBufferData(buffer, format,
				 &data.front(), buf_size, info.samplerate);

	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);
	
	int loop_count = 0;
	while(true) {
		sleep(1);
		loop_count ++;
		if(loop_count >  playtime ){
			break;
		}

		// progess info
		int time_remain = playtime - loop_count;
    	fprintf(stderr, "\r ( %3d sec)",  time_remain);

		} // while

    	fprintf(stderr, "\n");

 	alSourceStop(source);

	// cleanup
	alDeleteBuffers(1, &buffer);
	alDeleteSources(1, &source);
	delete[] read_buffer;

	return EXIT_SUCCESS;
}
