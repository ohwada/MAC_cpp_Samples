#pragma once
/**
 * http_response_builer.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "mime.h"
#include "file_util.h"
#include "c_parse_filename.h"


// prototype
void build_response_header_ok_from_file(char *file, char* response_header);
void build_response_header_ok(int length, char* mime, bool is_crlf, char* header);
void build_response_header(int length, char* mime, char* response);


/**
 *  build_response_header_ok_from_file
 */
void build_response_header_ok_from_file(char *file, char* response_header)
{
    const size_t BUFSIZE = 10;
   char ext[BUFSIZE];
   char mime[BUFSIZE];

    printf("file : %s \n", file);

    strcpy( ext, get_file_ext(file) );
    printf("ext: %s \n", ext);

    strcpy( mime, get_mime(ext) );
    printf("mime : %s \n", mime);

    size_t size = get_file_size(file);
    printf("file size : %zu \n", size);

    bool is_crlf = true;
    build_response_header_ok(size, (char *) mime, is_crlf, response_header);

}


/**
 * build_response_header_ok
 */
void build_response_header_ok(int length, char* mime, bool is_crlf, char* header)
{
    const char CRLF[] = "\r\n";

   const char HEADER_OK[] = "HTTP/1.1 200 OK\r\n";

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];
 
    build_response_header(length, mime, (char *)buf);

    strcpy(header,  HEADER_OK);
    strcat(header,  buf);
    if(is_crlf){
        strcat(header,  (char *)CRLF);
    }

    return;
}


/**
 * build_response_header
 */
void build_response_header(int length, char* mime, char* response)
{

  const char FORMAT_CONTENT_TYPE[] =
"Content-Type: %s \r\n";

    const char  FORMAT_CONTENT_LENGTH[] = 
"Content-Length: %d \r\n";

    const char FORMAT_DATE[] = "Date: %s \r\n";

    // const char CLOSE[] ="Connection: Close\r\n";


    const size_t BUFSIZE = 128;
    char header_content_type[BUFSIZE]; 
    char header_content_length[BUFSIZE]; 
    char header_date[BUFSIZE];
    char date[BUFSIZE];

    snprintf(header_content_type, BUFSIZE, 
    (char *)FORMAT_CONTENT_TYPE, mime);
   
    snprintf(header_content_length, BUFSIZE, 
    (char *)FORMAT_CONTENT_LENGTH, length );

    get_date_rfc5322( (char *)date);

    snprintf( header_date, BUFSIZE, 
    (char *)FORMAT_DATE, (char *)date );

  strcpy(response, header_date);
    strcat(response, header_content_type);
    strcat(response, header_content_length);
    // strcat(response, CLOSE);

    return;
}

