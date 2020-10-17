/**
 * libquickmail sample
 * 2020-07-01 K.OHWADA
 */

// send mail with attached files to SMTP server with TLS and AUTH

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
#include "smtp.h"



/**
 * main
 */

int main (void)
{
    const char SUBJECT[] = "libquickmail attach";
 
     struct MailParam p = getUbuntuMailParam();
    char* SERVER = p.smtp_server;
    int PORT = p.smtp_port;
    char* USER = p.user;
    char* PASSWD = p.passwd;
    char* TO = p.to;
    char* FROM = p.from;

 quickmail_initialize();

  quickmail mailobj = quickmail_create(FROM, SUBJECT);

  quickmail_add_to(mailobj, TO);

    addHeader(mailobj);

// body
    char body1[] = "This is a test e-mail. \r\n";
    char body2[] = "This mail has two attachments. \r\n";

    char body3[100];
    sprintf( body3, "This mail was sent using %s \r\n",  getMailer() );

    char body[200];
    strcpy(body, body1);
    strcat(body, body2);
    strcat(body, body3);

    quickmail_set_body(mailobj, body );

    // attachment
    quickmail_add_attachment_file(mailobj, "assets/lorem-ipsum.txt", NULL);

    quickmail_add_attachment_file(mailobj, "assets/baboon.png", NULL);

    sendMail(mailobj, SERVER, PORT, USER, PASSWD);

  return 0;
}
