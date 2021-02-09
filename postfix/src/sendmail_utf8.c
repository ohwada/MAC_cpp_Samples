/**
 * postfix sample
 * 2020-07-01 K.OHWADA
 */


// send mail using sendmail command
// mail with UTF-8 encoding

// gcc sendmail_utf8.c `pkg-config --cflags --libs json-c`



#include <stdio.h>
#include <stdlib.h>
#include "sendmail.h"
 #include "msg_builder_charset.h"



/**
 *  main
 */
int main(void)
{

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    char * TO =  p.to;
    char * FROM =  p.from;

    const char SUBJECT[] = "sendmail utf8 テスト";


    char body[BODY_SIZE];
    strcpy(body, "これはテストメールです。");
    strcat(body, (char *)CRLF);
    strcat(body, "このメールの文字コードはUTF8です。");
    strcat(body, (char *)CRLF);
    strcat(body, "このメールは sendmail コマンドで送信されました。");
    strcat(body, (char *)CRLF);

    printf("%s \n", body);

    char msg[MSG_SIZE];

    buildMessageUtf8( 
    (char *)SUBJECT, 
    (char *)TO, 
    (char *)FROM,  
    (char *)body, 
    (char *)msg );


    bool is_save = true;
    if(is_save){
        saveMsg(msg);
    }

    char error[ERROR_SIZE];

    bool ret1 = sendmail( 
    (char *)TO, 
    (char *)msg, 
    (char *)error );

    if(!ret1){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    printf("successful \n");

    return EXIT_SUCCESS;
}

