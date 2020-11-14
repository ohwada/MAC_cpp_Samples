#pragma once
/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// function for HTTP
// reference : http://x68000.q-e-d.net/~68user/net/c-http-1.html

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>


// prototype
bool get_addrinfo(char *host, char *service, struct addrinfo **info, char *error);
void get_ipaddr_from_addrinfo(struct addrinfo *info, char *ipaddr);
bool open_socket(struct addrinfo *info, int *socketfd, char *error);
bool connect_socket(int socketfd, struct addrinfo *info, char *error);
bool connect_host(int socketfd, char *ipaddr, uint16_t port, char *error);
void close_socket(int socketfd);
bool get_ipaddr(char *host,  char *service, char *ipaddr, char *error);
void build_http_request(char *host, char *path, char *request);
void socket_send(int socketfd, char *request);
void print_socket_recv(int socketfd);
void print_addrinfo( struct addrinfo *info);


/**
 * get_addrinfo
 */
bool get_addrinfo(char *host, char *service, struct addrinfo **info, char *error)
{

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(host, service, &hints, info);

    if (err != 0) {
        strcpy( error, gai_strerror(err) );
        return false;
    }

    return true;
}


/**
 * get_ipaddr_from_addrinfo
 */
void get_ipaddr_from_addrinfo(struct addrinfo *info, char *ipaddr)
{

    struct in_addr addr;

    addr.s_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr.s_addr;

    strcpy(ipaddr, inet_ntoa(addr) );
}


/**
 * open_socket
 */
bool open_socket(struct addrinfo *info, int *socketfd, char *error)
{

    int sfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

    if (sfd < 0) {
            int err_save = errno;
            strcpy(error, strerror(err_save));
            return false;
        }

    *socketfd =  sfd;

    return true;
}


/**
 * connect_socket
 */
bool connect_socket(int socketfd, struct addrinfo *info, char *error)
{

    int ret = connect( socketfd, info->ai_addr, info->ai_addrlen );
    if (ret != 0) {
        int err_save = errno;
        strcpy(error, strerror(err_save));
        return false;
    }

    return true;
}


/** 
 * connect_host
 */
bool connect_host(int socketfd, char *ipaddr, uint16_t port, char *error)
{

        struct sockaddr_in sa;

        memset(&sa, '\0', sizeof(sa));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(port);
        inet_pton(AF_INET, ipaddr, &sa.sin_addr);

        int err = connect( socketfd, (struct sockaddr *) &sa, sizeof(sa) );
        if (err < 0) {
            int err_save = errno;
            strcpy(error, strerror(err_save));
            return false;
        }

        return true;
}


/** 
 * closes the given socket descriptor.
 */
void close_socket(int socketfd)
{

 /* no more receptions */
        shutdown(socketfd, SHUT_RDWR);       
        close(socketfd);
}


/** 
 *  get IP address from host name
 */
bool get_ipaddr(char *host,  char *service, char *ipaddr, char *error)
{

    struct sockaddr_in server;
    struct addrinfo hints, *res;
    struct in_addr addr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(host, service, &hints, &res);

    if (err != 0) {
        strcpy(error, gai_strerror(err));
        return false;
    }

    addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;

    strcpy( ipaddr, inet_ntoa(addr) );

    return true;
}


/** 
 *  build_http_request
 */
void build_http_request(char *host, char *path, char *request)
{

    const size_t BUFSIZE = 100;
    char buf[100];

  snprintf(buf, BUFSIZE, "GET %s HTTP/1.1\r\n", (char *)path);
  strcpy(request, buf);

  strcat(request, "Accept: */* \r\n");

  snprintf(buf, BUFSIZE, "Host: %s\r\n", (char *)host ); 
  strcat(request, buf); 

   strcat(request, "Connection: close\r\n\r\n"); 
}


/** 
 *  socket_send
 */
void socket_send(int socketfd, char *request)
{
    write(socketfd, request, strlen(request) );
}


/** 
 *  print_socket_recv
 */
void print_socket_recv(int socketfd)
{
    const size_t BUF_LEN = 200;
    char buf[BUF_LEN];
    int read_size;

    while (1)
    {
        read_size  = read(socketfd, buf, BUF_LEN);
        if ( read_size > 0 ) {
            printf("%s", (char*)buf );
        } else {
            break;
        }
    } // while

    printf("\n");

}


/**
 * print_addrinfo
 */
void print_addrinfo( struct addrinfo *info)
{
   fprintf( stderr, "ai_flags: %d \n", info->ai_flags );
    fprintf( stderr, "ai_family: %d \n", info->ai_family );
    fprintf( stderr, "ai_socktype: %d \n", info->ai_socktype );
    fprintf( stderr, "ai_protocol: %d \n", info->ai_protocol );
    fprintf( stderr, "ai_canonname: %s \n", info->ai_canonname);
}

