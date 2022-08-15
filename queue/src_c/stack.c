/**
 *  stack.c
 * 2022-06-01 K.OHWADA
 */

// gcc stack.c
// reference : https://daeudaeu.com/stack_queue/

#include <stdio.h>

/// Maximum number of data to be managed
#define MAX_NUM 10

 #define EMPTY -1


/**
 * stack structure
 */
typedef struct STACK 
{
// end of data
    int tail;
// Stacked data
    int data[MAX_NUM];
} STACK_T;


// prototype
void initSack(STACK_T*);
void printSack(STACK_T*);
void push(STACK_T*, int);
int pop(STACK_T*);


/**
 * initStack
 */
void initStack(STACK_T *stack)
{
// set stack to empty
    stack->tail = EMPTY;
}


/**
 * push
 */
void push(STACK_T *stack, int input)
{
// if the stack is full, do nothing and exit the function
    if(stack->tail >= MAX_NUM - 1){
        printf("can't push, because stack is full \n");
        return;
    }

// store data one after the end of data
    stack->data[stack->tail + 1] = input;

// move the end of the data back by one
    stack->tail = stack->tail + 1;
}


/**
 * pop
 */
int pop(STACK_T *stack)
{
    int ret = 0;

// if the stack is empty, do nothing and exit the function
    if(stack->tail ==  EMPTY ){
        printf("stack is empty \n");
        return  EMPTY ;
    }

// get data from the end of data
    ret = stack->data[stack->tail];

// move the end of the data forward by one
    stack->tail = stack->tail - 1;

// return the acquired data
    return ret;
}


/**
 * printStack
 */
void printStack(STACK_T *stack){
    int i = 0;

    printf("the left side represents the top of the stack \n");
    for(i = 0; i <= stack->tail; i++){
        printf("%d,", stack->data[stack->tail - i]);
    }
    printf("\n");
}


/**
 * main
 */
int main(void)
{

    STACK_T stack;

// initialize stack
    initStack(&stack);

       push(&stack, 1);
       push(&stack, 2);
       push(&stack, 3);
    printStack(&stack);

    int v1 = pop(&stack);
    if(v1 !=  EMPTY ){
                printf("Popped %d \n", v1);
    }

    int v2  = pop(&stack);
    if(v2 !=  EMPTY ){
                printf("Popped %d \n", v2);
    }

    printStack(&stack);

    return 0;
}


// the left side represents the top of the stack 
// 3,2,1,
// Popped 3 
// Popped 2 
// the left side represents the top of the stack 
// 1,

