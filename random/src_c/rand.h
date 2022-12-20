#pragma once
 /**
 * rand.h
 * 2020-03-01 K.OHWADA
 */

// generate random int number using C rand()
// rference : https://9cguide.appspot.com/21-02.html


// Note
// rand () is outdated
// rand() has regularity in the generated random numbers
// random() is recommend 
// https://www.jpcert.or.jp/sc-rules/c-msc30-c.html


#include <stdlib.h>
#include <time.h>

// prototype
void initRand();
double genRand();
int genRandInt(int min, int max);


/**
 * initRand
 */
void initRand()
{
    srand((unsigned int)time(NULL));
}


/**
 * genRand
 */
double genRand()
{
// static variable is cleared to zero
	static int flag;
	
	if (flag == 0) {
        initRand();
        rand();
		flag = 1;
	}

    double d = (double)rand() /( (double)RAND_MAX + 1.0);
    return d;
}


/**
 * genRandInt
 */
int genRandInt(int min, int max)
{
    int ret = (int)((max - min + 1) * genRand()) + min;
    return ret;
}
