/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build for HTML 

#include <string.h>
#include "msg_builder_attach.h"


// constant
const char CONTENT_TYPE_TEXT_HTML_USASCII[] =
"Content-Type: text/html; charset=us-ascii; \r\n";



// prototype
void buildMessageHtml( char* str_subject, char* str_to, char* str_from, char* plain,  char* html, char* msg );
void buildMultipartHtml( char* plain, char* html, char* msg );
void buildContentTypeMultipartAlternative(char* boundary, char* content_type, char* boundary_begin, char* boundary_end, size_t content_type_size );





/**
 * buildMessageHtml
 * RFC 2822 format
 */
void buildMessageHtml( char* subject, char* to, char* from, char* plain,  char* html, char* msg )
{

    char headers[HEADERS_SIZE];
    buildHeaders( subject, to, from,  headers );

	// boundary
   char boundary[BOUNDARY_SIZE + 1];
    getRandomBoundary( (char *)boundary );

    char content_type_multipart[HEADER_SIZE];
    char * boundary_begin[HEADER_SIZE];
    char * boundary_end[HEADER_SIZE];

    buildContentTypeMultipartAlternative( 
    (char *)boundary,  
    (char *)content_type_multipart,  
    (char *)boundary_begin, 
    (char *)boundary_end,
    HEADER_SIZE );


    strcpy(msg, headers);

// multipart 
    strcat(msg, (char*)content_type_multipart );

// plain text
    strcat(msg, (char *)boundary_begin );
    strcat(msg, (char*)CONTENT_TYPE_TEXT_PLANE_USASCII );
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

	strcat(msg, (char *)CRLF ); // saparator

    strcat(msg, plain);
	strcat(msg, (char *)CRLF ); 

// html
    strcat(msg, (char *)boundary_begin );
    strcat(msg, 
    (char *)CONTENT_TYPE_TEXT_HTML_USASCII );
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

	strcat(msg, (char *)CRLF ); // saparator

    strcat(msg, html);
	strcat(msg, (char *)CRLF ); 
    
     strcat(msg, (char *)boundary_end );

}



/**
 *  buildMultipartHtml
 */
void buildMultipartHtml( char* plain, char* html, char* msg )
{

	// boundary
   char boundary[BOUNDARY_SIZE + 1];
    getRandomBoundary( (char *)boundary );

    char content_type_multipart[HEADER_SIZE];
    char * boundary_begin[HEADER_SIZE];
    char * boundary_end[HEADER_SIZE];

    buildContentTypeMultipartAlternative( 
    (char *)boundary,  
    (char *)content_type_multipart,  
    (char *)boundary_begin, 
    (char *)boundary_end,
    HEADER_SIZE );


// plain text
    strcat(msg, (char*)content_type_multipart );
    strcpy(msg, (char *)boundary_begin );
    strcat(msg, (char*)CONTENT_TYPE_TEXT_PLANE_USASCII );
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

	strcat(msg, (char *)CRLF ); // saparator

    strcat(msg, plain);
	strcat(msg, (char *)CRLF ); 

// html
    strcat(msg, (char *)boundary_begin );
    strcat(msg, 
    (char *)CONTENT_TYPE_TEXT_HTML_USASCII );
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

	strcat(msg, (char *)CRLF ); // saparator

    strcat(msg, html);
	strcat(msg, (char *)CRLF ); 
    
     strcat(msg, (char *)boundary_end );

}


/**
 *  buildContentTypeMultipartalternative
 */
void buildContentTypeMultipartAlternative(char* boundary, char* content_type, char* boundary_begin, char* boundary_end, size_t content_type_size )
{
    buildContentTypeMultipart(
    (char *)SUBTYPE_ALTERNATIVE,
    boundary, content_type, boundary_begin, boundary_end, content_type_size );
}

