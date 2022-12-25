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
#include <ctype.h>
#include <sys/socket.h>


// prototype
bool tcp_write(int sockfd, char *buf, size_t size, char *error );
bool tcp_write_str(int sockfd, char *buf, char *error );
bool tcp_read_str( int sockfd, char *buffer, char *error );
ssize_t tcp_read( int sockfd, char *buf, size_t bufsize, int *err );
bool tcp_block_read(int socketfd, char* buffer, size_t block_size, int loop, bool is_verbose, char *error);
void set_tcp_write_timeout(int sock_fd, int time);
void set_tcp_read_timeout(int sock_fd, int time);
void dump_tcp_read(ssize_t  read_size, char* data, char* error);


/**
 * tcp_write
 */
bool tcp_write(int sockfd, char *buf, size_t bufsize, char *error )
{
    ssize_t write_size = write( sockfd, buf, bufsize );
    if(write_size <= 0){
            int save_err = errno;
            strcpy( error, strerror(save_err) );
            return false;
    }

    return true;
}


/**
 * tcp_write
 */
bool tcp_write_str(int sockfd, char *buf, char *error )
{
    return tcp_write(sockfd, buf, strlen(buf), error );
}


/**
 *  tcp_read_str
 */
bool tcp_read_str( int sockfd, char *buffer, char *error )
{
    const char NUL = '\0';

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

    memset(buf, NUL, BUFSIZE);

    int err;

    ssize_t size = tcp_read( sockfd, (char *)buf, BUFSIZE, &err );

    bool ret = false;
    if(size < 0){
        strcpy( error, strerror(err) );
    } else if(size > 0){
    // null terminated string
        buf[size] = NUL;
        strcpy(buffer, buf);
        ret = true;
    }

    return ret;
}


/**
 *  tcp_read
 */
ssize_t tcp_read( int sockfd, char *buf, size_t bufsize, int *err )
{

// zero clear
    memset(buf, 0,  bufsize);

    ssize_t size = read(sockfd, buf, ( bufsize - 1));

    if(size < 0 ){
        *err = errno;
    }

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


/**
 * dump_tcp_read
 */
void dump_tcp_read(ssize_t  read_size, char* data, char* error)
{
    if(read_size < 0){
        printf("tcp read error: %s \n", error);
        return;
    }  else if(read_size == 0){
        printf("tcp read: no data \n");
        return;
    }

    printf("read size: %zu \n", read_size);

    for(int i=0; i<read_size; i++){
        char c = data[i];
        printf("%d : %02x ", i, (unsigned char)c );
        if( isprint(c) ){
            printf("%c ", c );
        }
        printf("\n");
    } // for
        printf("\n");
}

