/**
 * mail sample
 * 2020-07-01 K.OHWADA
 */

// parse mail json file
// test for getGmailParam

// gcc pop3/test_mail_json.c  `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include <stdlib.h>
#include "mail_json.h"



/**
 * main
 */
int main(void) 
{

    struct MailParam p1 = getGmailParam();
    printMailParam(p1);

    struct MailParam p2 = getUbuntuMailParam();
    printMailParam(p2);

    return EXIT_SUCCESS;;
}


// smtp_url: smtp://smtp.gmail.com:587 
// smtp_server: smtp.gmail.com 
// smtp_port: 993 
// pop_url: pop3s://pop.gmail.com:995 
// imap_url: imaps://imap.gmail.com:993 
// user: user@gmail.com 
// passwd: password 
// to: user@gmail.com 
// from: user@gmail.com 

