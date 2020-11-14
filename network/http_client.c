/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// get web page from HTTP server
// reference : http://x68000.q-e-d.net/~68user/net/c-http-1.html


#include <stdio.h>
#include <stdlib.h>
#include "http_socket.h"
#include "http_build.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char* host = "example.com";

    int port = PORT_HTTP;

    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] []port] \n",  argv[0] );
    }

    fprintf(stderr, "%s : %d \n",  host, port );

// getaddrinfo
    struct addrinfo *info;
    char error[100];

 bool ret1 = get_addrinfo( (char *)host, (char *)SERVICE_HTTP,  &info, (char *)error );

   if ( ret1) {
        print_addrinfo( info );
    } else {
        fprintf(stderr, "get_addrinfo: %s \n", error );
        return EXIT_FAILURE;
    }

// get IP addinfos
    char ipaddr[100];

    get_ipaddr_from_addrinfo(info, (char *)ipaddr);

    fprintf(stderr, "ipaddr: %s \n", ipaddr);


// open socket
    int socketfd;


    bool ret2 = open_socket( info, &socketfd, (char *)error );

    if(ret2){
        fprintf(stderr, "open_socket: %d \n", socketfd);
    } else {
        fprintf(stderr, "open_socket: %s \n", error);
        return EXIT_FAILURE;
    }


// connect host
    bool ret3 = connect_host( socketfd, (char *)ipaddr, port, (char *)error);

    if(ret3){
        fprintf(stderr, "Conntect to %s\n", (char *)host);
    } else {
        fprintf(stderr,  "%s \n", (char *)error);
        goto label_error;
    }


// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );

// send request
    bool ret4 = socket_send(socketfd, (char *)request, (char *)error);

    if(!ret4){
        fprintf(stderr, "socket_send: %s \n", error);
        goto label_error;
    }

// recieve infoponse
    bool ret5 = print_socket_recv( socketfd, (char *)error );

    if(!ret5){
        fprintf(stderr, "socket_recv: %s \n", error);
        goto label_error;
    }


// close
    close_socket(socketfd);

    fprintf(stderr, "sucessful \n");

    return EXIT_SUCCESS;


// --- error ---
label_error:

    close_socket(socketfd);

    fprintf(stderr, "failed \n");

    return EXIT_FAILURE;
}


// Conntect to "example.com



