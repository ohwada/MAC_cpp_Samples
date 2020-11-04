/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// connect HTTP srver using BIO_new_connect

// refrence : https://bg1.hatenablog.com/entry/2017/05/23/210000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>


/**
 * main
 */
int main(int argc, char **argv)
{

    char *host = "example.com";

    if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [host] \n",  argv[0] );
    }


    const size_t URL_SIZE = 100;
    char url[URL_SIZE];

    const int PORT = 80;

    snprintf(url, URL_SIZE, "%s:%d", (char *)host, PORT);


    BIO *bio = NULL;

// open BIO and connect to URL
    bio = BIO_new_connect(url); 

    if(!bio) {
        // failed
        fprintf(stderr, "BIO_new_connect faild: %s \n", url);
        return EXIT_FAILURE;
    }


// success to connect
    fprintf(stderr, "conected: %s \n", url);
    fprintf(stderr, "bio = %08x\n", (int)bio); 


// create GET request 
    const size_t BUFSIZE = 100;
    char buf[100];
    char request[500];

    strcpy(request, "GET / HTTP/1.1\r\n");

    strcat(request, "Accept: */* \r\n");

    snprintf(buf, BUFSIZE, "Host: %s\r\n", (char *)host ); 
    strcat(request, buf); 

   strcat(request, "Connection: close\r\n\r\n"); 

    fprintf(stderr, "%s \n", request);

// calculate request length
  int request_len = strlen(request);


// write request
  int ret1 = BIO_write(bio, request, request_len); 
    fprintf(stderr, "BIO_write: %d \n", ret1);

    const size_t RESPONSE_SIZE = 1024;
    char response[RESPONSE_SIZE ];
    int read_len = RESPONSE_SIZE -1;
    int len;


// resd response
 while((len = BIO_read(bio, response, read_len)) > 0)
{
        // print response
        printf("%s \n", (char *)response); 

} // while 

// close and release BIO
    BIO_free_all(bio);

    return EXIT_SUCCESS;
}


// conected: example.com:80 
// bio = 8fd04080


