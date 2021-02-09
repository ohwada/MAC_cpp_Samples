/**
 * postfix sample
 * 2020-07-01 K.OHWADA
 */


// send mail using mail command

// reference : https://www.binarytides.com/linux-mail-command-examples/


#include <stdio.h>
#include <stdlib.h>
#include "json_mail.h"


/**
 *  main
 */
int main(void)
{

    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    char * TO =  p.to;

    const char *subject = "mail test";
    const char *body = "this mail sent by mail command ";

 

    snprintf(buf, BUFSIZE, "echo %s | /usr/bin/mail -s %s %s", body, subject, TO);

    printf("%s \n", buf);

    system(buf);

return EXIT_SUCCESS;
}

