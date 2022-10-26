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
bool tcp_write1(int sockfd, char *buf, char *error );
bool tcp_write2(int sockfd, char *buf, size_t buf_size, char *error );
bool tcp_read1( int sockfd, char *buffer, char *error );
ssize_t tcp_read2( int sockfd, char *buf, size_t bufsize, char *error );
void set_tcp_write_timeout(int sock_fd, int time);
void set_tcp_read_timeout(int sock_fd, int time);


/**
 * tcp_write1
 */
bool tcp_write1(int sockfd, char *buf, char *error )
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
 * tcp_write2
 */
bool tcp_write2(int sockfd, char *buf, size_t buf_size, char *error )
{
    ssize_t write_size = write( sockfd, buf, buf_size );
    if(write_size <= 0){
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


