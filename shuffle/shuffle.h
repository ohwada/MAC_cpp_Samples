/**
 * sshuffle sample
 * 2020-03-01 K.OHWADA
 */


// shufle char in string with C random 
// reference : http://www5.airnet.ne.jp/tomy/cpro/ra4.htm


#include <stdlib.h>
#include <string.h>
#include <time.h>


#ifndef _H_SHUFFLE_H_
#define _H_SHUFFLE_H_

// prototype
int genRandom(int min, int max);
void shuffleChars(char* chars);


/**
 * genRandom
 */
int genRandom(int min, int max)
{
	static int flag;
    struct timespec ts;

	if (flag == 0) {
        timespec_get(&ts, TIME_UTC);
        srandom(ts.tv_nsec ^ ts.tv_sec);
		flag = 1;
	}

    double d = (double)random() /( (double)RAND_MAX + 1.0);
    int ret = (int)((max - min + 1)*d) + min;

    return ret;
}


/**
 * shufflechars
 */

void shuffleChars(char* chars)
{

    int len = strlen(chars);
    int max = len - 1;

	for(int i = 0; i<len; i++)
	{

        int index1 = genRandom(0, max);
        int index2 = genRandom(0, max);
        if(index1 == index2){
	        continue;
        }

        // swap
        char a = chars[index1];
        char b = chars[index2];
        chars[index1] = b;
        chars[index2] = a;

	} // for

}

#endif // _H_SHUFFLE_H_