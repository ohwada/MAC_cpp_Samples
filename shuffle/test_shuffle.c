/**
 * sshuffle sample
 * 2020-03-01 K.OHWADA
 */

// test for shuffle.h

#include <stdio.h>
#include "shuffle.h"


/**
 * main
 */
int main(void)
{

    char  str1[] = "0123456789";
    char  str2[] = "abcdefghij";

	printf("before: %s \n", str1);
	shuffleChars(str1);
	printf(" after: %s \n", str1);

	printf("\n");
	printf("before: %s \n", str2);
	shuffleChars(str2);
	printf(" after: %s \n", str2);

// before: 0123456789 
//  after: 0458163792 
// 
// before: abcdefghij 
//  after: ghejcafbid 

	return 0;
}

