/**
 *  test_two_dem_int_array.c
 * 2020-07-01 K.OHWADA
 */

 // 2-demension int array
// gcc test_two_dem_int_array.c

// reference :https://www.sejuku.net/blog/24394

#include <stdio.h>
#include <stdlib.h>
 #include "two_dem_int_array.h"

// prototype
void init_nums(int** nums, int n, int m);


/**
 * init_nums
 */
void init_nums(int** nums, int n, int m)
{

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
// initialize
			nums[i][j] = i * m + j;
		} // for j
	} // for i

}


/**
 * main
 */
int main(void) 
{

	int n = 3;
	int m = 5;

	int** nums = alloc_nums(n, m); 

// calloc may be clearded to zoro
	print_nums( nums, n, m);

	init_nums(nums, n, m);

	printf("\n");
	print_nums( nums, n, m);

	free_nums(nums, n);
 
    return EXIT_SUCCESS;
}


// 0 : 0,1,2,3,4
// 1 : 5,6,7,8,9
// 2 : 10,11,12,13,14


