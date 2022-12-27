 #pragma once
/**
 * random sample
 * 2020-03-01 K.OHWADA
 */


// generate random number using C random()
// since C11
// reference : https://www.jpcert.or.jp/sc-rules/c-msc30-c.html
// https://linuxjm.osdn.jp/html/LDP_man-pages/man3/random.3.html
// Note:
// if You wnat to compile with g++
// c++17 is required
// https://en.cppreference.com/w/cpp/chrono/c/timespec_get

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
    struct timespec ts;
     timespec_get(&ts, TIME_UTC);
    srandom(ts.tv_nsec ^ ts.tv_sec);
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
		flag = 1;
	}

    double d = (double)random() /( (double)RAND_MAX + 1.0);
    return d;
}


/**
 * genRanInt
 */
int genRandInt(int min, int max)
{
    int ret = (int)((max - min + 1) * genRand() ) + min;
    return ret;
}

