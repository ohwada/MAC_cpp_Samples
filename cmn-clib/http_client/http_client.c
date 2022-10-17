/**
 * http_client.c
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmn_http_client.h"
#include "http_client.h"


int main(int argc, char *argv[])
{

    char* host = "example.com";

    int port = PORT_HTTP;


    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] \n",  argv[0] );
    }

    printf("host: %s \n",  host );
    printf("port: %d \n",  port );

    const size_t BUFSIZE = 512;
    char request[BUFSIZE];


// create GET request 
    build_http_root_path_request( (char *)host, (char *)request);

    printf("request \n");
    printf("%s \n", (char *)request );
	printf( "request len: %zu \n", strlen(request) );

    bool is_save_response = true;

    char *body = http_client(host, port, (char *)request, is_save_response );
     if(!body){
            fprintf(stderr, "http_client faild \n");
            return EXIT_FAILURE;
    }

    printf("\n body \n");
	printf( "%s \n", body);
	printf( "body len: %zu \n", strlen(body) );

    bool is_save_verbose = true;

    save_body( body, is_save_verbose);

    free(body);

    return EXIT_SUCCESS;
}

