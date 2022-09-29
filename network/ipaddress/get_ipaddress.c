/**
 * get_ipaddress.c
 * 2022-06-01 K.OHWADA
 */

// Get the IP Address from the host name
// using getaddrinfo

// reference : https://www.geekpage.jp/programming/linux-network/getaddrinfo-4.php

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


// protoype
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error);
bool get_hostname(char *ipaddress, char *service, char *hostname, socklen_t  hostlen, char *error ) ;


/**
 * get_ipaddress
* resolve IP address with forward DNS lookup
 */
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error)
{

    struct addrinfo hints, *info;
  
    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(hostname, service, &hints, &info);
    if (err != 0) {
        strcpy( error, gai_strerror(err) );
        return false;
    }

    struct in_addr addr;

    addr.s_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr.s_addr;

    strcpy( ipaddress, inet_ntoa(addr) );

    freeaddrinfo(info);

     return true;
}


/**
 * main
 */
int main(int argc, char *argv[]) 
{

    char *hostname = "example.com";

   if (argc == 2) {
        hostname = argv[1];
    } else {
        printf("Usage: %s [hostname] \n", argv[0] );
    }

    printf("hostname: %s \n", hostname);
 
    const size_t BUSIZE  = 100;
    char ipaddress[BUSIZE];
    char error[BUSIZE];

    char *service = NULL;

    bool ret = get_ipaddress( (char*)hostname, service, (char *)ipaddress, (char*)error);

    if(!ret){
       fprintf( stderr, "get_ipaddress: %s \n", error);
         return EXIT_FAILURE;
    }

    printf("ip address: %s \n", ipaddress );

     return EXIT_SUCCESS;
}


// hostname: example.com 
// ip address: 93.184.216.34 


