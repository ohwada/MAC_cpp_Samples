/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// fuction for BIO


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>


// constant
const uint16_t PORT_HTTP = 80;
 const uint16_t PORT_HTTPS = 443;


// prototype
bool send_bio(    BIO *bio, char *data);
bool print_recv_bio(BIO *bio);
void build_url(char *host, int port, char *url, size_t url_size);


/**
 * send_bio
 */
bool send_bio(    BIO *bio, char *data)
{
    int write_size = BIO_write(bio, data, strlen(data) ); 

    if(write_size <= 0 ) {
        return false;
    }

    return true;
}


/**
 * print_recv_bio
 */
bool print_recv_bio(BIO *bio)
{
    const size_t BUFSIZE = 1024;
    char response[BUFSIZE + 1 ];

    int read_size;

    bool is_error = false;

     while(1)
    {
        read_size = BIO_read(bio, (char *)response,  BUFSIZE );

        if(read_size >0) {
        // success
                printf("%s \n", response); 
        } else if (read_size == 0) {
    // recv end
            break;
        } else {
        // error
            is_error = true;
            break;
        }

    } // while 

    return !is_error;
}


/** 
 *  build_url
 */
void build_url(char *host, int port, char *url, size_t url_size)
{
    snprintf(url, url_size, "%s:%d", host, port);
}

