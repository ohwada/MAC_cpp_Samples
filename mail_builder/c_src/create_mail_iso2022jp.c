/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with ISO-2022-jp encoding

// require libiconv <br/>
// gcc c_src/create_mail_iso2022jp.c  `pkg-config --cflags --libs iconv` 




#include <stdio.h>
#include <stdlib.h>
#include "msg_builder_charset.h"
#include "iso2022jp.h"



/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "iso2022jp テスト";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

// body
    char body[BODY_SIZE];
    strcpy( body, "これはテストメールです。" );
    strcat(body, (char *)CRLF);
    strcat( body, "このメールの文字コードは ISO-2022-JP です。" );
    strcat(body, (char *)CRLF);


    char subject_iso2022[CONV_BUFSIZE];
    char body_iso2022[CONV_BUFSIZE];
     char error[CONV_ERROR_SIZE];

    bool ret1 = utf8_to_iso2022jp(
    (char *)SUBJECT, 
    strlen(SUBJECT),
    (char *)subject_iso2022, 
    CONV_BUFSIZE, 
    (char *)error );

    if( !ret1 ){
        fprintf(stderr, "utf8_to_iso2022jp: %s \n", error );
        return EXIT_FAILURE;
    }

    bool ret2 = utf8_to_iso2022jp(
    (char *)body, 
    strlen(body),
    (char *)body_iso2022, 
    CONV_BUFSIZE, 
    (char *)error );

    if( !ret2 ){
        fprintf(stderr, "utf8_to_iso2022jp: %s \n", error );
        return EXIT_FAILURE;
    }


    char msg[MSG_SIZE];

    buildMessageCharset( 
    (char *)subject_iso2022,  
    (char *)TO, 
    (char *)FROM, 
    (char *)body_iso2022, 
    (char *)CHARSET_ISO2022JP,
    (char *)msg );

    printMsg(msg);
    saveMsg(msg);

    return EXIT_SUCCESS;
}


