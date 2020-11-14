/**
 * C sample
 * 2020-07-01 K.OHWADA
 */

 // 2-demension int array
// reference :https://www.sejuku.net/blog/24394

#include <stdio.h>
#include <stdlib.h>
 
// prototype
int** alloc_nums(int n, int m) ;
void init_nums(int** nums, int n, int m);
void print_nums(int** nums, int n, int m);
void free_nums(int** nums, int n);


/**
 * alloc_nums
 */
int** alloc_nums(int n, int m) 
{

	int **nums;

// allocate an area to hold addresses for n lines
	nums = malloc(sizeof(int *) * n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		nums[i] = malloc(sizeof(int) * m); 
	}
 
	return nums;
}

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
 * print_nums
 */
void print_nums(int** nums, int n, int m)
{

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {

			if(j == 0) {
				printf("%d : %d,", i, nums[i][j]);
			} else if(j < m -1) {
				printf("%d,", nums[i][j]);
			} else {
				printf("%d\n", nums[i][j]);
			}

		} // for j
	} // for i

}


/**
 * free_nums
 */
void free_nums(int** nums, int n)
{

	for(int i = 0; i < n; i++) {
// release Memory 
		free(nums[i]);
	}
	free(nums);
}


/**
 * main
 */
int main(void) 
{

	int n = 3;
	int m = 5;

	int** nums = alloc_nums(n, m); 

	init_nums(nums, n, m);

	print_nums( nums, n, m);

	free_nums(nums, n);
 
    return EXIT_SUCCESS;
}


// 0 : 0,1,2,3,4
// 1 : 5,6,7,8,9
// 2 : 10,11,12,13,14


