/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create simple text mail 

// gcc c_src/create_mail_text.c



#include <stdio.h>
#include <stdlib.h>
#include "msg_builder.h"





/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "mail text";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

// body
    char body[BODY_SIZE];

    strcpy( body, "This is test email.");
    strcat(body, CRLF);
    strcat (body, "this mail has simple plane text.");
    strcat(body, CRLF);

    char msg[MSG_SIZE];
    buildMsgText( (char *)SUBJECT,  (char *)TO,  (char *)FROM,  (char *)body, (char *)msg);

    printMsg(msg);
    saveMsg(msg);

    return EXIT_SUCCESS;
}


