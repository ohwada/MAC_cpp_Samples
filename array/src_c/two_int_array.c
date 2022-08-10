/**
 * two_int_array.c
 * 2022-06-01 K.OHWADA
 */

// gcc two_int_array.c
// reference : https://qiita.com/t-yama-3/items/e3304cc4dce2193f9300

#include <stdio.h>
#include <stdlib.h>


const int LEN = 5;


/**
 * dump1
 */
void dump1(int arr[][ LEN], int num) 
{
    printf("dump1: num=%d \n", num);
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < 5; j ++) {
      printf("%d ", arr[i][j]);
    } // for j
    printf("\n");
  } // for i
}


/**
 * dump2
 */
void dump2(int *arr, int num, int size) 
{
    printf("\n dump2: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < size; j ++) {
        int pos = i * size + j;
        printf("%d ", arr[pos]);
    } // for j
    printf("\n");
  } // for i
}


/**
 * dump3
 */
void dump3(int num, int size, int arr[num][size]) 
{
    printf("\n dump3: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {
    for (int j = 0; j <size; j ++) {
      printf("%d ", arr[i][j]);
    } // for j
    printf("\n");
  } // for i
}

/**
 * dump4
 */
void dump4(int **arr, int num, int size) 
{
    printf("\n dump4: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {
    for (int j = 0; j <size; j ++) {
      printf("%d ", arr[i][j]);
    } // for j
    printf("\n");
  } // for i
}


/**
 * main
 */
int main(void) 
{
  int arr[][ LEN] = {
    { 32, 4, 78, 34, 64 },
    { 74, 5, 66, 36, 42 },
    { 56, 13, 55, 3, 81 },
    { 7, 56, 33, 83, 4 },
    { 32, 85, 50, 24, 39 },
    { 16, 24, 56, 43, 6 },
    { 75, 35, 27, 34, 83 },
    { 69, 41, 62, 2, 88 }
  };


	int num = sizeof(arr)/sizeof(arr[0]);
 	dump1(arr, num);

	int size = sizeof(arr[0])/sizeof(arr[0][0]);
 	dump2(&arr[0][0], num, size);

    dump3(num, size, arr);

  // Use malloc to create a two-dimensional structure
  int lines = sizeof(arr) / sizeof(int) / LEN;
  int **mem = malloc(lines * sizeof(int *));
  for (int i = 0; i <lines; i++) {
    mem[i] = malloc(LEN * sizeof(int));
    for (int j = 0; j <LEN; j++) {
      mem[i][j] = arr[i][j];
    } // for j
  }// for i

    dump4(mem, lines, LEN);

// free memory
    for (int i = 0; i < lines; i++) {
        free(mem[i]);
    } // for i
    free(mem);

  return 0;
}


// dump1: num=8 
// 32 4 78 34 64 
// 74 5 66 36 42 

