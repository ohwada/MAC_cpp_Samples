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
int tcp_socket(char *error);
bool tcp_connect_hostname( int sockfd,  char *hostname, int port, char *error );
bool tcp_connect_ipaddress( int sockfd,  char *ipaddress, int port, char *error );
bool tcp_write(int socketfd, char *request, char *error);
bool print_tcp_read(int socketfd, char *error);
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error);


/**
 *  tcp_socket
 */
int tcp_socket(char *error)
{

  // create socket
    int sfd  = socket(AF_INET, SOCK_STREAM, 0);
    if( sfd  <= 0 ) {
            int save_err = errno;
            strcpy(error, strerror(errno) );
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
 *  tcp_write
 */
bool tcp_write(int socketfd, char *request, char *error)
{
    int size = write(socketfd, request, strlen(request) );

    if(size <= 0) {
            int err_save = errno;
            strcpy(error, strerror(err_save));
            return false;
    }

    return true;
}


/** 
 *  print_tcp_read
 */
bool print_tcp_read(int socketfd, char *error)
{

    const char CHAR_NULL = '\0';

    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];
    
    bool is_error = false;

    while (1)
    {
        memset(buf, 0, BUFSIZE);

     ssize_t size  = read(socketfd, buf, ( BUFSIZE - 1 ) );

        if ( size > 0 ) {
            // null terminated string
            buf[size] = CHAR_NULL;
            printf("%s", buf);
        } else if ( size == 0 ) {
            // read end
            break;
        } else  {
            // error
            is_error = true;
            int err_save = errno;
            strcpy(error, strerror(err_save));
            break;
        }
    } // while

    printf("\n");

    return !is_error;
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
