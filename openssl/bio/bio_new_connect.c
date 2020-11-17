/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// connect HTTP srver using BIO_new_connect

// refrence : https://bg1.hatenablog.com/entry/2017/05/23/210000


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bio_func.h"
#include "http_build.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char *host = "example.com";

    int port = PORT_HTTP;


    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
   }  if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [host] [port] \n",  argv[0] );
    }


// build url
    const size_t URL_SIZE = 100;
    char url[URL_SIZE];

    build_url((char *)host, port, (char *)url, URL_SIZE);

  fprintf(stderr, "url: %s \n", url);


    BIO *bio;
    bio = NULL;


    ERR_load_crypto_strings();
 

// open BIO and connect to URL
    bio = BIO_new_connect(url); 

    if(bio){
        fprintf(stderr, "BIO_new_connect: %s \n",  url); 
    } else {
        fprintf(stderr, "BIO_new_connect faild: %s \n",  url); 
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }


// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", request);


// send request
    bool ret1 = send_bio( bio, (char *)request );
    if(!ret1){
        fprintf(stderr, "send_bio failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }


// read response    
    bool ret2 = print_recv_bio( bio );
    if(!ret2){
        fprintf(stderr, "print_recv_bio failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }


// close and release BIO
    BIO_free_all(bio);


   fprintf(stderr, "sucessful \n");

    return EXIT_SUCCESS;


// ----- error -----
label_error:

    if( bio ){
        BIO_free_all(bio);
    }

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;
}


// conected: example.com:80 
// bio = 8fd04080


