/**
 * C network sample
 * 2020-07-01 K.OHWADA
 */

// TCP Client for toupperServer
// send the input data to the server
// and display the received data

// reference : http://onishi-lab.jp/programming/tcp_linux.html

// TODO: quit with ESC key

#include <stdio.h>
#include <stdlib.h>
#include "tcp_client.h"
#include "tcp_port.h"


/**
 * main
 */
int main(void)
{

    const char HOSTNAME[] = "localhost";

    const char CHAR_NULL = '\0';

    const int BUFSIZE = 1024;
    char buf[BUFSIZE];

    char error[100];


  // create socket
    int sockfd ;

    sockfd  = tcp_socket( (char *)error );
    if( sockfd  <= 0) {
            fprintf(stderr, "socket: %s \n", error );
            return EXIT_FAILURE;
    }

  
  // connect server
    bool ret1 = tcp_connect_hostname( sockfd , (char *)HOSTNAME,  PORT , (char *)error );

    if(!ret1){
       fprintf( stderr, "tcp_connect_hostname: %s : %d : %s \n", HOSTNAME,  PORT, error);
        goto label_error;
    }

  printf("connected : %s : %d \n", HOSTNAME, PORT);
  
bool is_verboce = true;

  while (1)
{
        printf("please enter the alphabets \n>");
        fgets(buf, BUFSIZE, stdin);

        // quit when only return key
        // TODO: quit with ESC key
        int len = strlen(buf);
        if(len == 1){
            // only return code
            break;
        }

        // replace return code to null
        buf[len - 1] = CHAR_NULL;

        // send packet
        int ret2 = tcp_trace_write_read(sockfd, buf );

        if(ret2 == 0){
            printf("maybe server socket closed \n");
            break;
        }

  } // while

    close(sockfd );

    printf("quit \n");

      return EXIT_SUCCESS;


// ----- label_error -----
label_error:

    if(sockfd ){
        close(sockfd );
    }

    return EXIT_FAILURE;
}

