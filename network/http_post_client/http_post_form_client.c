/**
 * http_form_client.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tcp_client.h"
#include "http_client.h"
#include "request_post_builder.h"
#include "main_proc.h"
#include "json_response_parser.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    const size_t REQ_SIZE = 1024; // 1KB
    char request[REQ_SIZE];
    char response[REQ_SIZE];

    const size_t BUFSIZE = 128;
    char form[BUFSIZE];
    char name[BUFSIZE];
    char age[BUFSIZE];
    char error[BUFSIZE];

    const char NUL = '\0';

    char* host = "postman-echo.com";

    char* path = "/post";

    char* post_data =
    "name=michael&age=30";

    int port = PORT_HTTP;

    const int LOOP = 5;

    bool is_verbose = false;

// create POST request 
    build_http_post_form_request( (char *)host, (char *)path,  (char * )post_data, (char *)request);

    printf("request \n");
    printf("%s \n", (char *)request );
    printf("request size: %zu \n", strlen(request) );


// clear buffer
    memset(response, NUL, BUFSIZE);


    bool ret1 = http_client( (char *)host, port, (char *)request, (char *) response, LOOP, (char *)error, is_verbose );
    if(!ret1){
printf(" http_client failed \n");
            return EXIT_FAILURE;
    }

// prepare a buffer with a size corresponding to the amount of data received
    size_t response_len = strlen(response);
    char body[response_len];
    proc_response2( (char*)response, (char *)body);

    bool ret2 = parse_response_post_form( (char *)body, (char *)form, (char *)name, (char *)age);
    if(!ret2){
        fprintf(stderr, "cannot parse \n");
        return EXIT_FAILURE;
    }

    printf("\n form: %s \n", form);
    printf("name: %s \n", name);
    printf("age: %s \n", age);

    assert(strcmp(name, "michael") == 0);
    assert( strcmp(age, "30") == 0 );

    printf("successful \n");

    return EXIT_SUCCESS;
}


