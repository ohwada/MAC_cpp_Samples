#pragma once
/**
 * tcp.h
 * 2022-06-01 K.OHWADA
 */

// function for TCP write read
// reference : http://onishi-lab.jp/programming/tcp_linux.html


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>


// prototype
bool tcp_write(int sockfd, char *buf, char *error );
bool tcp_read1( int sockfd, char *buffer, char *error );
ssize_t tcp_read2( int sockfd, char *buf, size_t bufsize, char *error );
bool tcp_block_read(int socketfd, char* buffer, size_t block_size, int loop, bool is_verbose, char *error);
void set_tcp_write_timeout(int sock_fd, int time);
void set_tcp_read_timeout(int sock_fd, int time);


/**
 * tcp_write
 */
bool tcp_write(int sockfd, char *buf, char *error )
{
    ssize_t size = write( sockfd, buf, strlen(buf) );
    if(size <= 0){
            int save_err = errno;
            strcpy( error, strerror(save_err) );
            return false;
    }

    return true;
}


/**
 *  tcp_read1
 */
bool tcp_read1( int sockfd, char *buffer, char *error )
{

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

    ssize_t size = tcp_read2( sockfd, (char *)buf, BUFSIZE, error );

    bool ret = (size>0)? true : false;
    return ret;
}


/**
 *  tcp_read2
 */
ssize_t tcp_read2( int sockfd, char *buf, size_t bufsize, char *error )
{

    const char NUL = '\0';


// zero clear
    memset(buf, 0,  bufsize);

    ssize_t size = read(sockfd, buf, ( bufsize - 1));

    if(size > 0){
            // null terminated string
                buf[size] = NUL;
    } else if(size < 0 ){
                // error
                strcpy( error, strerror(errno) );
    } // if

    return size;
}


/** 
 *  tcp_block_read
* ivide into small blocks and receive multiple times
 */
bool tcp_block_read(int socketfd, char* buffer, size_t block_size, int loop, bool is_verbose, char *error)
{

    const char NUL = '\0';

    char buf[block_size];
    
    bool is_error = false;

    int i = 0;

    for(i=0; i<loop; i++)
    {

        memset(buf, NUL, block_size);

     ssize_t size  = read(socketfd, buf, ( block_size - 1 ) );

        if ( size > 0 ) {
            // null terminated string
            buf[size] = NUL;
            if(is_verbose) {
                printf("%d: %s \n", i, buf);
            }
            strcat(buffer, buf);
        } else if ( size == 0 ) {
            if(is_verbose) {
                // progress
                printf("%d \n", i);
            }
// exit loop when recieve nothing
            break;
        } else  {
            if(is_verbose) {
                // progress
                printf("errno: %d \n", errno);
            }
            if(errno == 35){
                // read err: 35 Resource temporarily unavailable
            } else{
                is_error = true;
                int err_save = errno;
                strcat(error, strerror(err_save));
                break;
            }
        }

    } // while

        if(is_verbose) {
                printf("loop: %d \n", i);
        }

    return !is_error;
}


/**
 * set_write_timeout
 */
void set_tcp_write_timeout(int sock_fd, int time)
{

    struct timeval tv;

    tv.tv_sec = time;
    tv.tv_usec = 0;

    setsockopt(sock_fd, SOL_SOCKET,  SO_SNDTIMEO, (char *)&tv, sizeof(tv));
}


/**
 * set_read_timeout
 */
void set_tcp_read_timeout(int sock_fd, int time)
{

    struct timeval tv;

    tv.tv_sec = time;
    tv.tv_usec = 0;

    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
}

