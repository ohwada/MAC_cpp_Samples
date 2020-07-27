/**
 * C++ network sample
 * 2020-03-01 K.OHWADA
 */

// send the input data to the server
// display the received data
// reference : http://onishi-lab.jp/programming/tcp_linux.html

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "host.h"


/**
 * main
 */
int main()
{

    const int BUFSIZE = 1024;
    char buf[BUFSIZE];

    int dstSocket;
    int    numrcv;
    struct sockaddr_in dstAddr;
    struct hostent *hp;
  
  //sockaddr_in setting
  bzero((char *)&dstAddr, sizeof(dstAddr));
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_port = htons(PORT);
  
  hp = gethostbyname(LOCALHOST);
  bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

  // create socket
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  // connect server
  if (connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0){
        printf("cannot connect: %s \n", LOCALHOST);
        return(-1);
  }

  printf("connected : %s : %d \n", LOCALHOST, PORT);

  printf("please enter the alphabets \n");
  
  while (1){
        scanf("%s",buf);
        // send packet
        write(dstSocket, buf, BUFSIZE);
        printf("send: %s \n", buf);
        // recieve packet
        numrcv = read(dstSocket, buf, BUFSIZE);
        printf("recv: %s \n\n", buf);
  } // while

  close(dstSocket);

  return(0);
}

