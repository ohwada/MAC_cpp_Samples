/**
 * system sample
 * 2020-07-01 K.OHWADA
 */

 // get executable path for macOS
// test for executable_path.h
// work  on macOS only

// gcc test_executable_path.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mac_executable_path.h"
#include "str_replace.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    char cmd[100];

    strcpy(cmd, argv[0]);

    printf("cmd: %s\n", cmd);


    char path[100];
    bool ret1 = getExecutablePath( (char *)path );
if(ret1){
    printf("path: %s\n", path);
} else {
    fprintf(stderr, "can not get ExecutablePath \n");
    return EXIT_FAILURE;
}

    const char *replace = "";

    char dir[100];
 
bool ret2 = str_replace(path, cmd, replace, dir );
    if(ret2){
        printf("dir: %s\n", dir);
    }else{
        fprintf(stderr, "can not found %s \n",  cmd);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


 // executable path: /Users/taro/hoge/ 

