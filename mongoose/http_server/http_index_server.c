/**
 *  http_index_server.c
 * 2022-06-01 K.OHWADA
 */


// Minimal HTTP server
// https://mongoose.ws/documentation/#minimal-http-server

#include "http_server.h"


/**
 *  cb
 */
void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
  if (ev == MG_EV_HTTP_MSG) {
// request
    printf("\n request \n");
    printf("%s \n", c->recv.buf);
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    print_mg_str("method",  hm->method);
    print_mg_str("uri",  hm->uri);

// response
    char* file = (char *)"data/index.html";
    struct mg_http_serve_opts opts = {};
    mg_http_serve_file(c, hm, file, &opts);
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
