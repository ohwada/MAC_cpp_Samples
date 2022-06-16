 /**
* printf.c 
 * Sample of variable length arguments 
* 2022-06-01 K.OHWADA 
 */

// refference: https://ez-net.jp/article/E3/CQ4fxR9H/br4mR3gSb_sE/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


/**
 *  printF
 * function like printf
 * that  have variable length arguments
 */
void printF(char *format, ...)
{
const int BUFSIZE = 128;
char buf[BUFSIZE];

va_list ap;

va_start(ap, format);

vsprintf(buf, format, ap);

va_end(ap);

printf("%s", buf);
}


/**
 * main
 */
int main()
{

	char s[] = "abc";
	int d = 123;
	float f = 3.14;

	printF("%s, %d, %f \n", s, d, f);

	return 0;
}

// abc, 123, 3.140000 

