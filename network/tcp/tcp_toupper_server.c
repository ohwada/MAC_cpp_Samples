/**
 * C network sample
 * 2020-07-01 K.OHWADA
 */

// TCP Server
 // convert the string sent from the client to uppercase
//  and send it back

// reference : http://onishi-lab.jp/programming/tcp_linux.html

 // Note: inet_ntoa segmentation fault on macOS
// reference :  https://stackoverflow.com/questions/17140107/inet-ntoa-segmentation-fault-on-osx

// TODO: quit with ESC key


#include <stdio.h>
#include <stdlib.h>
#include "tcp_server.h"
#include "tcp_port.h"

// prototype
void toUpper(char* src, char *dst);


/**
 * toUpper
 */
void toUpper(char* src, char *dst)
{

    size_t size = strlen(src);

    for (int i=0; i< size; i++){
                    // convert lowercase letters in buf to uppercase
        if(isalpha(src[i])) {
            dst[i] = toupper(src[i]);
        }else{
            dst[i] = src[i];
        }
    } // for
}


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

    if(sockfd_listen < 0){
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
   
        if(sockfd_client < 0){
            fprintf(stderr, "accept: %s \n", error);
        }
 
        while(1) {
            // recieve packet
            int size_read = tcp_read( sockfd_client, 
            (char *)recv_buf, BUFSIZE, (char *)error );

        if( size_read > 0 ){
                // read
                    printf("r: %s \n", recv_buf);
                // convert
                 toUpper( (char *)recv_buf,  (char *)send_buf );
            // send packet
                    bool ret1 = tcp_write( sockfd_client, (char *)send_buf, (char *)error );
                    if(!ret1){
                        fprintf( stderr, "write: %s \n", error );
                    }
            } else if ( size_read == 0 ){
                    // close
                    printf("maybe client socket closed \n");
	                close(sockfd_client); 
                    break;
            } else {
                fprintf( stderr, "read: %s \n", error );
            }

           
        } // while

    } // while

    printf("close \n");
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
