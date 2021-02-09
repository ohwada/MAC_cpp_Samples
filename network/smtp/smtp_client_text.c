/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */


// SMTP Client
// send plain text message



#include <stdio.h>
 #include "smtp_header.h"


/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "smtp client test";

    char body[BODY_SIZE];

    strcpy(body, "This is a test mail.");
    strcat(body, (char *)CRLF );
     strcat(body, "This mail was sent using smtp client program.");
    strcat(body, (char *)CRLF );


    char msg[MSG_SIZE];

    buildMsgText( 
    (char *)SUBJECT, 
    (char *)DUMMY_TO, 
    (char *)DUMMY_FROM, 
    (char *)body, 
    (char *)msg );

    printMsg(msg);

    saveMsg(msg);


   char error[ERROR_SIZE];

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

