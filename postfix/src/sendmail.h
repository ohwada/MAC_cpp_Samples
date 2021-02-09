/**
 * postfix sample
 * 2020-07-01 K.OHWADA
 */


// send mail using sendmail command


// reference : https://stackoverflow.com/questions/9317305/sending-an-email-from-a-c-c-program-in-linux


#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "json_mail.h"
#include "msg_builder.h"

// constant
const size_t ERROR_SIZE = 100;

// prototype
bool sendmail(char *to, char *msg, char *error);


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

    const size_t CMD_SIZE = 100;
    char cmd[CMD_SIZE];

  snprintf(cmd, CMD_SIZE,  (char *)CMD_FORMAT, to);

    printf("cmd: %s \n", cmd);

    FILE *fp;

// open pipe stream
    fp = popen( (char *)cmd, "w");

    if (!fp) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        return false;
     }

    fwrite(msg, 1, strlen(msg), fp);

    fwrite(END, 1, strlen(END), fp);

    pclose(fp);

    return true;
}
