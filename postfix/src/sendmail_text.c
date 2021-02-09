/**
 * postfix sample
 * 2020-07-01 K.OHWADA
 */


// send plain text mail using sendmail command

// gcc sendmail_text.c `pkg-config --cflags --libs json-c`

// reference : https://stackoverflow.com/questions/9317305/sending-an-email-from-a-c-c-program-in-linux


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "json_mail.h"
#include "msg_builder.h"

/**
 *  sendmail
 */
bool sendmail(char *to, char *msg, char *error)
{

// sendmail command
// -t : read message for recipients. To:, Cc:, and Bcc: lines will be scanned for recipient addresses.
// https://nxmnpg.lemoda.net/1/sendmail#4
   const char CMD_FORMAT[] = "/usr/sbin/sendmail %s";


   const char END[] = ".\r\n";

   //const char CRLF[] = "\r\n";

    const size_t BUFSIZE = 100;
    char cmd[BUFSIZE];

  snprintf(cmd, BUFSIZE,  (char *)CMD_FORMAT, to);

    printf("cmd: %s \n", cmd);


    FILE *fp;

// open pipe stream
    fp = popen( (char *)cmd, "w");

    if (!fp) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
     }

//send message to pipe stream
    //snprintf(buf, BUFSIZE, "To: %s \r\n", to);
    //fwrite(buf, 1, strlen(buf), fp);

    //snprintf(buf, BUFSIZE, "From: %s \r\n", from);
    //fwrite(buf, 1, strlen(buf), fp);

    //snprintf(buf, BUFSIZE, "Subject: %s \r\n", subject);
   //fwrite(buf, 1, strlen(buf), fp);

// splitter
   //fwrite(CRLF, 1, strlen(CRLF), fp);

    //fwrite(body, 1, strlen(body), fp);

    fwrite(msg, 1, strlen(msg), fp);

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

    const char SUBJECT[] = "sendmail test";

    //const char *body = "this mail sent by sendmail command";

    char body[BODY_SIZE];
    strcpy(body, "this is test mail");
    strcat(body, (char *)CRLF);
    strcat(body, "this mail sent by sendmail command");
    strcat(body, (char *)CRLF);

    char msg[MSG_SIZE];
    buildMsgText( 
    (char* )SUBJECT, 
    (char *)TO, 
    (char *)FROM, 
    (char *)body, 
    (char *)msg);

    char error[100];

    bool ret = sendmail( 
    (char *)TO, 
    (char *)msg, 
    (char *)error );

    if(!ret){
        fprintf(stderr, "%s \n", error);
        return EXIT_FAILURE;
    }

    printf("successful \n");

    return EXIT_SUCCESS;
}

