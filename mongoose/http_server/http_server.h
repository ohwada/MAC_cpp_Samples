#pragma once
/**
 *  http_server.h
 * 2022-06-01 K.OHWADA
 */


// Minimal HTTP server
// refrence : https://mongoose.ws/documentation/#minimal-http-server
// refrence : https://github.com/cesanta/mongoose/blob/master/examples/http-server/main.c

#include "mongoose.h"


// prototype
void run_server(unsigned short port);
 void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
void print_mg_str(char* name, struct mg_str str);


/**
 *  run_server
 */
void run_server(unsigned short port)
{
   char* FORMAT = "http://0.0.0.0:%d";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf((char *)buf, BUFSIZE, (char *)FORMAT, port);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                                      // Init manager
  mg_http_listen(&mgr, (char *)buf, cb, &mgr);  // Setup listener

    printf("listen port: %d \n", port);

  for (;;) mg_mgr_poll(&mgr, 1000);                       // Event loop
  mg_mgr_free(&mgr);                                      // Cleanup
}


/**
 *  print_mg_str
 */
void print_mg_str(char* name, struct mg_str str)
{
   printf("%s: %.*s \n", name, (int)str.len, (char *)str.ptr );
}

