#pragma once
/**
 * not_found_builder.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "response_builder.h"

// prototype
void build_msg_not_found(char* path, char* msg);
void build_response_header_not_found(
int length, char *mime, bool is_crlf, char* header);


/**
 *  build_msg_not_found
 */
 void build_msg_not_found(char* path, char* msg)
{
    const char FORMAT[] = 
"<html><head></head><body><h1>Not Found</h1><h2> %s </h2></body></html>";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, path);

    strcpy(msg, buf);
  
    return;
}


/**
 *  build_response_header_not_found
 */
 void build_response_header_not_found(int length, char* mime,  bool is_crlf, char* header)
{

    const char CRLF[] = "\r\n";

    const char HEADER_NOT_FOUND[] =
"HTTP/1.1 404  Not Found\r\n";

    //char* mime = "text/html";

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

    build_response_header(length, mime, (char *)buf );

    strcpy(header, HEADER_NOT_FOUND);
    strcat(header, buf);
if(is_crlf){
    strcat(header, (char *)CRLF);
}


    return;
}


