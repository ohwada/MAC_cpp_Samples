/**
 * menu sample
 * 2020-07-01 K.OHWADA
 */


// test for printMenu

#include <stdio.h>
#include "menu.h"


/**
 * main
 */
int main(void)
{

    const size_t SIZE = 3;
    const size_t LEN = 10; 

    char** list = alloc_chars(SIZE, LEN);

    strcpy(list[0], "foo");
   strcpy(list[1], "bar");
   strcpy(list[2], "fiz");

    int empty = -1;

while(1)
{
    printf("\n");
    int choice = printMenu( list, SIZE, empty );
    printf("choice: %d \n", choice );
    if(choice == empty){
        printf("empty \n");
    } else if(choice == 0){
        bool ret1 = getEnterYn("quit?");
        if(ret1){
            printf("goodby \n");
            break;
        }
    }

    bool ret2 = checkNumber( choice, 0, SIZE );
    if(!ret2){
        printf("out of range: %d \n", choice);
    }

    int index = choice - 1;
    if ((index >=0 )&&(index < SIZE)) {
        printf("item: %s \n", list[index]);
    }

} // while

    bool ret3 = hitEnterKey();
    if(ret3){
        printf("hitEnterKey \n");
    }

    return EXIT_SUCCESS;
}


// 0 quit 
// 1 foo
// 2 bar
//3 fiz
// [ 0 - 3] 

