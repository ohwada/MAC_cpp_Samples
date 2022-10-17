/**
 * server.c
 * 2022-06-01 K.OHWADA
 */

// TODO:
// cannot connect by telnet


// CmnNetSocket_StartServer
// https://ityorozu.net/dev/cmn-clib/doc/html/d7/df2/_cmn_net_8h.html#a21e857c2de39687e9b3654a2862ec632

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmnclib/CmnNet.h"
#include "cmnclib/CmnTime.h"
#include "port.h"

static void serverMethod(CmnNetSocket *socket)
{
	printf("serverMethod \n");

// Server processing: 
// Receive data and send it back as is

	CmnDataBuffer *request = CmnDataBuffer_Create(0);
	CmnNetSocket_ReceiveAll(socket, request, NULL, 0);
	printf( "%s \n", request->data);

	CmnNetSocket_SendAll(socket, request->data, request->size);
}


void run_server(unsigned short port)
{
	CmnNetSocketServer server;
	CmnNetSocketStatus serverRet;

// start server
	serverRet = CmnNetSocket_StartServer(port, serverMethod, &server);

printf("ststus : %d \n",  serverRet);

if(serverRet == CNS_SUCCESS ){
	printf("running \n");
}


// sleep for a while until listened
	CmnTime_Sleep(500);

	printf("listen port: %d \n", port);
}


int main()
{
	 unsigned short port= PORT;
    run_server(port);

    return 0;
}
