 /**
 * C sample
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
int genRandom(int min, int max);


/**
 * genRandom
 */
int genRandom(int min, int max)
{

	static int flag;
	
	if (flag == 0) {
		srand((unsigned int)time(NULL));
        rand();
		flag = 1;
	}

	int ret = min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));

    return ret;
}

#endif // _H_RAND_H_
