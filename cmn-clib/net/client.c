/**
 * client.c
 * 2022-06-01 K.OHWADA
 */

// CmnNetSocket_NoSessionRequest
// https://ityorozu.net/dev/cmn-clib/doc/html/d7/df2/_cmn_net_8h.html#a17c19524425cb0b39e9b27f81a55725d

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmnclib/CmnNet.h"
#include "port.h"

void run_client(unsigned short port)
{

	CmnDataBuffer *request, *response;


// send request（Graceful Close） 
	request = CmnDataBuffer_Create(0);
	response = CmnDataBuffer_Create(0);
	char *requestData = "test data";

	CmnDataBuffer_Append(request, requestData, strlen(requestData) + 1);
printf( "s: %s \n", request->data);
	CmnNetSocket_NoSessionRequest("127.0.0.1", port, request, response, NULL, 0, CNS_OPT_GRACEFUL_CLOSE);

	printf( "r: %s \n", response->data);
}


int main(int argc, char *argv[])
{

    int port = PORT;

    if(argc == 2){
      	port = atoi( argv[1] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

    printf("port: %d \n",  port );

    run_client(port);

    return 0;
}
