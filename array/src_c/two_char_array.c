/**
 * two_char_array.c
 * 2020-07-01 K.OHWADA
 */

// gcc two_char_array.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int LEN = 20;


/**
 * dump1
 */
void dump1(char arr[][ LEN], int num) 
{
    printf("dump1: num=%d \n", num);
  for (int i = 0; i < num; i++) {
      printf("%s \n ", arr[i]);
    } // for i
      printf("\n");
}


/**
 * dump2
 */
void dump2(char *arr, int num, int size) 
{
    printf("\n dump2: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {        
        int pos = i * size;
        printf("%s \n", &arr[pos]);
  } // for i
    printf("\n");
}


/**
 * dump3
 */
void dump3(int num, int size, char arr[num][size]) 
{
    printf("\n dump3: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {
      printf("%s \n", arr[i]);
    } // for i
    printf("\n");
}


/**
 * dump4
 */
void dump4(char **arr, int num, int size) 
{
    printf("\n dump4: num=%d size=%d \n", num, size);
  for (int i = 0; i < num; i++) {
      printf("%s \n", arr[i]);
    } // for i
    printf("\n");
}


/**
 * main
 */
int main(void) 
{
    char arr[][LEN] = {"Sierra", "Mojave", "Catalina" };

    int num = sizeof(arr)/sizeof(arr[0]);
    dump1(arr, num); 

    int size = sizeof(arr[0]);
    dump2(&arr[0][0], num, size); 

    dump3(num, size, arr); 

// Use malloc to create a two-dimensional structure
  int lines = sizeof(arr) / sizeof(char) / LEN;
  char **mem = malloc(lines * sizeof(char *));
  for (int i = 0; i <lines; i++) {
    mem[i] = malloc(LEN * sizeof(char));
      strcpy( mem[i], arr[i]);
  }// for i

   dump4(mem, num, size); 

// free memory
    for (int i = 0; i < lines; i++) {
        free(mem[i]);
    } // for i
    free(mem);

    return 0;
}


// Sierra 
// Mojave 
// Catalina 


