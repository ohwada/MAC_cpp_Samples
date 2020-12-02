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
#include <stdlib.h>
#include "smtp.h"


/**
 * buildCustomBody
 */
void buildCustomBody(char *body)
{

    const char body1[] = "This is a test e-mail. \r\n";

    const char body2[] = "This mail has html. \r\n";

    char body3[100];
    buildBodyMailer( body3 );

    strcpy(body, body1);
    strcat(body, body2);
    strcat(body, body3);
}


/**
 * buildHtml
 */
void buildHtml(char *html)
{

    const char html1[] = "This is a <b>test</b> e-mail.<br/> \r\n";

    char html2[100];
    sprintf( html2, "This mail was sent using <u> %s </u> \r\n",  getMailer() );

    strcpy(html, html1);
    strcat(html, html2);
}


/**
 * main
 */
int main (void)
{
    const char SUBJECT[] = "libquickmail html";

    struct MailParam p = getUbuntuMailParam();
    printMailParam(p);
    char* SERVER = p.smtp_server;
    int PORT = p.smtp_port;
    char* USER = p.user;
    char* PASSWD = p.passwd;
    char* TO = p.to;
    char* FROM = p.from;

// build body
    char body[1024];
    buildCustomBody( body );

// buildHtml
     char html[1024];
    buildHtml(html);

 quickmail_initialize();

  quickmail mailobj = quickmail_create(FROM, SUBJECT);

  quickmail_add_to(mailobj, TO);

    addHeader(mailobj);

    quickmail_set_body(mailobj, body );

    quickmail_add_body_memory(mailobj, "text/html", html , strlen(html), 0);

    char error[100];
    bool ret = sendMail(mailobj, SERVER, PORT, USER, PASSWD, error);

    if(!ret){
        fprintf(stderr, "Error sending e-mail: %s \n", error );
        return EXIT_FAILURE;
    } 

      printf("successful \n");

    return EXIT_SUCCESS;
}


// < 220 smtp.gmail.com ESMTP t20sm3280819pgj.27 - gsmtp
// > AUTH PLAIN
// < 235 2.7.0 Accepted

