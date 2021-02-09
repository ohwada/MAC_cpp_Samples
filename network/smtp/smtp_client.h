#pragma once
/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */


// SMTP Client


// Implemented the basic protocol of SMTP in C language
// reference : http://techdatebook.seesaa.net/article/452940846.html


// constant
const size_t ERROR_SIZE = 100;


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tcp_client.h"


// prototype
bool sendMsg(char *msg, char *ret_error );
bool send_msg( char *host, int port, char *to, char *from, char *msg, char *ret_error );


/**
 * sendMsg
 */
bool sendMsg(char *msg, char *ret_error )
{


// the host name set in the /etc/hosts file
   const char HOST[] = "ubuntu";


// SMTP port
   const  int PORT = 25;


// NOT a email address.
// able to delivere when you specify the user name on the posifix server
    const char * TO =  "taro";


// NOT a real email address.
// virtual address used in SMTP protocol
    const char FROM[] = "hoge@example.com";


    char error[ERROR_SIZE];

    bool ret = send_msg( 
    (char *)HOST, 
    PORT, 
    (char *)TO, 
    (char *)FROM, 
    (char *)msg, 
    (char *)error );

    if(!ret){
        strcpy(ret_error, error );
    }

    return ret;
}


/**
 * send_msg
 */
bool send_msg( char *host, int port, char *to, char *from, char *msg, char *ret_error )
{

    const char HELO_FORMAT[] = "HELO %s \r\n";

    const char RCPT_TO_FORMAT[] = "RCPT TO: %s \r\n";

 const char MAIL_FROM_FORMAT[] = "MAIL FROM: %s \r\n";

    const char CMD_DATA[] = "DATA\r\n";

    const char END_OF_MESSAGE[] = ".\r\n";

    const char CMD_QUIT[] = "QUIT\r\n";

    const char SENDER[] = "localhost";

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    char error[100];

// Socket descriptor
    int sockfd;                 


// Creating a socket
    sockfd = tcp_socket( (char *)error );

    if( sockfd <= 0 ){
        strcpy(ret_error, error);
        return false;
    }


// Connect to server
bool ret1 = tcp_connect_hostname( sockfd,  (char *)host, port, (char *)error );

if(!ret1){
        strcpy(ret_error, error);
        return false;
}

    printf( "connect to: %s : %d \n", host, port );


// send HELO
    snprintf(buf, BUFSIZE, (char *)HELO_FORMAT, (char *)SENDER );
    tcp_trace_write(sockfd, buf);  
    tcp_trace_read(sockfd);  
 

// send MAIL FROM
    snprintf(buf, BUFSIZE, (char *)MAIL_FROM_FORMAT, (char *)from );
    tcp_trace_write(sockfd, buf);  
    tcp_trace_read(sockfd);  


// send RCPT TO
    snprintf(buf, BUFSIZE, (char *)RCPT_TO_FORMAT, (char *)to );
    tcp_trace_write(sockfd, buf);  
    tcp_trace_read(sockfd);  


// send DATA
    tcp_trace_write(sockfd,  (char *)CMD_DATA );   
    tcp_trace_read(sockfd);  



// send message
    // tcp_trace_write(sockfd, send_buf);  
    tcp_trace_write(sockfd, msg);  


// send message end
    //strcpy(buf, (char *)END_OF_MESSAGE );
    tcp_trace_write(sockfd, (char *)END_OF_MESSAGE);  
    tcp_trace_read(sockfd);  


// send quit
    tcp_trace_write(sockfd, (char *)CMD_QUIT );  
    tcp_trace_read(sockfd); 


    return true;
}
 