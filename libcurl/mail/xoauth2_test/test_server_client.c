/**
 * test_server_client.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tcp_client.h"
#include "http_client.h"
#include "file_util.h"
#include "../xoauth2/config.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    const char CRLF[] = "\r\n";

    const char NUL = '\0';

    const size_t BUFSIZE = 1024;
    char request[BUFSIZE];
    char response[BUFSIZE];
    char header[BUFSIZE];
    char body[BUFSIZE];
    char error[BUFSIZE];

memset( (char *)response, NUL, BUFSIZE);

    const int MAX = 3;

    char* host = "localhost";

    char *file = "sample/sample_server_request.txt";

    char* expect = "<html><head></head><body><h1>Local Server</h1><font size='+2'>code<br/>|4/0dummy-code| <br/>scope<br/>|dummy-scope|<br/></font></body></html>";

    bool is_verbose = false;

    bool ret1 = file_text_read2(file, (char *)request, (char *)error);
    if(!ret1){
            fprintf(stderr, "file_text_read failed: %s \n", error);
            return EXIT_FAILURE;
    }

    strcat(request, CRLF);

    printf("\nrequest \n");
    printf("%s \n", request );

    bool ret2 = http_client(host, PORT, (char *)request, (char *)response, MAX, (char *)error, is_verbose );
    if(!ret2){
            fprintf(stderr, "http client failed: %s \n", error);
            return EXIT_FAILURE;
    }

    printf("\n response \n");
    printf("%s \n", response );

bool ret3 = split_header_body( (char *)response, (char *)header, (char *)body);

  if(!ret3){
            fprintf(stderr, "cannot split_header_body \n");
            return EXIT_FAILURE;
    }

    printf("\n body \n");
    printf("%s \n", body );

    assert( strcmp(body, expect) == 0 );

    printf("successful \n");

    return EXIT_SUCCESS;
}

