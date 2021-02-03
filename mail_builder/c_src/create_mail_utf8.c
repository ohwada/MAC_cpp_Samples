/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with UTF-8 encoding

// gcc c_src/create_mail_utf8.c 




#include <stdio.h>
#include <stdlib.h>
#include "msg_builder_utf8.h"




/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "utf8 テスト";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

// body
    char body[500];
    strcpy( body, "これはテストメールです。" );
    strcat(body, (char *)CRLF);
    strcat( body, "このメールの文字コードは UTF-8 です。" );
    strcat(body, (char *)CRLF);

    char msg[1024];
    char error[100];

    bool ret= buildMessageUtf8( (char *)SUBJECT, (char *)TO, (char *)FROM, (char *)body, (char *)msg, (char *)error );

    if(!ret){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    printMsg(msg);
    saveMsg(msg);

    return EXIT_SUCCESS;
}


