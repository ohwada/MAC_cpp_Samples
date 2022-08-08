/**
 *  sort_string.c
 * 2022-06-01 K.OHWADA
 */

// gcc sort_string.c
// reference : https://daeudaeu.com/c-qsort/#_qsort-3

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp */


/**
 *  compare
 */
int compare(const void *p1, const void *p2) {
    const char *str1 = p1;
    const char *str2 = p2;

    return strcmp(str1, str2);
}


/**
 *  dump
 */
void dump( char* data, int num, int size)
{
    for (int i = 0; i < num; i++) {
        int pos = size*i;
        printf("%d: %s \n", i, &data[pos]);
    }
    printf("\n");
}


/**
 *  main
 */
int main(void) 
{

const int LEN = 100;
    char data[][LEN] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    int size = sizeof(data[0]);
 	int num = sizeof(data) / size;
	dump( &data[0][0], num, size);

    qsort(&data[0][0], num , size, compare);
    
    dump(&data[0][0], num, size);

    return 0;
}


// 0: Friday 
// 1: Monday 
// 2: Saturday 
// 3: Sunday 
// 4: Thursday 
// 5: Tuesday 
// 6: Wednesday 


