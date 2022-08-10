/**
 *  realloc_two_int_array.c
 * 2022-06-01 K.OHWADA
 */

 // 2-demension int array
// gcc realloc_two_int_array.c

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

	int nn = n+3;
	size_t size = sizeof(int*) * nn;

	int** new = realloc(nums, size);
	if(new == NULL) {
		printf("realloc faild \n");
		return EXIT_FAILURE;
	}


	for(int i = n; i < nn; i++) {
		new[i] = calloc(sizeof(int), m); 
	}

	printf("\n");
	print_nums( new, nn, m);

	for(int i = n; i < nn; i++) {
		for(int j = 0; j < m; j++) {
			new[i][j] = i * m + j;
		} // for j
	} // for i

	printf("\n");
	print_nums( new, nn, m);

	free_nums(new, nn);
 
    return EXIT_SUCCESS;
}


// 0 : 0,1,2,3,4
// 1 : 5,6,7,8,9
// 2 : 10,11,12,13,14
// 3 : 15,16,17,18,19
// 4 : 20,21,22,23,24
// 5 : 25,26,27,28,29


