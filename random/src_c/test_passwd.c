/**
 * random sample
 * 2022-06-01 K.OHWADA
 */

// generate password with passwd.h


#include<stdio.h>
#include <stdlib.h>
#include "passwd.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

	const char ZERO = '\0';

	const int lower = 2;
	const int upper = 2;
	const int digit = 2;
	const int special = 1;
	const int mix = 2;

	const int BUFSIZE = 128;
	char buf[BUFSIZE];
	buf[0] = ZERO;


    genPasswd(buf, BUFSIZE-1, lower, upper,
digit, special, mix );


	printf("%s \n", buf);

	int len = strlen(buf);
	shuffle( buf, len);

	printf("%s \n", buf);

    return EXIT_SUCCESS;
}

