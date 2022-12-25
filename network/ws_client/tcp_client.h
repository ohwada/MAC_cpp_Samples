#pragma once
/**
 * tcp_client.h
 * 2022-06-01 K.OHWADA
 */

// function  TCP Client

// reference : http://onishi-lab.jp/programming/tcp_linux.html


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"

const int SOCKFD_ERR = -1;

// prototype
int tcp_connect_server(char* host, unsigned short port, int read_timeout, char *error );
int tcp_socket( char *error );
bool tcp_connect_hostname( int sockfd ,  char *hostname, unsigned short port, char *error );
bool tcp_connect_ipaddress( int sockfd ,  char *ipaddress, unsigned short port, char *error );
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error);
bool tcp_trace_write_read(int sockfd , char *send_buf);
bool tcp_trace_write(int sockfd , char *send_buf );
bool tcp_trace_read( int sockfd  );


// global
const int READ_BUFSIZE = 1024;
char read_buf[READ_BUFSIZE]; 


/**
 * tcp_connect_server
 */
int tcp_connect_server(char* host, unsigned short port, int read_timeout, char *error )
{

  // create socket
    int sockfd = tcp_socket( error );

    if( sockfd  < 0){
            return SOCKFD_ERR;
    }

  // connect to server
    bool ret1 = tcp_connect_hostname( sockfd, host,  port , error );

    if(!ret1){
        close( sockfd );
        return SOCKFD_ERR;
    }

    set_tcp_read_timeout(sockfd, read_timeout);

    return sockfd;
}


/**
 * tcp_socket
 */
int tcp_socket( char *error )
{
   int  sfd  = socket(AF_INET, SOCK_STREAM, 0);
    if( sfd  <= 0) {
            int save_err = errno;
            strcpy( error, strerror(save_err) );
            return SOCKFD_ERR;
    }

    return sfd;
}


/**
 * tcp_connect_hostname
 */
bool tcp_connect_hostname( int sockfd ,  
    char *hostname, unsigned short port, char *error )
{

    char ipaddress[100];

    bool ret = get_ipaddress( hostname, NULL, (char *)ipaddress, error);

    if(!ret){
         return false;
    }

    return tcp_connect_ipaddress(  sockfd ,  
    (char *)ipaddress, port, error );
}


/**
 * tcp_connect_ipaddress
 */
bool tcp_connect_ipaddress( int sockfd ,  char *ipaddress, unsigned short port, char *error )
{
  // connect server
    struct sockaddr_in sock_addr;

  bzero((char *)&sock_addr, sizeof(sock_addr));
  sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr( ipaddress );
  sock_addr.sin_port = htons(port);

  int ret = connect(sockfd , (struct sockaddr *)&sock_addr, sizeof(sock_addr));

  if(ret == -1){
        strcpy(error, strerror(errno) );
        return false;
  }

    return true;
}


/**
 * get_ipaddress
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
 *tcp_trace_write_read
 */
bool tcp_trace_write_read(int sockfd , char *send_buf )
{
    bool ret1 =tcp_trace_write( sockfd , send_buf );
    if(!ret1){
        return false; // error   
    }
    
    bool ret2 = tcp_trace_read( sockfd  );

    if(ret2){
        printf("\n");
    }

    return ret2;
}


/**
 *tcp_trace_write
 */
bool tcp_trace_write(int sockfd , char *send_buf )
{
    const size_t BUFSIZE = 128;
    char error[BUFSIZE];

    bool ret = tcp_write_str(sockfd, send_buf, (char *)error );
    if( ret){
        printf("s: %s \n", send_buf);
    } else {
        fprintf(stderr, "write: %s \n", error );
        return false;
    }

    return true;
}


/**
 *  tcp_trace_read
 */
bool tcp_trace_read( int sockfd  )
{

    int err;

    ssize_t size = tcp_read( sockfd, (char *)read_buf, READ_BUFSIZE, &err );

    bool ret = false;

    if(size > 0){
            printf("r: %s \n", read_buf);
            ret = true;
    } else if(size < 0){
            fprintf(stderr, "read: %s \n", strerror(err) );
    }

    return ret;
}

