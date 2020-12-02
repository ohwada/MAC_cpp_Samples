/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// simple UDP transmitter
// send UDP packet continuously every one second

// reference : https://www.geekpage.jp/programming/linux-network/udp.php

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ipaddr.h"
#include "udp_port.h"

/**
 * main
 */
int main(void)
{

    const char HOSTNAME[] = "localhost";

    const int INTINTERVAL = 1;  // 1 sec

    const size_t BUFSIZE = 100;
    char send_buf[BUFSIZE];

    char ipaddress[100];
    char error[100];

    int sock;
    int save_err;
 

    bool ret1 = get_ipaddress( (char *)HOSTNAME, NULL, (char *)ipaddress, (char*)error );

    if(!ret1){
        fprintf(stderr, "get_ipaddress: %s \n", error);
        return EXIT_FAILURE;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock<= 0){
        save_err = errno;
        fprintf( stderr, "socket: %s \n", strerror(save_err) );
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr;   
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr( ipaddress );
    addr.sin_port = htons( PORT );

    printf("sendto: %s : %d \n", HOSTNAME, PORT);


// send UDP packet continuously
for(int i=0; i<100; i++) {

    snprintf( send_buf, BUFSIZE, "%03d", i );
    
    ssize_t size = sendto(sock, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr, sizeof(addr));

    if(size > 0 ) {
        printf("s: %s \n", send_buf);
    } else {
        save_err = errno;
        fprintf( stderr, "sendto: %s \n", strerror(save_err) );
    }

    sleep(INTINTERVAL);
}

    close(sock);

    return EXIT_SUCCESS;

}

