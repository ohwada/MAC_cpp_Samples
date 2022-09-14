/*
 * test_split.h
 * 2022-06-01 K.OHWADA 
*/

#include <stdio.h>
#include "split.h"


/*
 * main
*/
int main(void)
{

    char* text = "The quick brown fox jumps over the lazy dog";
    char* delim = " "; 

    size_t num = 20;
    size_t len = 256;
    char** result = alloc_chars(num, len) ;

    printf("%s \n", text);

    size_t result_size = split(text, delim, result, num);

    print_chars(result,  result_size);

    free_chars(result, num);

    return 0;
}

// 0 : The 
// 1 : quick 
// 2 : brown 
// 3 : fox 
// 4 : jumps 
// 5 : over 
// 6 : the 
// 7 : lazy 
// 8 : dog 

