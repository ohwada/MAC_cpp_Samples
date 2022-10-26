#pragma once
/**
  * redirect_url.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "config.h"

// prototype
void getRedirectUri(char* uri);
void build_redirect_uri(int port, char* uri);


/**
 * etRedirectUri
 */
void getRedirectUri(char* uri)
{
    build_redirect_uri(PORT, uri);
}


/**
 * build_redirect_uri
 */
void build_redirect_uri(int port, char* uri)
{
// loopback ip address
    const char FORMAT[] = 
"http://127.0.0.1:%d";

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    snprintf( (char*)buf, BUFSIZE, (char *)FORMAT, port);

    strcpy(uri, buf);
}
