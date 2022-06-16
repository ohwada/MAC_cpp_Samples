/**
 * sshuffle sample
 * 2022-06-01 K.OHWADA
 */

// test for shuffle.h

#include <stdio.h>
#include "shuffle.h"


/**
 * main
 */
int main(void)
{
	const int BUFSIZE = 20;
	int buf1[BUFSIZE];
	int buf2[BUFSIZE];

    char  str1[] = "0123456789";
    char  str2[] = "abcdefghij";

	const int SIZE = 10;
	for(int i=0; i<SIZE; i++){
		buf1[i] = i;
		buf2[i] = i;
	}

	initRand();

	printf("before: \n");
	dumpInt(buf1, SIZE);
	shuffleInt1(buf1, SIZE);
	printf("shuffleInt1: \n");
	dumpInt(buf1, SIZE);
	shuffleInt2(buf2, SIZE);
	printf("shuffleInt2: \n");
	dumpInt(buf2, SIZE);

	printf("\n");
	printf("before: %s \n", str1);
	shuffleChar1(str1);
	printf(" after: %s \n", str1);

	printf("\n");
	printf("before: %s \n", str2);
	shuffleChar1(str2);
	printf(" after: %s \n", str2);

// before: 0123456789 
//  after: 0458163792 
// 
// before: abcdefghij 
//  after: ghejcafbid 

	return 0;
}

