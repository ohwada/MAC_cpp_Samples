/**
 * sort_array.c
 * 2022-06-01 K.OHWADA
 */

// gcc sort_array.c
// reference : https://monozukuri-c.com/langc-funclist-qsort/

#include <stdio.h>
#include <stdlib.h>


/**
 *  comp_int
 */
int comp_int(const void * a, const void * b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


/**
 *  dump
 */
void dump(int* data, int size)
{

    for (int i = 0; i < size; i++) {
        printf("%2d, ", data[i]);
    }
    printf("\n");
}


/**
 *  main
 */
int main(void)
{

	int data[] = { 60, 10, 50, 30, 80, 40 ,20, 90, 70 , 0};

    int size = sizeof(data) / sizeof(data[0]);

	dump(data, size);

	qsort(data, size, sizeof(int), comp_int);

	dump(data, size);

	return 0;
}

