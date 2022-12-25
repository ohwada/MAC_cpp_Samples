#pragma once
/**
 * ws_response_builer.h
 * 2022-10-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "sha1.h"
#include "base64.h"


// prototype
void ws_build_response(char *key, char* response);
void gen_accept_key(char* seckey, char* accept_key);


/**
 *  build_response
 */
void ws_build_response(char *key, char* response)
{

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    const char* FORMAT = 
"HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n";

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, key );

    strcpy(response, buf);

}


/**
 * gen_accept_key
 */
void gen_accept_key(char* seckey, char* accept_key)
{

	const char GUID[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

    size_t guid_len = strlen(GUID);
    size_t seckey_len = strlen(seckey);
    size_t buf_len = seckey_len +  guid_len;

	char buf[buf_len+1];

	memcpy(buf, seckey, seckey_len);
	memcpy(&buf[seckey_len], GUID,  guid_len);

    unsigned char digest[SHA_DIGEST_LENGTH];

    gen_sha1( (char *)buf, buf_len, (unsigned char *)digest);

    char* key = base64Encode( (char *)digest,  SHA_DIGEST_LENGTH, BASE64_TYPE_STANDARD);

    strcpy(accept_key, key);

    free(key);

}

