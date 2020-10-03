/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// read filenames in directory

// reference : https://linuxjm.osdn.jp/html/LDP_man-pages/man3/readdir.3.html

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>  


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    char* path = ".";

    if(argc == 2) {
        path = argv[1];
    }else {
        printf( "Usage: %s [directory path]  \n" , argv[0] );
    }

    const int NUM = 10;
    char buf[NUM][100];

    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        printf ("%s : %s \n", strerror(errno), path);
        return 1;
    }

    struct dirent * ent;
    int cnt = 0;
    while ((ent = readdir (dir)) != NULL) {
        if(cnt < NUM){
            strcpy(buf[cnt], ent->d_name );
        } else {
            break;
        }
        cnt++;
    } 

    closedir (dir);

    for(int i=0; i<cnt; i++){
        printf ("%s \n", buf[i]);
    } 

    return 0;
}


// . 
// .. 
// README.md 
// a.out 
// c_src 
// data 
// src 

