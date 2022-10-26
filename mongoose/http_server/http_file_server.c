/**
 *  http_file_server.c
 * 2022-06-01 K.OHWADA
 */


// Minimal HTTP server
// reference : https://mongoose.ws/documentation/#minimal-http-server

#include "http_server.h"

const char* ROOT_DIR = "www";


/**
 *  cb
 */
void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{

  if (ev == MG_EV_HTTP_MSG) {
// request
    // printf("\n request \n");
    // printf("%s \n", c->recv.buf);
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        print_mg_str("method",  hm->method);
        print_mg_str("uri",  hm->uri);
// Serve files
        struct mg_http_serve_opts opts = 
        {.root_dir = (char *)ROOT_DIR };
// From root_dir
        mg_http_serve_dir(c, hm, &opts);
    }

}


/**
 *  main
 */
int main(int argc, char *argv[])    
{

    unsigned short port = 8000;

    run_server(port);

    return 0;
}
