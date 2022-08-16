/**
 * quicksort.c
 * 2022-06-01 K.OHWADA
 */

// gcc  quicksort.c
// reference : https://qiita.com/omu58n/items/7794f097b2c569a469bc

#include<stdio.h>
#include <stdlib.h>
#include "random.h"

void swap (int *a, int *b);
int partition (int array[], int left, int right);
void r_quicksort (int array[], int left, int right); 
void quicksort(int array[], int size) ;
int comp(const void * a, const void * b);
double calc_duration( struct timespec start_time, struct timespec end_time);


/**
 * swap
 */
void swap (int *a, int *b) 
{
  int tmp;  
  tmp = *a;
  *a = *b;
  *b = tmp;
}


/**
 * partition
 */
int partition (int array[], int left, int right) 
{
  int i, j, pivot;
  i = left;
  j = right + 1;
  pivot = left;

  do {
    do { i++; } while (array[i] < array[pivot]);
    do { j--; } while (array[pivot] < array[j]);

    if (i < j) {
        swap(&array[i], &array[j]); 
    }

  } while (i < j);

  swap(&array[pivot], &array[j]);

  return j;
}


/**
 * r_quicksort
* recursible call
 */
void r_quicksort(int array[], int left, int right) 
{
  int pivot;

  if (left < right) {
    pivot = partition(array, left, right);
    r_quicksort(array, left, pivot-1);       
    r_quicksort(array, pivot+1, right);
  }

}

/**
 * quicksort
 */
void quicksort(int array[], int size) 
{
    r_quicksort(array, 0, size-1) ;
}


/**
 *  dump
 */
void dump(int data[], int size)
{

    for (int i = 0; i < size; i++) {
        printf("%2d, ", data[i]);
    }
    printf("\n");
}

/**
 *  comp
 */
int comp(const void * a, const void * b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


/**
 * calc_duration
 */
double calc_duration( struct timespec start_time, struct timespec end_time)
{
    unsigned int  sec = end_time.tv_sec - start_time.tv_sec;
    int nsec = end_time.tv_nsec - start_time.tv_nsec;
    double dsec = (double)sec
        + (double)nsec / (1000 * 1000 * 1000);
    double msec = 1000 * dsec;
    return msec;
}


/**
 *  main
 */
int main (void) 
{
     const int BUFSIZE = 1000;
       int d1[BUFSIZE];
      int d2[BUFSIZE];

     int v[]={ 9, 1, 5, 3, 8, 6, 2, 7, 4, 0 };
    int size = sizeof(v) / sizeof(v[0]);

	dump(v, size);
  quicksort(v, size);
	dump(v, size);

initRand();

for(int i=0; i<BUFSIZE; i++)
{
    int d = genRandInt(1, BUFSIZE);
    d1[i] = d;
    d2[i] = d;
}

struct timespec start_time, end_time;

clock_gettime(CLOCK_REALTIME, &start_time);

  quicksort(d1, BUFSIZE);

clock_gettime(CLOCK_REALTIME, &end_time);

  double msec = calc_duration(start_time, end_time);

      printf("time: %f ms \n",  msec );

struct timespec start_time2, end_time2;

clock_gettime(CLOCK_REALTIME, &start_time2);

	qsort(d2, BUFSIZE, sizeof(int), comp);

clock_gettime(CLOCK_REALTIME, &end_time2);

  double msec2 = calc_duration(start_time2, end_time2);

printf("time: %f ms \n",  msec2 );

for(int i=0; i<BUFSIZE; i++)
{
    if(d1[i] != d2[i]){
        printf("unmatch \n");
        return 1;
    }
}

    printf("successful \n");

  return 0;
}

 // 9,  1,  5,  3,  8,  6,  2,  7,  4,  0, 
 // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 
// time: 0.100000 ms 
// time: 0.135000 ms 
// successful

