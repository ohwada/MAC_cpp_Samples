/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with HTML 

// gcc c_src/create_mail_html.c



#include <stdio.h>
#include <stdlib.h>
#include "msg_builder_html.h"




/**
 * main
 */
int main(void)
{

    const char SUBJECT[] ="mail html";

    const char TO[] = "taro@example.com";

    const char FROM[] = "jiro@example.com";

// plain
    char plain[BODY_SIZE];

    strcpy(plain, "This is test email. ");
    strcat(plain, (char *)CRLF );
    strcat(plain, "this mail has html. " );
    strcat(plain, (char *)CRLF );
    strcat(plain, "this part is plain text. ");
    strcat(plain, (char *)CRLF );


// html
    char html[BODY_SIZE];

    strcpy(html, "This is test email. <br/>");
    strcat(html, (char *)CRLF );
    strcat(html, "this mail has <b>html</b>. <br/>");
    strcat(html, (char *)CRLF );

    strcat(html, "this part is <b>html</b>. <br/>");
    strcat(html, (char *)CRLF );

    char msg[MSG_SIZE];

    buildMessageHtml( 
    (char *)SUBJECT, 
    (char *)TO, 
    (char *)FROM, 
    (char *)plain,  
    (char *)html, 
    (char *)msg );

    printMsg(msg);
    saveMsg(msg);

    return EXIT_SUCCESS;
}


