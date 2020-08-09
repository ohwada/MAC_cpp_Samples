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

#ifndef _H_RANDOM_H_
#define _H_RANDOM_H_

// prototype
int genRandom(int min, int max);


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

#endif // _H_RANDOM_H_