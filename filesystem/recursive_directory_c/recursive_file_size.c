/**
 * recursive_file_size.c
 * 2022-06-01 K.OHWADA
 */

 // Computing the size of a directory
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter04/problem_35/main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file_list.h"
#include "file_util.h"


/**
 * get_directory_size
 * call recursively
 */
int r_get_directory_size(
   char *dir, int depth)
{
printf("\n dir: %s : depth = %d \n", dir, depth);

const int BUFSIZE = 256;
char error[BUFSIZE];
char path[BUFSIZE];

    if(!is_dir(dir)){
        printf("not dir: %s \n", dir);
        return 0;
    }


int num;
int list_size;

char** list = get_file_list(dir, &num, &list_size, error );

if(num == 0){
    printf("%s \n",error);
    return 0;
}

if(list_size == 0){
    return 0;
}


int sum = 0;

for(int i=0; i<list_size; i++)
{
  printf("%d-%d: %s \n", depth, i, list[i]);
    make_path(path, dir, list[i]);

    if( is_dir(path) ){
    sum += r_get_directory_size( path, depth+1);
    } else if( is_file(path) ) {
        sum += get_file_size(path);
    }
} // for

free_chars(list, num);

return sum;
}


/**
 * main
 */
int main(int argc, char *argv[])
{

    char *path = ".";

   if(argc == 2) {
      	path = argv[1];
    } else {
        printf("Usage: %s  [path] \n",  argv[0] );
    }

    printf("path: %s \n",  path );

    int size = r_get_directory_size(path, 0);
    printf("Size: %d \n", size );

    return 0;
}


//  dir: ./test : depth = 1 
// 1-0: wct123.txt 
// 1-1: .DS_Store 
// 1-2: wctABC.tmp 
// 1-3: 1st
// Size: 189818

