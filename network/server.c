/**
 * C++ network sample
 * 2020-03-01 K.OHWADA
 */


 // convert the string sent from the client to uppercase
//  and send it back
// reference : http://onishi-lab.jp/programming/tcp_linux.html

 // Note: inet_ntoa segmentation fault on macOS
// reference :  https://stackoverflow.com/questions/17140107/inet-ntoa-segmentation-fault-on-osx

// TODO: quit with ESC key

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "host.h"


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

  int srcSocket; // this server
  int dstSocket; // client
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);
  int status;
  int numrcv;


    // sockaddr_in setting
    bzero((char *)&srcAddr, sizeof(srcAddr));
    srcAddr.sin_port = htons(PORT);
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    
    // create socket
    srcSocket = socket(AF_INET, SOCK_STREAM, 0);
    // bind socket
    bind(srcSocket, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
    // allow connect
    listen(srcSocket, 1);
    
    // wait connet
    printf("waiting for connection port: %d \n", PORT);

    while(1)
    {
        // you can connect from the client as many times as you want 
        printf("\n");
        printf("please run client program \n");

        // TODO: quit with ESC key
        printf("or quit with ctrl-c \n");

        dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);

        // Note: inet_ntoa segmentation fault on macOS
        printf("connected from: %s : %d \n", inet_ntoa(dstAddr.sin_addr), ntohs(dstAddr.sin_port) );

        // close(srcSocket);
        
        while(1){
            // recieve packet
            numrcv = read(dstSocket, buf, BUFSIZE);
            if(numrcv == 0){
                    // close
                    printf("client socket closed \n");
	                close(dstSocket); 
                    break;
            } else if(numrcv == -1){
                    // error
                    printf("ERR: %d %s \n", errno,  strerror(errno));
	                close(dstSocket); 
                    break;
            } // if

            printf("recv: %s \n", buf);

            toUpper(buf, numrcv);
   
            // send packet
            write(dstSocket, buf, BUFSIZE);
            printf("send: %s \n\n", buf);

        } // while

    } // while

    close(srcSocket);
	close(dstSocket); 

    return(0);
}
