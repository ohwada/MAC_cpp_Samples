/**
 * flog_song.cpp
 * 2020-03-01 K.OHWADA
 */

// "Flog Song" is Japanese popular kid song <br/>
// https://youtu.be/H18SYpZShmQ <br/>


#include "flog_song.hpp"

using namespace std;


// global
const float FLOG_TIME = 0.25;
const int FLOG_USEC = 100000;
const int FLOG_COCE_UNDEFINE = -1;


/**
 * Score of Flog Somg
 */
// reference : https://ja.wikipedia.org/wiki/%E3%82%B5%E3%82%AF%E3%83%A9_(%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2)

// note format
// note code + dot + note length
std::vector<std::string> FLOG_SCORE =
{ 
"c.2",  // do
"d.2",  // re
"e.2", // mi
"f.2", // fa
"e.2", // mi
"d.2", // re
"c.4", // do

"e.2", // mi
"f.2", // fa
"g.2", // so
"a.2", // ra
"g.2", // so
"f.2", // fa
"e.4", // mi

"c.4", // do
"c.4", // do
"c.4", // do

"c.2", // do
"c.2", // do
"d.2", // re
"d.2", // re
"e.2", // mi
"e.2", // mi
"f.2", // fa
"f.2", // fa

"e.3", // mi
"d.3", // re
"c.4", // do
};


/**
 * getFlogScore
 */
std::vector<std::string> getFlogScore(){
    return FLOG_SCORE;
}


/**
 * createFlogPcmp
 */
int16_t* createFlogPcm(std::string note, int *pcm_size)
{
		int freq;
		int time;
		bool ret = parseNote(note, &freq, &time);
        if(!ret){
            return NULL;
        }

        int data_size;
		int16_t* data = createTone(freq, time, &data_size);

        *pcm_size = data_size;
        return data;
}


/**
 * parseNote
 */
bool parseNote(std::string note, int *freq, int *time)
{
    char DOT = '.';
    int pos = note.find_first_of(DOT);
    if (pos == string::npos) {
        printf("parseNote: NOT find dot: %s \n", note.c_str());
        return false;
    }

    string note_code = note.substr(0, pos);
    string note_length = note.substr(pos+1, note.size()-pos);

    int int_freq = convFreq(note_code); 
    int int_time = str2i(note_length);
    if (int_freq == 0) {
        printf("parseNote: NOT undefined musical code \n");
        return false;
    }
    if (int_time == 0) {
        printf("parseNote: NOT convert time \n");
        return false;
    }
    *freq = int_freq;
    *time = int_time;
    return true;
}


/**
 * str2i
 */
int str2i(string str)
{
    int val = atoi(str.c_str());
    return val;
}


/**
 * convFreq
 */
// reference : https://tomari.org/main/java/oto.html
int convFreq(string code) 
{
    int freq =  0;
    if(code == "a4"){
        // ra
        freq = 440;
    }else if(code == "b4"){
        // si
        freq = 493;
    }else if(code == "c"){
        // do
        freq = 523;
    }else if( code == "d"){
        // re
        freq = 587;
    }else if(code == "e"){
        // mi
        freq = 659;
    }else if(code == "f"){
        // fa
        freq = 698;
    }else if(code == "g"){
        // so
        freq = 783;
    }else if(code == "a"){
        // ra
        freq = 880;
    }else if(code == "b"){
        // si
        freq = 987;
    }else if(code == "c6"){
        // do
        freq = 1046;
    }
    return freq;
}


/**
 * crateTone
 * 16 bit 44.1 KHz sampling
 */
int16_t* createTone(int freq, int time, int *size)
{

// buffer size for one second
    int tone_size = FLOG_TIME * FLOG_SAMPLINGRATE * time;
    int pause_size = FLOG_TIME * FLOG_SAMPLINGRATE;
int bufsize =  tone_size+pause_size;
	int16_t* buff = new int16_t[bufsize];

// radian per sample rate
	double delta = (2 * M_PI * freq ) / FLOG_SAMPLINGRATE;

// Generate Sin wave for one second
	for (int i = 0; i < tone_size; i++) {
		buff[i] = SHRT_MAX * sin(delta * i);
	}
	for (int i = 0; i < pause_size; i++) {
		buff[tone_size+i] = 0;
	}

    *size = bufsize;
	return buff;
}

int getFlogPauseTime(void)
{
    int time = 4 * FLOG_TIME * FLOG_USEC;
    return time;
}





