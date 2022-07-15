/**
 *  callback_func.c
 * 2022-06-01 K.OHWADA
 */


// reference : https://qiita.com/pocket8137/items/df5afba90b51e90587a5


#include<stdio.h>


/**
 *   typedef 
 */
typedef void (* FUNC_POINTER)(char *); 


/**
 *  callback function 1
 */
void callback1(char *s)
{
    printf("%s\n", s);
}


/**
 *  callback function 2
 */
void callback2(char *s)
{
    printf("[ %s ]\n", s);
}


/**
 * function that calls callback function
 */
void func(char *s, FUNC_POINTER p)
{
    // call the callback function
    p(s);
}


/**
 *   main
 */
int main()
{
    FUNC_POINTER p;

    p = callback1;
    func("callback func 1",p);

    p = callback2;
    func("callback func 2",p);

    return 0;
}

// callback func 1
// [callback func 2]