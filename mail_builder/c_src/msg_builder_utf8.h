#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// build build message

 #include "msg_builder.h"
 #include "msg_builder_base64.h"


// prototype
bool buildMessageUtf8( char *subject, char *to, char *from,  char *body, char *msg, char *ret_error);

bool buildMessageCharset( char *subject,  char *to, char *from, char *body,   char *charset, char *ret_msg, char *ret_error);

bool buildSubjectB64( char *subject, char *charset, char *subject_b64, char *error );

 char* base64encode( char *data, int *ret_size, char *error );


/**
 * buildMessageUtf8
 */
bool buildMessageUtf8( char *subject, char *to, char *from,  char *body, char *msg, char *ret_error)
{
    char error[100];

    bool ret = buildMessageCharset( subject, to, from, body,  (char *)CHARSET_UTF8, msg, (char *)error );

    if(!ret){
        strcpy(ret_error, error);
        return false;
    }

    return true;
}



/**
 * buildMessageCharset
 */
bool buildMessageCharset( char *subject,  char *to, char *from, char *body,   char *charset, char *msg, char *ret_error)
{

    char subject_b64[200];
    char error[100];

    bool ret = buildSubjectB64( subject, charset, (char *)subject_b64, (char *)error );

    if(!ret){
        strcpy(ret_error, error);
        return false;
    }

    int body_b64_size;

    char* body_b64 = base64encode( body, &body_b64_size, (char *)error );

    if(!body_b64){
        strcpy(ret_error, error);
        return false;
    }

    char headers[1024];
    buildHeaders(subject_b64, to, from,  (char *)headers );

    strcpy(msg, (char *)headers);

    strcat(msg, (char *)CONTENT_TYPE_TEXT_PLANE_UTF8 );

    strcat(msg, (char *)CONTENT_TRANSFER_BASE64 );

    strcat(msg, (char *)CRLF );  // separater

    strcat(msg, (char *)body_b64 );

     strcat(msg, (char *)CRLF );

   free(body_b64);

    return true;
}



