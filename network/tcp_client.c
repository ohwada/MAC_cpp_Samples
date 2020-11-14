/**
 * C network sample
 * 2020-03-01 K.OHWADA
 */

// TCP Client
// send the input data to the server
// and display the received data
// reference : http://onishi-lab.jp/programming/tcp_linux.html

// TODO: quit with ESC key

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "tcp_host.h"


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
  int ret = connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr));
  if(ret == -1){
        printf("cannot connect: %s : %d \n", LOCALHOST, PORT);
        printf("ERR: %d %s \n", errno,  strerror(errno));
        return(-1);
  }

  printf("connected : %s : %d \n", LOCALHOST, PORT);
  
  while (1){
        printf("please enter the alphabets \n>");
        fgets(buf, BUFSIZE, stdin);

        // quit when only return key
        // TODO: quit with ESC key
        int len = strlen(buf);
        if(len == 1){
            break;
        }

        // delete return code
        buf[len - 1] = '\0';
        // send packet
        write(dstSocket, buf, BUFSIZE);
        printf("send: %s \n", buf);
        // recieve packet
        numrcv = read(dstSocket, buf, BUFSIZE);
        printf("recv: %s \n\n", buf);

  } // while

    close(dstSocket);
    printf("quit \n");

    return(0);
}

