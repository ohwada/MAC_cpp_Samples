/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// Get the IP Address from the host name
// using getaddrinfo

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/02/23/122908

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
 * get_hostname
* resolve hostname with reverse DNS lookup
 */
bool get_hostname(char *ipaddress, char *service, char *hostname, socklen_t  hostlen, char *error ) 
{ 
	struct sockaddr_in addr;	 
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = inet_addr(ipaddress); 
	socklen_t addr_len = sizeof(struct sockaddr_in); 

    socklen_t  servlen = 0;
    if(service){
        servlen = strlen(service);
    }

	int err = getnameinfo( (struct sockaddr *)&addr, addr_len, hostname, hostlen, service, servlen, NI_NAMEREQD );

	if (err != 0) { 
        strcpy( error, gai_strerror(err) );
		return false; 
	} 

	return true; 
} 


/**
 * main
 */
int main(int argc, char *argv[]) 
{

    char *hostname = "google.com";

   if (argc == 2) {
        hostname = argv[1];
    } else {
        printf("Usage: %s [hostname] \n", argv[0] );
    }

    printf("hostname: %s \n", hostname);
 
	char reverse_hostname[NI_MAXHOST]; 
    char ipaddress[100];
    char error[100];

    char *service = NULL;

    bool ret1 = get_ipaddress( (char*)hostname, service, (char *)ipaddress, (char*)error);

    if(!ret1){
       fprintf( stderr, "get_ipaddress: %s \n", error);
         return EXIT_FAILURE;
    }

    printf("ip address: %s \n", ipaddress );

    bool ret2 = get_hostname( (char *)ipaddress, service, 
    (char *)reverse_hostname, NI_MAXHOST, (char *)error );

    if(!ret2){
       fprintf( stderr, " get_hostname error: %s : %s \n", ipaddress, error);
         return EXIT_FAILURE;
    }

    printf("reverse hostname: %s \n", reverse_hostname );

     return EXIT_SUCCESS;
}


// hostname: google.com 
// ip address: 172.217.25.110 
// reverse hostname: nrt13s51-in-f14.1e100.net 


