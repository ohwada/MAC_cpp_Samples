/*
 * test_trim.c
 * 2022-06-01 K.OHWADA 
*/

#include <stdio.h>
#include "trim.h"


/*
 * main
*/
int main()
{
   char* text = "\n\t Hello World  \r\n";

    size_t len = strlen(text);
    char result[len];

    printf("|%s| \n", text);

    trim(text, result); 

    printf("|%s| \n", result);
}
