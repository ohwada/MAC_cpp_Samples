/**
  * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for HTTP Server


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// prototype
void build_response(char *html, char *response);
void build_html(char *title, char *headline, char *html);


/**
 *  build_response
 */
void build_response(char *html, char *response)
{

    const char HEADER_FORMAT[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d \r\nConnection: Close\r\n";

    // const char CLOSE[] = "Connection: Close\r\n";

    const char CRLF[] = "\r\n";

    const size_t BUFSIZE = 1024;
    char header[BUFSIZE];

    snprintf( header, BUFSIZE, (char *)HEADER_FORMAT, (int)strlen(html) );

    strcpy( (char *)response, (char *)header );
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
