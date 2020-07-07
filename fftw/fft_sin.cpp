/**
 * fftw sample
 * 2020-03-01 K.OHWADA
 */

// calc FFT of single sin wave
 // reference : https://qiita.com/Talokay/items/f7baddd661238e61dc51

#include <iostream>
#include <string.h>
#include<math.h>
#include "fftw3.h"

using namespace std;

// global 
const int FFTSIZE = 1024;
const float SAMPLINGRATE = 44100.0;


/**
 * calcFreq
 */
inline float calcFreq( int index)
{
    float freq = index * SAMPLINGRATE / FFTSIZE;
    return freq;
}


/**
 * createSin
 */
void createSin(fftw_complex *in, int freq)
{
    cout << "createSin: " << freq << endl;

    float div = (float)freq / SAMPLINGRATE * 2 * M_PI ;

    for(int i=0; i<FFTSIZE; i++){
        in[i][0] = sin(div*i);
        in[i][1] = 0.0;
    }

}


/**
 * getAmplitude
 */
float* getAmplitude(fftw_complex *out)
{
    float *buf =  new float[FFTSIZE];

    for(int i=0; i<FFTSIZE; i++){
        buf[i] = out[i][0] * out[i][0] + out[i][1] * out[i][1];
    }

    return buf;
}


/**
 * findIndexAtMaxAmplitude
 */
int findIndexAtMaxAmplitude(float *amplitude)
{
    int index = 0;
    float max = 0;

    for(int i=0;i<FFTSIZE;i++) {
        float amp = amplitude[i];
        if(amp > max){
            max = amp;
            index = i;
        }
    }
    return index;
}


/**
 * printResult
 */
void printResult(float *amplitude)
{
    int index = findIndexAtMaxAmplitude(amplitude);
    float freq = calcFreq(index);
    float max = amplitude[index];

    cout << "index " << index << endl;
    cout << "max " << max << endl;
    cout << "freq " << freq << endl;
}


/**
 * writeAmplitude
 */
bool writeAmplitude(string filepath, float *amplitude)
{
    FILE *fp = fopen( filepath.c_str(), "w");
    if(!fp){
        return false;
    }

    char *buf =  new char[100];

    for(int i=0; i<FFTSIZE ;i++) {
        float freq = calcFreq(i);
        sprintf(buf, "%d, %lf, %lf \n" ,i, freq, amplitude[i]);
        int size = strlen(buf);
        fwrite(buf, 1, size, fp);
    }

    fclose(fp);
    return true;
}


/**
 * createOutputFilePath
 */
string createOutputFilePath(int freq)
{
    string filepath = (char *)"fft_sin_" + std::to_string(freq) +  (char *)".txt";
    return filepath;
}


/**
 * main
 */
int main(int argc, const char ** argv) 
{

    fftw_complex *in, *out;
    fftw_plan plan;

    int freq = 440;

    if(argc == 2) {
        freq = atoi(argv[1]);
    } else {
        cout << "Usage: " << argv[0] << " <freq> "  << endl;
    }

    string filepath = createOutputFilePath(freq);

    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) *FFTSIZE);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) *FFTSIZE);
    plan = fftw_plan_dft_1d(FFTSIZE, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    createSin(in, freq);

    fftw_execute(plan); /* repeat as needed */

    fftw_destroy_plan(plan);
    fftw_free(in);

    float* amplitude = getAmplitude(out);
    fftw_free(out);

    printResult(amplitude);

    bool ret = writeAmplitude( filepath, amplitude);
    if(ret){
        cout << "saved: " << filepath << endl;
    } else {
        cout << "write error: " << filepath << endl;
    }

    return EXIT_SUCCESS;
}

