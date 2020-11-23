#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

 // 2-demension char array

#include <stdio.h>
#include <string.h>

// prototype
char** alloc_chars(int n, int m) ;
void free_chars(char** chars, int n);
void print_chars(char** chars, int n);


/**
 * alloc_chars
 */
char** alloc_chars(int n, int m) 
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


/**
 * print_chars
 */
void print_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
	    printf("%d : %s \n", i, chars[i]);
	} // for i

}