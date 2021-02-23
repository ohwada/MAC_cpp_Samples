/**
 * C network sample
 * 2020-07-01 K.OHWADA
 */

// TCP Client for Echo server
// send TCP packet continuously every one second

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/02/23/124215

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

    const int INTINTERVAL = 1; // 1 sec

    const int BUFSIZE = 1024;
    char send_buf[BUFSIZE];

    char error[100];


  // create socket
    int sockfd ;

    sockfd  = tcp_socket( (char *)error );
    if( sockfd  <= 0){
            fprintf(stderr, "socket: %s \n", error );
            return EXIT_FAILURE;
    }


  // connect to server
    bool ret1 = tcp_connect_hostname( sockfd , (char *)HOSTNAME,  PORT , (char *)error );
    if(!ret1){
       fprintf( stderr, "tcp_connect_hostname: %s : %d : %s \n", HOSTNAME,  PORT, error);
        goto label_error;
    }


  printf("connected : %s : %d \n", HOSTNAME, PORT);
  
bool is_verboce = true;

for(int i=0; i<100; i++)
{
    snprintf( send_buf, BUFSIZE, "%03d", i );

    int ret2 = tcp_trace_write_read(sockfd , (char *)send_buf );

    if(ret2 == 0){
       printf("maybe server socket closed \n");
        break;
    }
   
    sleep(INTINTERVAL);

  } // for

    close(sockfd );

      return EXIT_SUCCESS;


// ----- label_error -----
label_error:

    if(sockfd ){
        close(sockfd );
    }

    return EXIT_FAILURE;
}

