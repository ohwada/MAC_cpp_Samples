/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build for HTML 


#include <string>
#include "msg_builder_attach.hpp"


// prototype
bool buildMessageHtmlAttachment( std::string subject, std::string to, std::string from, std::string plain,  std::string html,  std::string filepath, std::string &msg, std::string &error );
void buildMessageHtml( std::string str_subject, std::string str_to, std::string str_from, std::string plain,  std::string html, std::string &msg );
void buildMultipartHtml( std::string plain, std::string html, std::string &msg );
void getContentTypeMultipartAlternative(std::string boundary, std::string &content_type, std::string &boundary_begin, std::string &boundary_end);



/**
 * buildMessageHtmlAttachment
 * RFC 2822 format
 */
bool buildMessageHtmlAttachment( std::string subject, std::string to, std::string from, std::string plain,  std::string html,  std::string filepath, std::string &msg, std::string &ret_error )
{

    std::string attach;
    std::string error;

    bool ret = buildAttachment( filepath, attach, error );

    if(!ret){
        ret_error = error;
        return false;
    }

    std::string multipart_html;
    buildMultipartHtml( plain,  html,  multipart_html );

	// boundary
   std::string boundary;
    getBoundary(boundary);

    std::string content_type_multipart;
    std::string boundary_begin;
    std::string boundary_end;
    getContentTypeMultipartMixed( boundary,  content_type_multipart,  boundary_begin, boundary_end );


    std::string headers;
    buildHeaders( subject, to, from,  headers );


// build msg
    msg = headers;
    msg += content_type_multipart;

// html plain
    msg += boundary_begin;

    msg += multipart_html;

// attachment
    msg += boundary_begin;

    msg += attach + CRLF;

    msg +=  boundary_end;

    return true;

}


/**
 * buildMessageHtml
 * RFC 2822 format
 */
void buildMessageHtml( std::string subject, std::string to, std::string from, std::string plain,  std::string html, std::string &msg )
{

    std::string multipart;

    buildMultipartHtml( 
    plain,  html, multipart );

    std::string headers;
    buildHeaders( subject, to, from,  headers );

    msg = headers;
    msg += multipart;

}



/**
 *  buildMultipartHtml
 */
void buildMultipartHtml( std::string plain, std::string html, std::string &msg )
{

    const std::string CONTENT_TYPE_TEXT_HTML_USASCII(
    "Content-Type: text/html; charset=us-ascii; \r\n");


	// boundary
   std::string boundary;
    getBoundary(boundary);

    std::string content_type_multipart;
    std::string boundary_begin;
    std::string boundary_end;
    getContentTypeMultipartAlternative( boundary,  content_type_multipart,  boundary_begin, boundary_end );

// plain text
    msg += content_type_multipart;

    msg += CRLF; // boundary
    msg += boundary_begin;

    msg += CONTENT_TYPE_TEXT_PLANE_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

		msg += CRLF; // saparator

        msg += plain + CRLF;

// html
    msg += CRLF; // boundary
    msg += boundary_begin;

    msg += CONTENT_TYPE_TEXT_HTML_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

	msg += CRLF; // saparator

    msg += html + CRLF;
    
    msg += CRLF;  // boundary
     msg +=  boundary_end;

}


/**
 *  getContentTypeMultipartAlternative
 */
void getContentTypeMultipartAlternative( std::string boundary, std::string  &content_type, std::string &boundary_begin, std::string &boundary_end  )
{

    getContentTypeMultipart( 
    SUBTYPE_ALTERNATIVE,
    boundary,  content_type, boundary_begin, boundary_end  );

}


