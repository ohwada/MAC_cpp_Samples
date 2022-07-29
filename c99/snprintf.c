/**
 * snprintf.c
 * 2022-06-01 K.OHWADA
 */

// gcc snprintf.c
// reference : https://www.buildinsider.net/language/clang/01

#include <stdio.h>


/**
 * foo
 */
void foo(const char *p, int i) 
{
 	char buf[16];
 	snprintf(buf, sizeof(buf), "%s %d", p, i);
	printf("buf: %s \n", buf);
}


/**
 * main
 */
int main()
{
	foo("hello", 10); 
    return 0;
}

// buf: hello 10 

