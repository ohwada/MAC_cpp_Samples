/**
 * postfix sample
 * 2020-07-01 K.OHWADA
 */


// send mail using sendmail command

// reference : https://stackoverflow.com/questions/9317305/sending-an-email-from-a-c-c-program-in-linux


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "mail_json.h"


/**
 *  sendmail
 */
bool sendmail(const char *to, const char *from, const char *subject, const char *body, char *error)
{

// sendmail command
// -t : read message for recipients. To:, Cc:, and Bcc: lines will be scanned for recipient addresses.
// https://nxmnpg.lemoda.net/1/sendmail#4
   const char CMD[] = "/usr/sbin/sendmail -t";


   const char END[] = ".\r\n";

   const char CRLF[] = "\r\n";

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];


    FILE *fp;

// open pipe stream
    fp = popen( (char *)CMD, "w");

    if (!fp) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
     }

//send message to pipe stream
    snprintf(buf, BUFSIZE, "To: %s \r\n", to);
    fwrite(buf, 1, strlen(buf), fp);

    snprintf(buf, BUFSIZE, "From: %s \r\n", from);
    fwrite(buf, 1, strlen(buf), fp);

    snprintf(buf, BUFSIZE, "Subject: %s \r\n", subject);
   fwrite(buf, 1, strlen(buf), fp);

// splitter
   fwrite(CRLF, 1, strlen(CRLF), fp);

    fwrite(body, 1, strlen(body), fp);

    fwrite(END, 1, strlen(END), fp);

    pclose(fp);

    return true;
}


/**
 *  main
 */
int main(void)
{

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    char * TO =  p.to;
    char * FROM =  p.from;

    const char *subject= "sendmail test";

    const char *body = "this mail sent by sendmail command";

    char error[100];

    bool ret = sendmail( TO, FROM, subject, body, (char *)error );

    if(!ret){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

