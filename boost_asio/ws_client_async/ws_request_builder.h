#pragma once
/**
 * request_builder.h
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "random_char.h"
#include "base64.h"

// constant
const char *ROOT_PATH = "/";


// prototype
void build_ws_request(char *host, char* path, char* key, char *request);
void gen_ws_key(char* key,  size_t size);
void gen_rand_key(char* key,  size_t size);


/** 
 *  gen_ws_key
 */
void gen_ws_key(char* key,  size_t size)
{
    char rand[size+2];

    gen_rand_key( (char *)rand,  size);

    char *b64 = base64Encode(rand, size, BASE64_TYPE_STANDARD);

    strcpy(key, b64);
    free(b64);
}


/*
 *  gen_rand_key
 */
void gen_rand_key(char* key,  size_t size)
{
    const char NUL = '\0';

    char rand[size+1];

    for(int i=0; i<size; i++){
        rand[i] = getRandomCharMix();
    }
    rand[size] = NUL;

    strcpy(key, rand);
}


/** 
 *  build_ws_request
 */
void build_ws_request(char *host, char* path, char* key, char *request)
{
const size_t BUFSIZE = 512;
char buf[BUFSIZE];

const char* FORMAT = 
"GET %s HTTP/1.1\r\nHost: %s\r\nUpgrade: websocket\r\nConnection: upgrade\r\nSec-WebSocket-Key: %s\r\nSec-WebSocket-Version: 13\r\n\r\n";

snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, path, host,  key );

strcpy(request, buf);

}

