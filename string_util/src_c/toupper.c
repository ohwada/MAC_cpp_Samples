/*
 *  toupper.c
 * 2022-06-01 K.OHWADA 
*/

#include <stdio.h>
#include <ctype.h>
#include "split.h"


/*
 * main
*/
int main()
{

char *text = "hello world goodby japan";
char* delim = " "; 

size_t num = 20;
    size_t len = 256;
	char word[len];

    char** result = alloc_chars(num, len) ;

	printf("%s \n", text);

    size_t size = split(text, delim, result, num);

for(int i=0; i<size; i++){
	strcpy(word, result[i]);
	word[0] = toupper(word[0]);
	printf("%s ", word);
}
	printf("\n");

	return 0;
}

// Hello World Goodby Japan

