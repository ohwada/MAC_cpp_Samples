 /**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// generate random int number using C rand()
// rference : https://9cguide.appspot.com/21-02.html


// Note
// rand() has regularity in the generated random numbers
// C++ suport mt19937 better than rand()


#include <stdlib.h>
#include <time.h>

#ifndef _H_RAND_H_
#define _H_RAND_H_

// prototype
int genRand(int min, int max);


/**
 * genRand
 */
int genRand(int min, int max)
{

	static int flag;
	
	if (flag == 0) {
		srand((unsigned int)time(NULL));
        rand();
		flag = 1;
	}

    double d = (double)rand() /( (double)RAND_MAX + 1.0);
    int ret = (int)((max - min + 1)*d) + min;

    return ret;
}

#endif // _H_RAND_H_
