/**
 *  thread.c
 * 2022-06-01 K.OHWADA
 */

// gcc thread.c -lpthread
// calculates the 40th power of 40 integers from 0 to 39 and stores the result in an array
// reference : https://daeudaeu.com/multithread/

#include <stdio.h>
#include <pthread.h>

#define NUM 40
#define NUM_THREAD 2


/**
 *  struct data
 * a structure that stores data necessary for thread execution
 */
struct data {
    int start;
    int num;
    int* result;
};


// prototype
void *func(void *arg);


/**
 *  func
 * what to do with threads
* @arg: information necessary for thread (work)
 */
void *func(void *arg){
    int i;
    struct data *pd = (struct data *)arg;

// process based on information specified in arg
    for(i = pd->start; i < pd->start + pd->num; i++){
        pd->result[i] = i * i * i * i;
    } // for

    return NULL;
}


/**
 *  dump
 */
void dump(  struct data d, int max)
{
   int* r = d.result;
for(int i=0; i<max; i++)
{
    printf("%d \n", r[i]);
} // for
    printf("\n");
}


/**
 *  main
 */
int main(void)
{
const int MAX = 10;

//an array to store the results
    int r[NUM] = {0};

// an array to store the threads
    pthread_t t[NUM_THREAD];
    
// an array that stores information necessary for thread execution
    struct data d[NUM_THREAD];

// store the information necessary for executing the first thread

// starting number
    d[0].start = 0; 
// number of times to do the calculation
    d[0].num = NUM / 2; 
// address to store 
    d[0].result = r; 

// create the first thread
    pthread_create(&t[0], NULL, func, &d[0]);

// stores information necessary for executing the second thread
    d[1].start = NUM / 2;
    d[1].num = NUM / 2; 
    d[1].result = r; 

// create a second thread
    pthread_create(&t[1], NULL, func, &d[1]);

// wait for thread to finish
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);

    printf("thread 0 \n");
    dump(d[0],  MAX);

    printf("thread 1 \n");
    dump(d[1],  MAX);

    return 0;
}

// thread 0 
// 0 
// 1 
// 16 

