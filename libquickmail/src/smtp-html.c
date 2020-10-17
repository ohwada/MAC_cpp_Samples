/**
 *  libquickmail sample
 * 2020-07-01 K.OHWADA
 */

// send mail with html body to SMTP server with TLS and AUTH

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
    const char SUBJECT[] = "libquickmail html";

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
    char body2[] = "This mail has html. \r\n";

    int body3size = 100;
    char body3[ body3size];
    snprintf( body3,   body3size, "This mail was sent using %s \r\n",  getMailer() );

    char body[200];
    strcpy(body, body1);
    strcat(body, body2);
    strcat(body, body3);

    quickmail_set_body(mailobj, body );

    // html
char html1[] = "This is a <b>test</b> e-mail.<br/> \r\n";

    char html2[100];
    sprintf( html2, "This mail was sent using <u> %s </u> \r\n",  getMailer() );

    char html[200];
    strcpy(html, html1);
    strcat(html, html2);

  quickmail_add_body_memory(mailobj, "text/html", html , strlen(html), 0);

    sendMail(mailobj, SERVER, PORT, USER, PASSWD);

  return 0;
}


// < 220 smtp.gmail.com ESMTP t20sm3280819pgj.27 - gsmtp
// > AUTH PLAIN
// < 235 2.7.0 Accepted

