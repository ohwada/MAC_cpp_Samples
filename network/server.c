/**
 * C++ network sample
 * 2020-03-01 K.OHWADA
 */

// convrt the string recieve from the client
// send back it
// reference : http://onishi-lab.jp/programming/tcp_linux.html

// reference :  https://stackoverflow.com/questions/17140107/inet-ntoa-segmentation-fault-on-osx

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "host.h"


// macOS
#include <arpa/inet.h>
char * inet_ntoa(struct in_addr in);


/**
 * main
 */
int main() 
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



  while(1){
    // you can connect from the client as many times as you want 

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
    printf("please run client program \n");
    dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);

    printf("connected from: %s : %d \n", inet_ntoa(dstAddr.sin_addr), ntohs(dstAddr.sin_port) );

    close(srcSocket);
        
    while(1){
      // recieve packet
      numrcv = read(dstSocket, buf, BUFSIZE);
      if(numrcv == 0 || numrcv == -1 ){
	        close(dstSocket); break;
      } // if

      printf("recv: %s \n", buf);

      for (int i=0; i< numrcv; i++){
            // convert lowercase letters in buf to uppercase
	        if(isalpha(buf[i])) {
                buf[i] = toupper(buf[i]);
            }
      } // for

      // send packet
      write(dstSocket, buf, BUFSIZE);
      printf("send: %s \n", buf);
    } // while
  } // while

  return(0);
}
