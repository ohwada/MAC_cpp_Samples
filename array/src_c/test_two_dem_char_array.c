/**
 * test_two_dem_char_array.c
 * 2020-07-01 K.OHWADA
 */

 // 2-demension char array
// gcc test_two_dem_char_array.c

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

	free_chars(chars, N );
 
    return EXIT_SUCCESS;
}


// 0 :  
// 1 : Sierra 
// 2 : Mojave 
// 3 : Catalina 
// 4 :  


