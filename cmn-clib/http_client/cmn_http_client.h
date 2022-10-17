#pragma once
/**
 * cmn_http_client.h
 * 2022-06-01 K.OHWADA
 */

// CmnNetSocket_NoSessionRequest
// https://ityorozu.net/dev/cmn-clib/doc/html/d7/df2/_cmn_net_8h.html#a17c19524425cb0b39e9b27f81a55725d

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cmnclib/CmnNet.h"
#include "save.h"

//prototype
char* http_client(char* host, unsigned short port, char *request_data, bool is_save_response);
bool split_header_body(CmnDataBuffer* response, CmnDataBuffer *header, CmnDataBuffer *body);


/**
 * http_client
 */
char* http_client(char* host, unsigned short port, char *request_data, bool is_save_response )
{

    const char NUL = '\0';

	CmnDataBuffer *request, *response, *header, *body;

	request = CmnDataBuffer_Create(0);
	response = CmnDataBuffer_Create(0);
	header = CmnDataBuffer_Create(0);
	body = CmnDataBuffer_Create(0);

	CmnDataBuffer_Append(request,  request_data, strlen(request_data) );
// printf( "s: %s \n", request->data);

// send request（Graceful Close） 
	CmnNetSocket_NoSessionRequest(host, port, request, response, NULL, 0, CNS_OPT_GRACEFUL_CLOSE);

	// printf( "r: %s \n", response->data);
	printf("response len: %zu\n", strlen(response->data) );

    if(is_save_response){
        bool is_save_verbose = true;
        save_response( response->data, is_save_verbose);
    }

    bool ret1 = split_header_body( response, header, body);
    if(!ret1){
        return NULL;
    }

	// printf("\n header \n");
	// printf(%s \n", header->data);
	printf("header len: %zu\n", strlen(header->data) );

	// printf("\n body \n");
	// printf( "r: %s \n", body->data);

    size_t len = strlen(body->data);
	printf("body len: %zu\n", len);

    char *buf = (char *)calloc( (len+1), sizeof(char) );
    memcpy(buf, body->data, len);
    buf[len] = NUL;

    CmnDataBuffer_Free(request);
    CmnDataBuffer_Free(response);
    CmnDataBuffer_Free(header);
    CmnDataBuffer_Free(body);

    return buf;
}


/*
 *  split_header_body
*/
bool split_header_body(CmnDataBuffer* response, CmnDataBuffer *header, CmnDataBuffer *body)
{

    const char NUL = '\0';

    const char* DELIM = "\r\n\r\n"; 

    char *text = response->data;

    size_t text_len = strlen(text);

    char* p = strstr(text, DELIM);

    if(p==NULL){
        return false;
    }

// Note:
// overwrite repsponse
    *p = NUL;

	CmnDataBuffer_Append(header, text, strlen(text) );

	CmnDataBuffer_Append(body, (char *)&p[4], (text_len -4) );

    return true;
}
