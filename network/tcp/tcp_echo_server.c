/**
 * C network sample
 * 2020-07-01 K.OHWADA
 */

// TCP Echo Server
// Echo back the received data as it is

// reference : http://onishi-lab.jp/programming/tcp_linux.html

// TODO: quit with ESC key


#include <stdio.h>
#include <stdlib.h>
#include "tcp_server.h"
#include "tcp_port.h"


/**
 * main
 */
int main(void) 
{
    const int BUFSIZE = 1024;
    char recv_buf[BUFSIZE];
    char send_buf[BUFSIZE];

    char error[100];

    int sockfd_listen; // this server
    int sockfd_client; // client

    int backlog = 1;

// create socket
    sockfd_listen = tcp_socket_listen_port( PORT, backlog, (char *)error );

    if( sockfd_listen < 0 ){
        fprintf(stderr, "socket: %s \n", error);
        return EXIT_FAILURE;
    }

// wait connet
    printf("waiting for connection port: %d \n", PORT);

    bool is_verboce = true;

while(1)
{
        // you can connect from the client as many times as you want 
        printf("\n");
        printf("please run client program \n");

        // TODO: quit with ESC key
        printf("or quit with ctrl-c \n");

// accept
        sockfd_client = tcp_accept( sockfd_listen, (char *)error, is_verboce );

        if( sockfd_client < 0){
            fprintf(stderr, "accept: %s \n", error);
        }

        while(1){
            // recieve packet
            int size_read = tcp_read( sockfd_client, 
            (char *)recv_buf, BUFSIZE, (char *)error );

            if( size_read > 0 ){
                // read
                    printf("r: %s \n", recv_buf);
                // echo back
                    strcpy(send_buf, recv_buf);
                    bool ret1 = tcp_write( sockfd_client, send_buf, (char *)error );
                    if(!ret1){
                        fprintf( stderr, "write: %s \n", error );
                    }
            }else if( size_read == 0 ) {
                // close
                printf("maybe client socket closed \n");
	            close(sockfd_client); 
                break;
            } else {
                fprintf( stderr, "read: %s \n", error );
            }

        } // while

    } // while

    close(sockfd_listen);
	close(sockfd_client); 

   return EXIT_SUCCESS;


// ----- label_error -----
label_error:

    if(sockfd_listen){
        close(sockfd_listen);
    }

    if(sockfd_client){
	    close(sockfd_client); 
    }

    return EXIT_FAILURE;
}
