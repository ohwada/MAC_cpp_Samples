/**
 * test_mail_json.c
 * 2022-06-01 K.OHWADA
 */

// parse mail json file
// test for getGmailParam

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../xoauth2/mail_json.h"


/**
 * main
 */
int main(void) 
{

    struct MailParam p = getGmailParam();
    printMailParam(p);

   char * url = p.smtp_url;
    int port = p.smtp_port;

    assert( strcmp(url, "smtp://smtp.gmail.com:587") == 0);
    assert(port == 587);

    printf("successful \n");

    return EXIT_SUCCESS;;
}

