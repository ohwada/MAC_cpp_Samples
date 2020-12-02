/**
 *  network sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// gcc smtp_client.c

// Implemented the basic protocol of SMTP in C language
// reference : http://techdatebook.seesaa.net/article/452940846.html


#include <stdio.h>
#include <stdlib.h>
 #include "smtp_client.h"
#include "tcp_client.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    const char SUBJECT[] = "smtp client test";

    const char BODY[] =  "This is a test mail.\r\nThis mail was sent using smtp client test program.\r\n";

    const char SENDER[] = "localhost";

    const char FROM[] = "hoge@example.com";

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    char send_buf[1024];

    char message[1024];

    char error[100];

    char * host = "ubuntu";
    int port = 25;
    char * to =  "taro";
    char * from = "hoge@example.com";

  if(argc == 4){
        host = argv[1];
        port = atoi( argv[2]);
        to = argv[3];
} else {
     printf("Usage: %s [host]  [port] [to] \n",  argv[0] );
}

    printf( "host: %s \n", host );
    printf( "port: %d \n", port );
    printf( "to: %s \n", to );

    buildMessage( (char *)from, (char *)to, (char *)SUBJECT, (char *)BODY, (char *)message );

    printf("%s \n", message);


// Socket descriptor
  int sockfd;                 


// Creating a socket
    sockfd = tcp_socket( (char *)error );

    if( sockfd <= 0 ){
        fprintf(stderr, " socket: %s \n", error );
        return EXIT_FAILURE;
    }


// Connect to server
bool ret1 = tcp_connect_hostname( sockfd,  (char *)host, port, (char *)error );

if(!ret1){
        fprintf(stderr, "tcp_connect_hostname: %s \n", error );
        return EXIT_FAILURE;
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
    strcpy(send_buf, (char *)CMD_DATA );
    tcp_trace_write(sockfd, send_buf);  
    tcp_trace_read(sockfd);  

// from
    snprintf(buf, BUFSIZE, (char *)FROM_FORMAT,  (char *)from );
    strcpy(send_buf, buf );

// to
    snprintf(buf, BUFSIZE, (char *)TO_FORMAT,  (char *)to );
    strcat(send_buf, buf );

// message
    strcat(send_buf, message );
    strcat(send_buf, (char *)CRLF );
    tcp_trace_write(sockfd, send_buf);  

// message end
    strcpy(buf, (char *)END_OF_MESSAGE );
    tcp_trace_write(sockfd, buf);  
    tcp_trace_read(sockfd);  


// quit
    strcpy(buf, (char *)CMD_QUIT );
    tcp_trace_write(sockfd, buf);  
    tcp_trace_read(sockfd); 

    printf("successful \n");

    return EXIT_SUCCESS;
}
 
 
// connect to: ubuntu : 25 
// * <HELO localhost 
// * >220 VirtualBox ESMTP Postfix (Ubuntu)

