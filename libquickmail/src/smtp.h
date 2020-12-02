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
#include <stdbool.h>
#include <string.h>
#include "quickmail.h"
#include "mail_json.h"


//prototype
void buildBody( char *body );
void buildBodyMailer(char *body);
char* getMailer(void);
void addHeader( quickmail mailobj );
 bool sendMail(quickmail mailobj, const char* smtpserver, unsigned int smtpport, const char* username, const char* password, char *error );
void printMessage(quickmail mailobj);


void list_attachment_callback (quickmail mailobj, const char* filename, quickmail_attachment_open_fn email_info_attachment_open, quickmail_attachment_read_fn email_info_attachment_read, quickmail_attachment_close_fn email_info_attachment_close, void* callbackdata)
{
  printf("[%i]: %s\n", ++*(int*)callbackdata, filename);
}


/**
 * buildBody
 */
void buildBody( char *body )
{
    char body1[] = "This is a test e-mail. \r\n";

    char body2[100];
    buildBodyMailer( body2 );

    strcpy(body, body1);
    strcat(body, body2 );
}


/**
 *  buildBodyMailer
 */
void buildBodyMailer(char *body)
{
   const size_t  BUFSIZE = 100;
    char buf[BUFSIZE];
    snprintf( buf,  BUFSIZE, "This mail was sent using %s \r\n",  getMailer() );

    strcpy(body, buf);
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
bool sendMail(quickmail mailobj, const char* smtpserver, unsigned int smtpport, const char* username, const char* password, char *error )
{

    bool is_error = false;
    
    quickmail_set_debug_log(mailobj, stderr);

    const char* errmsg;
    errmsg = quickmail_send(mailobj, smtpserver, smtpport, username, password);

    if (errmsg != NULL) {
        is_error = true;
        strcpy(error, errmsg);
    }

    quickmail_destroy(mailobj);
    quickmail_cleanup();

  return !is_error;
}


/**
 * printMessage
 */
void printMessage(quickmail mailobj)
{
    
    const char* body = quickmail_get_body(mailobj);

    printf("\n");
   printf("---------- \n");
    printf(" %s \n", body);
   printf("---------- \n");
    printf("\n");

}