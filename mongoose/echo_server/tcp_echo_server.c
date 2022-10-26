/**
 *  tcp_echo_server.c
 * 2022-06-01 K.OHWADA
 */

// reference : Minimal TCP echo server
// https://mongoose.ws/documentation/#minimal-tcp-echo-server

#include "mongoose.h"


/**
 * cb
 */
static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    if (ev == MG_EV_READ) {
        printf("r: %s \n", c->recv.buf);
        mg_send(c, c->recv.buf, c->recv.len);     // Echo received data back
        mg_iobuf_del(&c->recv, 0, c->recv.len);   // And discard it
    }
}


/**
 *  run_server
 */
void run_server(unsigned short port)
{
   char* FORMAT = "tcp://0.0.0.0:%d";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf((char *)buf, BUFSIZE, (char *)FORMAT, port);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                                // Init manager
  mg_listen(&mgr, (char *)buf, cb, &mgr);  // Setup listener

printf("listen port: %d \n", port);

  for (;;) mg_mgr_poll(&mgr, 1000);                 // Event loop
  mg_mgr_free(&mgr);                                // Cleanup
}


/**
 *  main
 */
int main(int argc, char *argv[]) 
{

    unsigned short port = 1234;

    run_server(port);

  return 0;
}

