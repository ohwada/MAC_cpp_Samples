#pragma once
/**
 * C sample
 * 2020-07-01 K.OHWADA
 */

 // 2-demension char array

#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

// prototype
char** alloc_chars(int n, int m) ;
void print_chars(char** chars, int n);
void free_chars(char** chars, int n);


/**
 * alloc_chars
 */
char** alloc_chars(int n, int m) 
{
 const char ZERO = '\0';

	char **chars;

// allocate an area to hold addresses for n lines
	chars = calloc(sizeof(char *), n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		chars[i] = calloc(sizeof(char), m); 
// clear to zero with calloc, just in case
		chars[i][0] = ZERO;
	}
 
	return chars;
}


/**
 * print_chars
 */
void print_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
	    printf("%d : %s \n", i, chars[i]);
	} // for i

}


/**
 * free_chars
 */
void free_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
// release Memory 
		free( chars[i] );
	}
	free(chars);
}

