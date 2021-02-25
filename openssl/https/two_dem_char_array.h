#pragma once
/**
  * openssl sample
 * 2021-02-01 K.OHWADA
 */

 // 2-demension char array

#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

// prototype
char** alloc_chars(size_t n, size_t m) ;
void print_chars(char** chars, size_t n);
void free_chars(char** chars, size_t n);


/**
 * alloc_chars
 */
char** alloc_chars(size_t n, size_t m) 
{

	char **chars;

// allocate an area to hold addresses for n lines
	chars = malloc(sizeof(char *) * n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		chars[i] = malloc(sizeof(char) * m); 
	    chars[i][0] = '\0';
	}
 
	return chars;
}


/**
 * print_chars
 */
void print_chars(char** chars, size_t n)
{

	for(int i = 0; i < n; i++) {
	    printf("%d : %s \n", i, chars[i]);
	} // for i

}


/**
 * free_chars
 */
void free_chars(char** chars, size_t n)
{

	for(int i = 0; i < n; i++) {
// release Memory 
		free( chars[i] );
	}
	free(chars);
}

