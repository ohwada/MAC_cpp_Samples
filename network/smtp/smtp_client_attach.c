/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */

// SMTP Client
// send message with attached file

// gcc smtp/smtp_client_text.c



#include <stdio.h>
#include "smtp_header.h"
#include "msg_builder_attach.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    const char SUBJECT[] = "smtp client attach";

    char *file = "data/baboon.jpg";


   if (argc == 2) {
        file =   argv[1] ;
    } else {
        printf( "usage: %s [file] \n", argv[0] );
    }

    printf( "file: %s \n", file );


    char body[BODY_SIZE];

    strcpy(body, "This is a test mail.");
    strcat(body, (char *)CRLF );
     strcat(body, "This mail has one attched file.");
    strcat(body, (char *)CRLF );
     strcat(body, "This mail was sent using smtp client program.");
    strcat(body, (char *)CRLF );


    char error[ERROR_SIZE];

    char* msg = buildMsgAttachment( 
    (char *)SUBJECT, 
    (char *)DUMMY_TO, 
    (char *)DUMMY_FROM, 
    (char *)body,  
    (char *)file, 
    (char *)error );

    if(!msg){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }



    saveMsg(msg);


    bool ret = sendMsg( 
    (char *)msg, 
    (char *)error );

    if(!ret){
        printf("%s \n", error);
        return EXIT_FAILURE;
    }

    printf("successful \n");

    return EXIT_SUCCESS;
}
 
 
// connect to: ubuntu : 25 
// * <HELO localhost 
// * >220 VirtualBox ESMTP Postfix (Ubuntu)
