/*
 * split.h
 * 2022-06-01 K.OHWADA 
*/

// reference : https://programming-place.net/ppp/contents/c/rev_res/string015.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
size_t split(char* str, const char* separator, char** result, size_t result_size);
char** alloc_chars(int n, int m) ;
void print_chars(char** chars, int n);
void free_chars(char** chars, int n);


/*
 * split
* @return : number of strings after division
*/
size_t split(char* s, const char* separator, char** result, size_t result_size)
{
    const char NUL = '\0';

    if(s == NULL) return 0;
    if(separator == NULL) return 0;
    if(result == NULL) return 0;
    if(result_size == 0) return 0;

    size_t s_len = strlen(s);
    char str[s_len];
    strcpy(str, s); 

    size_t start = 0;
    size_t end = 0;
    size_t len = 0;
    size_t cnt = 0;

    do {
// find out how many consecutive non-delimiter characters,
// add to variable end.
// there is a delimiter in the position after the addition.

        len = strcspn(&str[start], separator); 
        end = start + len; 
      
// overwrite delimiter with null character
         str[end] = NUL;


// store the start address of the string after division in result
        if(cnt < result_size) {
            strcpy( result[cnt], &str[start]);
            cnt ++;
        }
           
// set next position to check
        start = end + 1;

    } while (start <= s_len);
// if s ends with a delimiter,
// to make it consider that there is an empty string at the end,
// we need to continue the loop when start == s_len

    return cnt;
}


/**
 * alloc_chars
 */
char** alloc_chars(int n, int m) 
{

	char **chars;

// allocate an area to hold addresses for n lines
	chars = calloc(sizeof(char *), n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		chars[i] = calloc(sizeof(char), m); 
// clear to zero with calloc
// You can comment out
		// chars[i][0] = ZERO;
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

