#pragma once
/**
 * http_server.h
 * 2020-07-01 K.OHWADA
 */

// function for HTTP Server


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"


// prototype
bool get_index_html_response(char *response, char* error);
void build_response(char *html, char *response);
void build_html(char *title, char *headline, char *html);


/**
 * get_index_html_response
 */
bool get_index_html_response(char *response, char* error)
{

    char *file = "data/index.html";

    char* html = file_text_read(file, error);
    if( !html ) {
        return false;
    }

    build_response( html, response);

    free(html);

    return true;
}


/**
 *  build_response
 */
void build_response(char *html, char *response)
{

    const char HEADER_OK[] = "HTTP/1.1 200 OK\r\n";
    const char HEADER_CONTENT_HTML[] = "Content-Type: text/html\r\n";

    const char FORMAT_CONTENT_LENGTH[] = "Content-Length: %d \r\n";

    // const char CLOSE[] = "Connection: Close\r\n";

    const char CRLF[] = "\r\n";

    const size_t BUFSIZE = 512;
    char header_content_length[BUFSIZE];

    snprintf( header_content_length, BUFSIZE, 
    (char *)FORMAT_CONTENT_LENGTH, (int)strlen(html) );

 strcpy( (char *)response, (char *)HEADER_OK );
 strcat( (char *)response, 
    (char *)HEADER_CONTENT_HTML );
    strcat( (char *)response, (char *)header_content_length );
    strcat( (char *)response, (char *)CRLF);
    strcat( (char *)response, html);
    strcat( (char *)response, (char *)CRLF);
    // ( (char *)response, (char *)CLOSE );
}


/**
 * build_html
 */
void build_html(char *title, char *headline, char *html)
{

    const char HTML_FORMAT[] = "<html><head><title>%s</title></head><body><h1>%s</h1></body></html>";

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

    snprintf( buf, BUFSIZE, (char *)HTML_FORMAT, title, headline);

    strcpy(html, buf);
}

