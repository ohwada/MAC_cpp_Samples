/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// get HTTP page
// save into a local file


#include "url_to_file.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    int const BUFSIZE = 100;
    char url[BUFSIZE];
    char file[BUFSIZE];

    char* host = "localhost";

    if(argc == 2) {
        host = argv[1];
    } else {
        printf("Usage: %s <host>\n", argv[0]);
    }

    snprintf(url, BUFSIZE, "http://%s", host);
    printf("url: %s \n", url);

    snprintf(file, BUFSIZE, "%s_response.txt", host);
    printf("file: %s \n", file);

    int ret = url_to_file(url,  file);
    if(ret != 0){
        return 1;
    }

    printf("saved to: %s \n", file);
    return 0;
}



// * Connected to localhost (::1) port 80 (#0)
// save to: localhost.txt 


