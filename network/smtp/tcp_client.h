/**
 * C network sample
 * 2020-07-01 K.OHWADA
 */

// function  for TCP Client


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// prototype
int tcp_socket( char *error );
bool tcp_connect_hostname( int sockfd,  char *hostname, int port, char *error );
bool tcp_connect_ipaddress( int sockfd,  char *ipaddress, int port, char *error );
bool tcp_trace_write(int sockfd, char *data);
int tcp_trace_read(int sockfd);
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error);


// global
const size_t READ_BUFSIZE = 1024;
char read_buf[READ_BUFSIZE];


/**
 * tcp_socket
 */
int tcp_socket( char *error )
{
   int  sfd  = socket(AF_INET, SOCK_STREAM, 0);
    if( sfd  <= 0) {
            int save_err = errno;
            strcpy( error, strerror(errno) );
            return -1;
    }

    return sfd;
}


/**
 * socket_connect_hostname
 */
bool tcp_connect_hostname( int sockfd ,  
    char *hostname, int port, char *error )
{

    char ipaddress[100];

    bool ret = get_ipaddress( hostname, NULL, (char *)ipaddress, error);

    if(!ret){
         return false;
    }

    return tcp_connect_ipaddress( sockfd ,  
    (char *)ipaddress, port, error );
}


/**
 * tcp_connect_ipaddress
 */
bool tcp_connect_ipaddress( int sockfd , char *ipaddress, int port, char *error )
{
  // connect server
    struct sockaddr_in sock_addr;

  bzero((char *)&sock_addr, sizeof(sock_addr));
  sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr( ipaddress );
  sock_addr.sin_port = htons(port);

  int ret = connect(sockfd , (struct sockaddr *)&sock_addr, sizeof(sock_addr));

  if(ret == -1){
        int save_err = errno;
        strcpy(error, strerror(errno) );
        return false;
  }

    return true;
}


/**
 *  tcp_trace_write
 */
bool tcp_trace_write(int sockfd, char *buf)
{
    ssize_t size = write(sockfd, buf, strlen(buf) );

    if(size > 0){
        printf("< %s", buf);
    } else {
        int err_save = errno;
        fprintf(stderr, "write: %s \n", strerror(err_save) );
        return false;
    }

    return true;
}


/**
 * tcp_trace_read
 */
int tcp_trace_read(int sockfd)
{

    const char CHAR_NULL;

// zero clear
    memset(read_buf, 0, READ_BUFSIZE);

    ssize_t size =  read(sockfd, read_buf, (READ_BUFSIZE - 1) );

    if(size > 0){
            // null terminated string
            read_buf[size] = CHAR_NULL;
            printf("> %s \n", read_buf);
    } else if(size < 0){
            int err_save = errno;
            fprintf(stderr, "read: %s \n", strerror(err_save) );
    }

return (int)size;
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

