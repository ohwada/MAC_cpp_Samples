/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// TCP Echo Client
// send TCP packet continuously every one second

// reference : https://stackoverflow.com/questions/9513327/gio-socket-server-client-example/10085464#10085464

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gio_stream.h"
#include "echo_port.h"


/**
 * main
 */
int main (void)
{

    const char HOST[] = "localhost";

    const int MAX_LOOP = 100;

    const unsigned int INTRVAL = 1; // 1sec

    const size_t BUFSIZE = 1024;
    char write_buf[BUFSIZE];
    char read_buf[BUFSIZE];
    char error[100];

  GError * err = NULL;

  /* create a new connection */
  GSocketConnection * connection = NULL;

  GSocketClient * client = g_socket_client_new();

  /* connect to the host */
  connection = g_socket_client_connect_to_host(client,
                                               (gchar*) HOST,
                                                PORT, /* your port goes here */
                                                NULL,
                                                &err);

  /* don't forget to check for errors */
    if(!connection){
        if (err != NULL) {                           
            g_error("%s", err->message);
        }
        return EXIT_FAILURE;
    }

    printf ("Connection successful: %s : %d \n", HOST, PORT);


  /* use the connection */
GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));

  GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));

    gboolean is_error = FALSE;

for(int i=0; i<MAX_LOOP; i++)
{
    // snprintf(write_buf, BUFSIZE, "%03d", i);



    gboolean ret1 = stream_write( ostream, 
    (char *)write_buf, (char *)error );

    if(ret1){
        printf("s: %s \n", write_buf);
    } else{
        fprintf(stderr,  "write: %s \n", error );
        is_error = TRUE;
        break;
    }

    gssize read_size = stream_read(  istream, (char *)read_buf, BUFSIZE, (char *)error );

    if(read_size > 0){
        printf( "r: %s \n", read_buf );
    } else if(read_size == 0){
        printf("maybe server connection close \n");
        break;
    } else{
        fprintf(stderr,  "read: %s \n", error );
        is_error = TRUE;
        break;
    }

    printf( "\n");
    sleep(INTRVAL);
} // for


    if(is_error) {
        return EXIT_FAILURE;
    }
 
    printf("sucessful \n");

    return EXIT_SUCCESS;
}


// ** (process:75393): ERROR **: 09:19:24.680: localhost ???????????: Connection refused

