/**
 * C network sample
 * 2020-03-01 K.OHWADA
 */

// TCP Server
 // convert the string sent from the client to uppercase
//  and send it back
// reference : http://onishi-lab.jp/programming/tcp_linux.html

 // Note: inet_ntoa segmentation fault on macOS
// reference :  https://stackoverflow.com/questions/17140107/inet-ntoa-segmentation-fault-on-osx

// TODO: quit with ESC key


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tcp_host.h"


// macOS
 // Note: inet_ntoa segmentation fault on macOS
#include <arpa/inet.h>
char * inet_ntoa(struct in_addr in);


/**
 * toUpper
 */
void toUpper(char*buf, int size)
{
    for (int i=0; i< size; i++){
                    // convert lowercase letters in buf to uppercase
        if(isalpha(buf[i])) {
            buf[i] = toupper(buf[i]);
        }
    } // for
}


/**
 * main
 */
int main(void) 
{
    const int BUFSIZE = 1024;
    char buf[BUFSIZE];

  int socket_listen; // this server
  int socket_client; // client
  struct sockaddr_in addr_listen;
  struct sockaddr_in addr_client;
  socklen_t size_addr_client = sizeof(addr_client);
  int status;
  int numrcv;


    // sockaddr_in setting
    bzero((char *)&addr_listen, sizeof(addr_listen));
    addr_listen.sin_port = htons(PORT);
    addr_listen.sin_family = AF_INET;
    addr_listen.sin_addr.s_addr = INADDR_ANY;
    
    // create socket
    socket_listen = socket(AF_INET, SOCK_STREAM, 0);
    // bind socket
    bind(socket_listen, (struct sockaddr *)&addr_listen, sizeof(addr_listen));
    // allow connect
    listen(socket_listen, 1);
    
    // wait connet
    printf("waiting for connection port: %d \n", PORT);

    while(1)
    {
        // you can connect from the client as many times as you want 
        printf("\n");
        printf("please run client program \n");

        // TODO: quit with ESC key
        printf("or quit with ctrl-c \n");

        socket_client = accept(socket_listen, (struct sockaddr *)&addr_client, &size_addr_client);

        // Note: inet_ntoa segmentation fault on macOS
        printf("connected from: %s : %d \n", inet_ntoa(addr_client.sin_addr), ntohs(addr_client.sin_port) );

        // close(socket_listen);
        
        while(1){
            // recieve packet
            numrcv = read(socket_client, buf, BUFSIZE);
            if(numrcv == 0){
                    // close
                    printf("client socket closed \n");
	                close(socket_client); 
                    break;
            } else if(numrcv == -1){
                    // error
                    printf("ERR: %d %s \n", errno,  strerror(errno));
	                close(socket_client); 
                    break;
            } // if

            printf("recv: %s \n", buf);

            toUpper(buf, numrcv);
   
            // send packet
            write(socket_client, buf, BUFSIZE);
            printf("send: %s \n\n", buf);

        } // while

    } // while

    close(socket_listen);
	close(socket_client); 

    return(0);
}
