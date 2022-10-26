/**
 *  http_client.c
 * 2022-06-01 K.OHWADA
 */

// Example HTTP client
// original : https://github.com/cesanta/mongoose/blob/master/examples/http-client/main.c

#include "http_client.h"
#include "main_proc.h"


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
    char *url = "http://example.com";

    if(argc == 2) {
      	url = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [url] \n",  argv[0] );
    }

    printf("url: %s \n",  url );

    bool is_verbose = false;

    http_client(url, is_verbose);

    proc_response1( (char* )response);

    return EXIT_SUCCESS;
}
