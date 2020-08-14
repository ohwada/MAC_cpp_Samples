/**
 * sort sample
 * 2020-03-01 K.OHWADA
 */

// sorts the array in ascending order using qsort()
// reference : https://en.cppreference.com/w/c/algorithm/qsort


 #include <stdio.h>
#include <stdlib.h>


/**
 *  compare_int
 */
int compare_int(const void* a, const void* b)
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
void dump(int* data, int len)
{

    for (int i = 0; i < len; i++) {
        printf("%2d, ", data[i]);
    }
    printf("\n");
}


/**
 *  main
 */
int main(void)
{

    int data[] = {4, 2, 3, 6, 3, 2, 1, 3, 7, 5};

    size_t len = sizeof(data) / sizeof(data[0]);

    printf("brfore: \n");
    dump(data, len);

    qsort(data, len, sizeof(int), compare_int);

    printf("after: \n");
    dump(data, len);

// brfore: 
// 4,  2,  3,  6,  3,  2,  1,  3,  7,  5, 
// after: 
// 1,  2,  2,  3,  3,  3,  4,  5,  6,  7, 

    return EXIT_SUCCESS;
}

