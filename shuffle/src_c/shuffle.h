#pragma once
/**
 * sshuffle sample
 * shufle with C random()
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <string.h>
#include <time.h>


// prototype
void initRand();
void shuffleInt1( int array[], int size);
void shuffleInt2( int array[], int size);
void shuffleChar1( char *str);
void dumpInt( int array[], int size);
int genRandInt(int min, int max);


/**
 * initRand
 */
void initRand()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srandom(ts.tv_nsec ^ ts.tv_sec);
}


/**
 * shuffleInt1
 */
 // reference: http://shopping2.gmobb.jp/htdmnr/www08/c01/algorithm/shuffle.c
void shuffleInt1( int array[], int size) {
    for(int i = 0; i < size; i++) {
        int j = random()%size;
       if(i != j){
            // swap
            int t = array[i];
            array[i] = array[j];
            array[j] = t;
        }
    } // for
}


/**
 * shuffleInt2
 */
// reference : http://www5.airnet.ne.jp/tomy/cpro/ra4.htm
void shuffleInt2(int array[], int size)
{
    int max = size -1;
 	for(int i = 0; i<size; i++)
	{
        int j = genRandInt(0, max);
        int k= genRandInt(0, max);
       if(j != k){
            // swap
            int t = array[k];
            array[k] = array[j];
            array[j] = t;
        }
	} // for
}


/**
 * shuffleChar1
 */
void shuffleChar1( char *str) 
{
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        int j = random()%len;
        if(i != j){
            // swap
            char t = str[i];
            str[i] = str[j];
            str[j] = t;
        }
    } // for
}


/**
 * dumpInt
 */
void dumpInt( int array[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}


/**
 * genRandInt
 */
int genRandInt(int min, int max)
{
    double d = (double)random() /( (double)RAND_MAX + 1.0);
    int ret = (int)((max - min + 1)*d) + min;
    return ret;
}

