#pragma once
/**
 * libquickmail sample
 * 2020-07-01 K.OHWADA
 */

// common function for SMTP client
// original : https://github.com/cdevelop/libquickmail/blob/master/test_quickmail.c

/*
    This file is part of libquickmail.

    libquickmail is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libquickmail is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libquickmail.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <string.h>
#include "quickmail.h"
#include "mail_json.h"


//prototype
void buildMail( quickmail mailobj);
char* getMailer(void);
void addHeader( quickmail mailobj );
 void sendMail(quickmail mailobj, const char* smtpserver, unsigned int smtpport, const char* username, const char* password);

void list_attachment_callback (quickmail mailobj, const char* filename, quickmail_attachment_open_fn email_info_attachment_open, quickmail_attachment_read_fn email_info_attachment_read, quickmail_attachment_close_fn email_info_attachment_close, void* callbackdata)
{
  printf("[%i]: %s\n", ++*(int*)callbackdata, filename);
}


/**
 * buildMail
 */
void buildMail( quickmail mailobj )
{
    char body1[] = "This is a test e-mail. \r\n";

    int body2size = 100;
    char body2[body2size];
    snprintf( body2, body2size, "This mail was sent using %s \r\n",  getMailer() );

    char body[200];
    strcpy(body, body1);
    strcat(body, body2 );

    addHeader( mailobj );
    quickmail_set_body(mailobj, body );
}


/**
 *  addHeader
 */
void addHeader( quickmail mailobj )
{

    int xmailersize = 100;
    char xmailer[xmailersize];
    snprintf(xmailer,  xmailersize, "X-Mailer: %s ",  getMailer() );

  quickmail_add_header(mailobj, "Importance: Low");
  quickmail_add_header(mailobj, "X-Priority: 5");
  quickmail_add_header(mailobj, "X-MSMail-Priority: Low");
  quickmail_add_header(mailobj,  xmailer );
}


/**
 *  getMailer
 */
char* getMailer(void)
{
    const size_t bufsize = 100;
    static char buff[bufsize];
    snprintf(buff, bufsize, "libquickmail %s", quickmail_get_version());
    return buff;
}



/**
 * sendMail
 */
void sendMail(quickmail mailobj, const char* smtpserver, unsigned int smtpport, const char* username, const char* password)
{

    printf( "smtpserver: %s \n", smtpserver );
    printf( "username: %s \n", username );
    printf( "password: %s \n", password );

    quickmail_set_debug_log(mailobj, stderr);

    const char* errmsg;
    errmsg = quickmail_send(mailobj, smtpserver, smtpport, username, password);
    if (errmsg != NULL) {
    fprintf(stderr, "Error sending e-mail: %s\n", errmsg);
    }

    quickmail_destroy(mailobj);
    quickmail_cleanup();

  return ;
}
