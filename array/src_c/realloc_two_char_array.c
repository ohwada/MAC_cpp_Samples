/**
 *  realloc_two_char_array.c
 * 2022-06-01 K.OHWADA
 */

 // 2-demension char array
// gcc realloc_two_char_array.c

#include <stdio.h>
#include <stdlib.h>
#include "two_dem_char_array.h"

// prototype
 void init_chars(char** chars);


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
 * main
 */
int main(void) 
{

	const int N = 5;
	const int M = 20;

	char** chars = alloc_chars( N, M ); 

// calloc may be clearded to zoro
    print_chars( chars, N );

    init_chars(chars);

    printf("\n");
	print_chars( chars, N );

int nn = N+4;
	size_t size = sizeof(char*) * nn;

	char** new = realloc( chars, size);
	if(new == NULL) {
		printf("realloc faild \n");
		return EXIT_FAILURE;
	}


	for(int i = N; i < nn; i++) {
		new[i] = calloc(sizeof(char), M); 
	}

	printf("\n");
	print_chars( new, nn);

    strcpy( new[5], "Big Sur");
    strcpy( new[6], "Monterey");
    strcpy( new[7], "Ventura");

	printf("\n");
	print_chars( new, nn);

	free_chars(new, nn);


    return EXIT_SUCCESS;
}


// 0 :  
// 1 : Sierra 
// 2 : Mojave 
// 3 : Catalina 
// 4 :  
// 5 : Big Sur 
// 6 : Monterey 
// 7 : Ventura 
// 8 : 

