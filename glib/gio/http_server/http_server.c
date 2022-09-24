/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Server

// reference : https://stackoverflow.com/questions/9513327/gio-socket-server-client-example/10085464#10085464

#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include "gio_stream.h"

// prototype
gboolean incoming_callback( GSocketService *service,
                    GSocketConnection *connection,
                    GObject *source_object,
                    gpointer user_data);
gboolean  print_connect_from( GSocketConnection *connection);
gboolean send_response(  GOutputStream *ostream);


/* this function will get called everytime a client attempts to connect */
gboolean 
incoming_callback( GSocketService *service,
                    GSocketConnection *connection,
                    GObject *source_object,
                    gpointer user_data)
{

    print_connect_from( connection);


    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));

  GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));

    const gsize BUFSIZE = 1024;
    gchar read_buf[BUFSIZE];
    char error[100];

    gssize read_size = stream_read( istream, (gchar *)read_buf, BUFSIZE, (char *)error);
    if(read_size > 0 ) {
        printf("%s\n", read_buf);
        send_response(ostream);
    } else if(read_size < 0 ) {
        fprintf(stderr, "read: %s", error);
    }

  return FALSE;
}


/**
 * print_connect_from
 */
gboolean  print_connect_from( GSocketConnection *connection)
{

    GError *err = NULL;

    GInetSocketAddress *sock_addr =
    (GInetSocketAddress *)
    g_socket_connection_get_remote_address( 
    connection, &err );

    if(sock_addr == NULL){
        if(err != NULL){
            g_error("%s", err->message);
        }
        return FALSE;
    }
    

    GInetAddress *inet_addr = 
    g_inet_socket_address_get_address( sock_addr );

    gchar *ipaddr =
    g_inet_address_to_string( inet_addr );

    guint16 port = g_inet_socket_address_get_port( sock_addr );

    printf("Connection from: '%s' : %d \n", ipaddr, port);

    g_object_unref(sock_addr);
 
    return TRUE;
}


/**
 * send_response
 */
gboolean send_response(  GOutputStream *ostream)
{
    const size_t BUFSIZE = 1024;
    char response[BUFSIZE];
    const size_t ERR_SIZE = 512;
    char error[ERR_SIZE];

    bool ret1 = get_index_html_response( (char *)response, 
    (char *)error );

    if(!ret1){
        fprintf(stderr, "%s \n", error);
        return FALSE;
    }

    gboolean ret2 = stream_write( ostream, (char *)response, (char *)error);
    if(!ret2){
        fprintf(stderr, "write: %s \n", error);
        return FALSE;
    }

    return TRUE;
}


/**
 * main
 */
int main (int argc, char *argv[])
{

    int port = 8080;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        fprintf(stderr, "Usage: %s  [port] \n",  argv[0] );
    }


  GError *error = NULL;

  /* create the new socketservice */
  GSocketService * service = g_socket_service_new();

  /* connect to the port */
  gboolean ret1 = g_socket_listener_add_inet_port ( (GSocketListener*)service,
                                    port, /* your port goes here */
                                    NULL,
                                    &error);

  /* don't forget to check for errors */
    if(!ret1){
        if (error != NULL){
            g_error ( "%s", error->message );
        }
        return EXIT_FAILURE;
    }

  /* listen to the 'incoming' signal */
    const char *details_signal = "incoming";
  g_signal_connect (service,
                    details_signal,
                    G_CALLBACK (incoming_callback),
                    NULL);

  /* start the socket service */
  g_socket_service_start(service);

  /* enter mainloop */
  printf("Waiting for client port: %d \n", port);

  GMainLoop *loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

    printf( "successful \n");

    return EXIT_SUCCESS;
}
