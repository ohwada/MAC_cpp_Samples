#pragma once
/**
 * two_dem_int_array.h
 * 2020-07-01 K.OHWADA
 */

 // 2-demension int array
// reference :https://www.sejuku.net/blog/24394

 
// prototype
int** alloc_nums(int n, int m) ;
void print_nums(int** nums, int n, int m);
void free_nums(int** nums, int n);


/**
 * alloc_nums
 */
int** alloc_nums(int n, int m) 
{

	int **nums;

// allocate an area to hold addresses for n lines
	nums = calloc(sizeof(int*), n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		nums[i] = calloc(sizeof(int), m); 
	}
 
	return nums;
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
