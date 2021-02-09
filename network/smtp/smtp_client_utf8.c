/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */

// SMTP Client
// send message with UTF-8 encoding


#include <stdio.h>
 #include "smtp_header.h"
#include "msg_builder_charset.h"


/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "smtp client テスト";

    char body[BODY_SIZE];

    strcpy(body, "これはテストメールです。");
    strcat(body, (char *)CRLF );
   strcat(body, "このメールの文字コードは UTF-8 です。");
    strcat(body, (char *)CRLF );
     strcat(body, "このメールは smtp client program を使って送信されました。");
    strcat(body, (char *)CRLF );


    char msg[MSG_SIZE];

    buildMessageUtf8( 
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

