/**
 * search sample
 * 2020-03-01 K.OHWADA
 */

// finds matched element in an int array using bsearch()
// reference : https://en.cppreference.com/w/c/algorithm/bsearch


#include <stdio.h>
#include "input.h"


/**
 * cmpfunc
*/
int cmpfunc(const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}


/**
 *  dump
 */
void dump(int *ary, size_t len)
{
    for(int i=0; i<len; i++)
    {
        int v = ary[i];
        printf("%d, ", v);
    }
    printf("\n");
}


/**
 *  main
 */
int main(void) 
{

    int data[] = { 5, 20, 29, 32, 63 };

    int num;
     int *item;
 
    size_t len = sizeof(data) / sizeof(data[0]);

    size_t size = sizeof (int);

    dump(data, len);


while(1)
{

    printf("Please enter number \n");
    printf(">"); // prompt

    int ret = getInt(&num);

    if(ret == INPUT_EMPTY){
        break;
    }else if(ret == INPUT_ERROR){
        puts("error");
        continue;
    }
   
       item = (int*) bsearch (&num, data, len, size, cmpfunc);

    if ( item == NULL ) {
            printf("not found: %d \n", num);
    } else {
            int pos = (int)(item - &data[0]);
            printf("found: %d at %d \n", 
            num, pos);
    }

} // while

    return EXIT_SUCCESS;
}



