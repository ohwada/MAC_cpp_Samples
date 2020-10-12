/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// get HTTP page
// copy into memory


#include "url_to_memory.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    int const BUFSIZE = 100;
    char url[BUFSIZE];

    struct Memory mem;

    char* host = "localhost";

    if(argc == 2) {
        host = argv[1];
    } else {
        printf("Usage: %s <host>\n", argv[0]);
    }

    snprintf(url, BUFSIZE, "http://%s", host);
    printf("url: %s \n", url);

    int ret = url_to_memory(url, &mem);
    if(ret != 0){
        return 1;
    }

    printMemory(mem);
    return 0;
}


// url: http://localhost 
// ---------- 
// <html><body><h1>It works!</h1></body></html>
// ---------- 


