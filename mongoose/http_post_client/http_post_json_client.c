/**
 *  http_post_json_client.c
 * 2022-06-01 K.OHWADA
 */

// Example HTTP POST client
// original : https://github.com/cesanta/mongoose/blob/master/examples/http-client/main.c
'
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "http_client.h"
#include "main_proc.h"
#include "json_response_parser.h"


/**
 *  cb
 */
void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    cb_default(c, ev, ev_data, fn_data);
}


/**
 *  main
 */
int main(int argc, char *argv[]) 
{

    char* url = "http://postman-echo.com/post";

    char* post_data =
  "{ \"name\": \"michael\" \"age\": 30 }";

    if(argc == 3) {
      	url = argv[1];
      	post_data = argv[2];
    } else if(argc == 2) {
      	url = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [url] [postdata] \n",  argv[0] );
    }

    printf("url: %s \n",  url );
    printf("data: %s \n",  post_data );

    bool is_verbose = false;

    http_post_json_client(url, post_data, is_verbose);

// prepare a buffer with a size corresponding to the amount of data received
    size_t response_len = strlen(response);
    char body[response_len];

   proc_response2( (char *)response, (char * )body);

    const size_t BUFSIZE = 128;
    char data[BUFSIZE];

    bool ret1 = parse_response_post_json( (char *)body, (char *)data);
    if(!ret1){
        fprintf(stderr, "cannot parse \n");
        return EXIT_FAILURE;
    }

    printf("\n data: %s \n", data);

    assert(strcmp(data, post_data) == 0);

    printf("successful \n");

    return EXIT_SUCCESS;
}
