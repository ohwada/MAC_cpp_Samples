#pragma once
/**
 * tcp_server.h
 * 2022-06-01 K.OHWADA
 */

// function for TCP Server
// reference : http://onishi-lab.jp/programming/tcp_linux.html


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"


// prototype
int tcp_socket_listen_port(int port, int backlog, char *error);
int tcp_socket(char *error);
bool tcp_reuse(int sockfd_listen, char *error);
bool tcp_bind(int sockfd_listen, int port, char *error);
bool tcp_listen(int sockfd_listen, int backlog, char *error);
int tcp_accept(int sockfd_listen, char *error, bool is_verboce);


/**
 *  tcp_socket_listen_port
 */
int tcp_socket_listen_port(int port, int backlog, char *error)
{

    int sockfd = tcp_socket( error );

    if( sockfd < 0 ){
        return -1;
    }

    bool ret1 = tcp_reuse( sockfd, error);
   if(!ret1){
        return -1;
    }

    bool ret2 = tcp_bind( sockfd, port, error );
    if(!ret2){
        return -1;
    }


    bool ret3 = tcp_listen( sockfd, backlog, error );
    if(!ret3){
        return -1;
    }

    return sockfd;
}


/**
 *  tcp_socket
 */
int tcp_socket(char *error)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd <= 0){
        int save_err = errno;
        strcpy(error, strerror(save_err));
        return -1;
    }
    return sfd;
}


/**
 * tcp_reuse
 */
bool tcp_reuse(int sockfd_listen, char *error)
{

   const int reuse_yes = 1;

    int ret = setsockopt( sockfd_listen,
   SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse_yes, sizeof(reuse_yes) );

    if (ret != 0) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
    }

    return true;
}


/**
 * tcp_bind
 */
bool tcp_bind(int sockfd_listen, int port, char *error)
{
  struct sockaddr_in addr_listen;

    bzero((char *)&addr_listen, sizeof(addr_listen));
    addr_listen.sin_family = AF_INET;
    addr_listen.sin_addr.s_addr = INADDR_ANY;
    addr_listen.sin_port = htons(port);

    // bind socket
    int ret = bind(sockfd_listen, (struct sockaddr *)&addr_listen, sizeof(addr_listen));
    if(ret != 0){
        int save_err = errno;
        strcpy(error, strerror(save_err));
        return false;
    }

    return true;
}


/**
 * tcp_listen
 */
bool tcp_listen(int sockfd_listen, int backlog, char *error)
{
    int ret = listen(sockfd_listen, backlog);
    if(ret != 0){
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
    }
    return true;
}


/**
 * tcp_accept
 */
int tcp_accept(int sockfd_listen, char *error, bool is_verboce)
{
    struct sockaddr_in addr_client;
    socklen_t size_addr_client = sizeof(addr_client);

        int sfd = accept(sockfd_listen, (struct sockaddr *)&addr_client, &size_addr_client);
    if(sfd  <= 0){
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return -1;
    }
    
        // Note: inet_ntoa segmentation fault on macOS
    if ( is_verboce ){
        printf("connected from: %s : %d \n", inet_ntoa(addr_client.sin_addr), ntohs(addr_client.sin_port) );
    }

    return sfd;
}

