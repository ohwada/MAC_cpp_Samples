/**
 *  queue.c
 * 2022-06-01 K.OHWADA
 */

// gcc queue.c
// reference : https://daeudaeu.com/stack_queue/

#include <stdio.h>


// Maximum number of managed data +1
#define MAX_NUM (10+1)

 #define EMPTY -1


/**
 *  Queue structure
 */
typedef struct QUEUE 
{
// tail of data
    int tail;
// top of data
    int head;
// data queued
    int data[MAX_NUM];
} QUEUE_T;


// prototype
void initSack(QUEUE_T*);
void printSack(QUEUE_T*);
void enqueue(QUEUE_T*, int);
int dequeue(QUEUE_T*);


/**
 *  initQueue
 */
void initQueue(QUEUE_T *queue)
{
// set queue empty
    queue->head = 0;
    queue->tail = EMPTY;
}


/**
 *  enqueue
 */
void enqueue(QUEUE_T *queue, int input)
{
// if the queue is full, do nothing and exit the function
    if((queue->tail + 2) % MAX_NUM == queue->head){
        printf("Queue is full \n");
        return;
    }

// store data one after the end of data
    queue->data[(queue->tail + 1) % MAX_NUM] = input;

// move the end of the data back by one
    queue->tail = (queue->tail + 1) % MAX_NUM;
}


/**
 *  dequeue
 */
int dequeue(QUEUE_T *queue){
    int ret = 0;

// if the queue is empty, do nothing and exit the function
    if((queue->tail + 1) % MAX_NUM == queue->head){
        printf("Queue is empty\n");
        return EMPTY;
    }

// get data from beginning of data
    ret = queue->data[queue->head];

// move the beginning of the data back by one
    queue->head = (queue->head + 1) % MAX_NUM;

// return the acquired data
    return ret;
}


/**
 *  printQueue
 */
void printQueue(QUEUE_T *queue){
    int i = 0;
    int num;

// calculate number of data in queue
    if (queue->tail < queue->head) {
        num = queue->tail + MAX_NUM - queue->head + 1;
    } else {
        num = queue->tail - queue->head + 1;
    }

    printf("the left side represents the exit side of the queue \n");
    for(i = 0; i < num; i++)
{
// display num pieces of data from the beginning of the data
        printf("%d,", queue->data[(queue->head + i) % MAX_NUM]);
} // for
    printf("\n");
}


/**
 *  main
 */
int main(void)
{
    QUEUE_T queue;

// initialize queue
    initQueue(&queue);

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    enqueue(&queue, 4);
    enqueue(&queue, 5);
      printQueue(&queue);

    int v1 = dequeue(&queue);
    if(v1 != EMPTY){
        printf("Dequeue %d \n", v1);
    }

    int v2 = dequeue(&queue);
    if(v2 != EMPTY){
        printf("Dequeue %d \n", v2);
    }

    int v3 = dequeue(&queue);
    if(v3 != EMPTY){
        printf("Dequeue %d \n", v3);
    }

      printQueue(&queue);

   return 0;
}


// the left side represents the exit side of the queue 
// 1,2,3,4,5,
// Dequeue 1 
// Dequeue 2 
//Dequeue 3 
// the left side represents the exit side of the queue 
// 4,5,

