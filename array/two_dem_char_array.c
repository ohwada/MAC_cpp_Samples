/**
 * C sample
 * 2020-07-01 K.OHWADA
 */

 // 2-demension char array

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
char** alloc_chars(int n, int m) ;
void init_chars(char** chars);
void print_chars(char** chars, int n);
void free_chars(char** chars, int n);


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
 * init_chars
 */
void init_chars(char** chars)
{
    strcpy( chars[1], "Sierra");
    strcpy( chars[2], "Mojave");
    strcpy( chars[3], "Catalina");
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


/**
 * main
 */
int main(void) 
{

	int n = 5;
	int m = 20;

	char** chars = alloc_chars(n, m); 

    init_chars(chars);

	print_chars( chars, n);

	free_chars(chars, n);
 
    return EXIT_SUCCESS;
}


// 0 :  
// 1 : Sierra 
// 2 : Mojave 
// 3 : Catalina 
// 4 :  


