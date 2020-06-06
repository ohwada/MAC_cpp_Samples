/**
 * Flog Song
 * 2020-03-01 K.OHWADA
 */


# include <string>
# include <vector>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#define FLOG_SAMPLINGRATE 44100
#define FLOG_CHANNELS 1
#define FLOG_BITS 16
#define FLOG_BYTES_PER_SAMPLE 2

std::vector<std::string> getFlogScore();

int16_t* createFlogPcm(std::string note, int *size);

bool parseNote(std::string note, int *freq, int *time);

int convFreq(std::string tone);

int str2i(std::string str);

int16_t* createTone(int freq, int time, int *size);

