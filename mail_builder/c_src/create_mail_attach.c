/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with attached file

// gcc c_src/create_mail_attach.c 


#include <stdio.h>
#include <stdlib.h>
#include "msg_builder_attach.h"



/**
 * main
 */
int main(int argc, char* argv[])
{

    const char SUBJECT[] = "mail attach";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

    char *file = "data/baboon.jpg";

   if (argc == 2) {
        file =   argv[1] ;
    } else {
        printf( "usage: %s [file] \n", argv[0] );
    }


// body
    char body[BODY_SIZE];
    strcpy(body, "This is test email. ");
    strcat(body, CRLF);
    strcat(body, "this mail has one attached file. ");
    strcat(body, CRLF);


    char error[ERROR_SIZE];

    char* msg = buildMsgAttachment( (char *)SUBJECT, (char *)TO, (char *)FROM, (char *)body,  (char *)file, (char *)error );

    if(!msg){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    saveMsg(msg);

    free(msg);

    return EXIT_SUCCESS;
}


