/**
 * ws_server.c
 * 2022-10-01 K.OHWADA
 */

// WebSocket Echo Server in C
// send back index.html when sccessed by Web Brawser
// echo back text

#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include "tcp_server.h"
#include "ws_server.h"
#include "port.h"


/**
 * on_accept
 */
void on_accept(int sockfd_client)
{

    const size_t DATA_SIZE = 200; 
    char read_data[DATA_SIZE];

    const int LOOP = 100;
    const int SLEEP = 5; // 5 sec

    bool ret1 = ws_handshake(sockfd_client);
    if(!ret1){
        return;
    }

    ssize_t read_size;
    int err;


// read out the concatenated multiple frames, 
// if the frame transmission interval of client is shorter than the read interval of server (5 sec)
// in that case, the first frame is processed and the rest are ignored.
// concatenated frames need to be decomposed and processed as separate frames.

    for(int i=0; i<LOOP; i++){
        sleep(SLEEP );
        read_size = tcp_read( sockfd_client, (char *)read_data,  DATA_SIZE, &err );
        if(read_size >= 2){
            printf("\n");
            dump_frame_read_data( (char *)read_data, read_size);
            char opcode = parse_frame( (char *)read_data, read_size);
            if(opcode == OP_TEXT){
                proc_text(sockfd_client, (char *)read_data, read_size );
            } else if(opcode == OP_CLOSE){
                proc_close(sockfd_client, (char *)read_data, read_size );
                break;
            } else if(opcode == OP_PING){
                proc_ping(sockfd_client, (char *)read_data, read_size );
            }
        }
    } // for

}


/**
 * main
 */
int main(int argc, char *argv[])
{

    unsigned short port = PORT;

    if(argc == 2){
      	port = atoi( argv[2] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

    printf("port: %d \n",  port );

    bool ret = run_server(port);
    if(!ret){
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
