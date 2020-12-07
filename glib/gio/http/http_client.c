/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Server

// reference : https://stackoverflow.com/questions/9513327/gio-socket-server-client-example/10085464#10085464

#include <stdio.h>
#include <stdlib.h>
#include "http_client.h"
#include "gio_stream.h"


/**
 * main
 */
int main (int argc, char *argv[])
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
  
    char request[1024];
    build_http_root_path_request( (char *)host, (char *)request );

printf("%s \n", request);

  GError * err = NULL;

  /* create a new connection */
  GSocketConnection * connection = NULL;

  GSocketClient * client = g_socket_client_new();

  /* connect to the host */
  connection = g_socket_client_connect_to_host(client,
                                               (gchar*) host,
                                                port, /* your port goes here */
                                                NULL,
                                                &err);

  /* don't forget to check for errors */
    if(!connection){
        if (err != NULL) {                           
            g_error("%s", err->message);
        }
        return EXIT_FAILURE;
    }

    printf ("Connection successful: %s : %d \n", host, port);


  /* use the connection */
GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));

  GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));

char error[100];

    gboolean ret1 = stream_write( ostream, 
    (char *) request, (char *)error );

    if(!ret1){
        fprintf(stderr,  "%s \n", error );
        return EXIT_FAILURE;;
    }

    const gsize BUFSIZE = 1024;
    gchar read_buf[BUFSIZE];

    gssize read_size = stream_read(  istream, (char *)read_buf, BUFSIZE, (char *)error );

    if(read_size > 0){
        printf( "%s \n", read_buf );
    } else if(read_size < 0){
        fprintf(stderr,  "%s \n", error );
        return EXIT_FAILURE;
    }

    printf( "successful \n");

    return EXIT_SUCCESS;
}


// ** (process:75393): ERROR **: 09:19:24.680: localhost ???????????: Connection refused

