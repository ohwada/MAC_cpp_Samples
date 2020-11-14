/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// very simple HTTP Server
// return fixed prepared response

// reference : https://www.geekpage.jp/programming/linux-network/http-server.php


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/**
 * build_response
 */
void build_response(char *response)
{
    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    char content[100];

    strcpy(content, (char *)"<h1>HELLO</h1>\r\n");

    int len_content = strlen(content);

    strcpy(response, (char *)"HTTP/1.1 200 OK\r\n");

    strcat(response, (char *)"Content-Type: text/html\r\n");

    snprintf(buf, BUFSIZE, "Content-Length: %d\r\n",  len_content);
    strcat(response, buf);

    strcat(response, (char *)"\r\n");

    strcat(response, (char *)content );

}


/**
 * main
 */
int main(void)
{

    const uint16_t PORT = 8080;

    const size_t BUFSIZE = 2048;
    char inbuf[BUFSIZE];

    const int reuse_yes = 1;
    const int backlog = 5;
    const int recv_flags = 0;
    const int send_flags = 0;

    int socket_listen;

    int socket_client;

    int save_err;


// build response
    char response[1000];
    build_response( (char *)response );

    printf("%s \n", response);


// open socket
    socket_listen = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_listen < 0) {
        save_err = errno;
        fprintf(stderr, "socket: %s \n", strerror(save_err) );
        return EXIT_FAILURE;
    }


// reuse
    int ret1 = setsockopt( socket_listen,
   SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse_yes, sizeof(reuse_yes) );

    if (ret1 != 0) {
        save_err = errno;
        fprintf(stderr, "bind: %s \n", strerror(save_err) );
        goto label_error;
    }


// bind port
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons( PORT );
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret2 = bind(socket_listen, (struct sockaddr *)&addr, sizeof(addr) );

    if (ret2 != 0) {
        save_err = errno;
        fprintf(stderr, "bind: %s \n", strerror(save_err) );
        goto label_error;
    }


// listen
    int ret3 = listen(socket_listen, backlog );

    if (ret3 != 0) {
        save_err = errno;
        fprintf(stderr, "listen: %s \n", strerror(save_err) );
        goto label_error;
    }

// recv request
    struct sockaddr_in client;

    socklen_t client_len =  sizeof(client);

    size_t recv_size;

    size_t send_size;

 while (1) 
{

   socket_client = accept(socket_listen, (struct sockaddr *)&client, &client_len );

   if (socket_client < 0) {
        save_err = errno;
        fprintf(stderr, "listen: %s \n", strerror(save_err) );
	   break;
   }

// clear buffer
   memset(inbuf, 0, sizeof(inbuf));

   recv_size = recv(socket_client, inbuf, BUFSIZE, recv_flags);

    if(recv_size > 0) {
        // success
        printf("%s", inbuf);
    } else if (recv_size == 0) {
        // recv end
        break;
    } else {
        // error
        save_err = errno;
        fprintf(stderr, "listen: %s \n", strerror(save_err) );
    }

// Normally, YOU should parse the request from the client.

// send fixed prepared response

   send_size = send(socket_client, (char *)response, (int)strlen(response),  send_flags);

    if(send_size <= 0) {
        save_err = errno;
        fprintf(stderr, "listen: %s \n", strerror(save_err) );
    }

    close(socket_client);

 } // while


    close(socket_listen);

    printf("successful \n");

    return EXIT_SUCCESS;


// --- error ---
label_error:


    if(socket_listen){
        close(socket_listen);
    }

    if(socket_client){
        close(socket_client);
    }

    printf("failed \n");

    return EXIT_FAILURE;
}

