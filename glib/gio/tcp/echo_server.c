/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// TCP Echo Server
// echo back the received data as it is

// reference : https://stackoverflow.com/questions/9513327/gio-socket-server-client-example/10085464#10085464

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gio_stream.h"
#include "echo_port.h"


// prototype
gboolean incoming_callback( GSocketService *service,
                    GSocketConnection *connection,
                    GObject *source_object,
                    gpointer user_data);
gboolean  print_connect_from( GSocketConnection *connection);


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
    gchar write_buf[BUFSIZE];
    char error[100];

    gboolean is_error = FALSE;

while(1)
{
    gssize read_size = stream_read( istream, (gchar *)read_buf, BUFSIZE, (char *)error);
    if(read_size > 0){
        printf("r: %s\n", read_buf);
        strcpy(write_buf, read_buf);
        gboolean ret = stream_write( ostream, write_buf, (char *)error);
        if(!ret){
            fprintf(stderr, "write: %s", error);
            is_error = TRUE;
            break;
        }
    } else if ( read_size == 0 ){
        printf("maybe client connection close \n");
        break;
    } else {
        fprintf(stderr, "read: %s", error);
        is_error = TRUE;
        break;
    }

} // while

    if( is_error ){
        return TRUE;
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
    // g_object_unref(inet_addr);

    return TRUE;
}


/**
 * main
 */
int main (void)
{

  GError *error = NULL;

  /* create the new socketservice */
  GSocketService * service = g_socket_service_new();

  /* connect to the port */
  gboolean ret1 = g_socket_listener_add_inet_port ( (GSocketListener*)service,
                                    PORT, /* your port goes here */
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
  g_signal_connect(service,
                    details_signal,
                    G_CALLBACK (incoming_callback),
                    NULL);

  /* start the socket service */
  g_socket_service_start(service);

  /* enter mainloop */
  printf("Waiting for client port: %d \n", PORT);

  GMainLoop *loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

    printf("sucessful \n");

    return EXIT_SUCCESS;
}
