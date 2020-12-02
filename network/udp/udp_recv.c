/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// simple UDP receiver
// receive UDP packet continuously

// reference : https://www.geekpage.jp/programming/linux-network/udp.php

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "udp_port.h"


// prototype
void intHandler(int dummy) ;


// global
int sock;


/**
 * Interrupt handler 
 */
void intHandler(int dummy) 
{ 

// release the port,
    if(sock ){
        close(sock);
    }

// quit the program
    printf("bye");
    exit(1);
} 


/**
 * main
 */
int main(void)
{

    const size_t BUFSIZE = 1024;
    char buf[ BUFSIZE];

    int save_err;


//catching interrupt
	signal(SIGINT, intHandler);

    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock<= 0){
        save_err = errno;
        fprintf( stderr, "socket: %s \n", strerror(save_err) );
        return EXIT_FAILURE;
    }


    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons( PORT );

    int ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if(ret != 0){
        save_err = errno;
        fprintf( stderr, "socket: %s \n", strerror(save_err) );
        return EXIT_FAILURE;
    }

    printf("listen: %d \n", PORT );

// clear buffer
    memset(buf, 0,  BUFSIZE);


 // receive UDP packet continuously
while(1) {
    ssize_t size = recv(sock, buf,  BUFSIZE, 0);
    if(size > 0){
        printf("r: %s\n", buf);
    }
}

    close(sock);

    return EXIT_SUCCESS;
}
