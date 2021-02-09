/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with Two attached file

// gcc c_src/create_mail_attach_two.c


#include <stdio.h>
#include <stdlib.h>
#include "msg_builder_attach.h"


// prototype
char * buildMsgAttachmentTwo( char * subject, char * to, char * from, char *body,  char *filepath1, char * filepath2, char *ret_error );


/**
 *  buildMsgAttachmentTwo
 */
char * buildMsgAttachmentTwo( char * subject, char * to, char * from, char *body,  char *filepath1, char * filepath2, char *ret_error )
{


    size_t attach_size1;
    size_t attach_size2;
    char error[ERROR_SIZE];

    char *attach1 = buildAttachment( filepath1,  &attach_size1, error );

    if(!attach1){
        strcpy(ret_error, (char *)error);
        return false;
    }

    char *attach2 = buildAttachment( filepath2,  &attach_size2, error );

    if(!attach2){
        strcpy(ret_error, (char *)error);
        return false;
    }

    size_t size = attach_size1 + attach_size2 + HEADERS_SIZE + BODY_SIZE ;
    char *msg = (char *)malloc(size);

    if(!msg){
        strcpy( ret_error, "buildMsgAttachmentTwo malloc faild");
        free(attach1);
        free(attach2);
        return NULL;
    }


// boundary
   char boundary[BOUNDARY_SIZE + 1];
    getRandomBoundary( (char *)boundary );

    char content_type_multipart[HEADER_SIZE];
    char * boundary_begin[HEADER_SIZE];
    char * boundary_end[HEADER_SIZE];

    buildContentTypeMultipartMixed( (char *)boundary,  
    (char *)content_type_multipart,  (char *)boundary_begin, 
    (char *)boundary_end, HEADER_SIZE );


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
   strcat( msg, (char *)attach1 );
    strcat(msg, (char *)CRLF );

    strcat(msg, (char *)boundary_begin );
   strcat( msg, (char *)attach2 );
    strcat(msg, (char *)CRLF );

     strcat(msg, (char *)boundary_end );


        free(attach1);
        free(attach2);

    return msg;

}




/**
 * main
 */
int main(int argc, char* argv[])
{

    const char SUBJECT[] = "mail attach";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

    char *file1 = "data/vegetables.jpg";
    char *file2 = "data/text_utf8.txt";

   if (argc == 3) {
        file1 =   argv[1] ;
        file2 =   argv[2] ;
    } else {
        printf( "usage: %s [file1] [file2] \n", argv[0] );
    }

// body
    char body[BODY_SIZE];
    strcpy(body, "This is test email. ");
    strcat(body, CRLF);
    strcat(body, "this mail has two attached files. ");
    strcat(body, CRLF);

    char error[ERROR_SIZE];

    char* msg = buildMsgAttachmentTwo( (char *)SUBJECT, (char *)TO, (char *)FROM, (char *)body,  (char *)file1,   (char *)file2, (char *)error );

    if(!msg){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    saveMsg(msg);

    free(msg);

    return EXIT_SUCCESS;
}



