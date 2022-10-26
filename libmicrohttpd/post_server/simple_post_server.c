/**
 * index_server.c
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/minimal_example.c

// TODO:
// segmentation fault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "index_html.h"
#include "request_parser.h"
#include "response_builder.h"


/**
 * ahc_echo
 */
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{

    const size_t BUFSIZE = 512;
    char key[BUFSIZE];
    char value[BUFSIZE];
    char msg[BUFSIZE];
    char error[BUFSIZE];

    char* mime = "text/html";

   printf("\n method: %s \n", method);
   printf("upload_data: %s \n", upload_data);



  //static int aptr;

bool is_response = false;

    if( strcmp(method, MHD_HTTP_METHOD_POST) == 0 ) {
        for(int i=0; i<3; i++){
            printf("ptr: %d %s \n", i, ptr[i]);
        }

// TODO:
// segmentation fault
        if( (ptr[6] != NULL)&&(strlen(ptr[6])> 0) ) {
            bool ret = parse_form( ptr[6],  (char *)key, (char *)value );
            if(ret){
                printf("key: %s \n", key);
                printf("value: %s \n", value);
                build_msg_form( (char* )msg, (char *)key, (char *)value );
                is_response = true;
            }
        }
    }

    if(!is_response){
        get_index_html((char *)msg, (char *)error);
    }

    printf("\n response \n");
    printf("%s \n", msg);

    return response_text_copy(connection, msg, mime);
}


/**
 * main
 */
int main (int argc, char *const *argv)
{

    int port = 8080;

    if (argc == 2) {
        port = atoi ( argv[1] );
    } else {
        printf ("%s [port] \n", argv[0]);
    }

    printf ("port: %d \n", port);

    run_server(port);

  return 0;
}
