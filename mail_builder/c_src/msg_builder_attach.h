#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// build build message


#include "msg_builder.h"
 #include "msg_builder_base64.h"
#include "media_type.h"


// constant
const size_t HEADER_SIZE = 200;
const size_t ERROR_SIZE = 100;


// prototype
char* buildMsgAttachment( char *subject, char *to, char *from, char *body,  char *filepath, char *ret_error );
char* buildAttachment(char *filepath,  size_t *msg_size, char *ret_error );


/**
 * buildMsgAttachment
 */
char* buildMsgAttachment( char *subject, char *to, char *from, char *body,  char *filepath, char *ret_error )
{

   size_t attach_size;
    char error[ERROR_SIZE];

    char *attachment = buildAttachment( filepath,  &attach_size, (char *)error );

    if( !attachment ) {
        strcpy(ret_error, error);
        return NULL;
    }


    size_t size = attach_size + HEADERS_SIZE + BODY_SIZE  ;  char *msg = (char *)malloc(size);

    if(!msg){
        strcpy( ret_error, "buildMessageAttachment malloc faild");
        free(attachment);
        return NULL;
    }


	// boundary
   char boundary[BOUNDARY_SIZE + 1];
    getRandomBoundary( (char *)boundary );

    char content_type_multipart[HEADER_SIZE];
    char * boundary_begin[HEADER_SIZE];
    char * boundary_end[HEADER_SIZE];

    buildContentTypeMultipartMixed( (char *)boundary,  (char *)content_type_multipart,  (char *)boundary_begin, (char *)boundary_end );


    char * headers[HEADERS_SIZE];
    buildHeaders( subject, to, from,  (char *)headers );


// build msg
    strcpy( msg,  (char *)headers);
    strcat(msg, (char *)content_type_multipart);
    strcat(msg, (char *)CRLF );


// body
    strcat(msg, (char *)boundary_begin);
    strcat(msg, 
    (char *)CONTENT_TYPE_TEXT_PLANE_USASCII);
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT);

	    strcat(msg, (char *)CRLF ); // saparator

        strcat(msg, (char *)body);
 	    strcat(msg, (char *)CRLF );


// attachment
    strcat(msg, (char *)boundary_begin );

   strcat( msg, (char *)attachment );
    strcat(msg, (char *)CRLF );

     strcat(msg, (char *)boundary_end );


        free(attachment);

    return msg;

}



/**
 * buildAttachment
 */
char* buildAttachment(char *filepath,  size_t *msg_size, char *ret_error )
{

    const size_t ATTACH_HEADER_SIZE = 1024;

    const size_t FILENAME_SIZE = 100;
    char filename[FILENAME_SIZE];  
    char ext[FILENAME_SIZE]; 


   const size_t MEDIATYPE_SIZE = 100;
    char media_type[MEDIATYPE_SIZE];


    if( !existsFile( filepath ) ) {
        strcpy(ret_error,  "not found: ");
        strcat(ret_error, filepath);
        return NULL;
    }

    size_t filesize;
    int b64_len;
    char error[ERROR_SIZE];

    char* b64 = getBase64Data( filepath,  &filesize, &b64_len, (char *)error );

    if(!b64){
        strcpy( ret_error, (char *)error );
        return NULL;
    }

    size_t size = b64_len +  ATTACH_HEADER_SIZE;

    char* msg = (char *)malloc(size);

    if(!msg){
        strcpy( ret_error, "getBase64Data malloc faild" );
        free(b64);
        return NULL;
    }


    getFileName( filepath, (char *)filename ) ;


    bool ret = getFileExt( filepath, (char *)ext, (char *)error );

    if(!ret){
        strcpy( ret_error, (char *)error );
        return NULL;
    }

    getMediaType( (char *)ext, (char *)media_type);


// content_type_file
    char content_type_file[HEADER_SIZE];	

    buildContentTypeMediaType( (char *)media_type, (char *)content_type_file );

//  content_disposition
    char content_disposition[HEADER_SIZE];

    buildContentDispotition( (char *)filename,  filesize, (char *) content_disposition );

// build msg
    strcpy( msg, (char *)content_type_file );
    strcat(msg, (char *)CONTENT_TRANSFER_BASE64 );
    strcat( msg, (char *)content_disposition );

	strcat(msg, (char *)CRLF); // separator

    strcat(msg, (char *)b64);
	strcat(msg, (char *)CRLF); 

    *msg_size = size;

    free(b64);

    return msg;
}

