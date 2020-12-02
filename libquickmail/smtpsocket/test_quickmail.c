/**
 * libquickmail sample
 * 2020-07-01 K.OHWADA
 */

// send mail to SMTP Server with AUTH

// gcc test_quickmail.c quickmail.c smtpsocket.c  `pkg-config --cflags --libs json-c`  -DNOCURL


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
#include <stdbool.h>
#include "quickmail.h"
#include "mail_json.h"


//#define CC          "otheruser@domain.com"
//#define BCC         "otheruser@domain.com"

void list_attachment_callback (quickmail mailobj, const char* filename, quickmail_attachment_open_fn email_info_attachment_open, quickmail_attachment_read_fn email_info_attachment_read, quickmail_attachment_close_fn email_info_attachment_close, void* callbackdata)
{
  printf("[%i]: %s\n", ++*(int*)callbackdata, filename);
}


/**
 * main
 */
int main(void)
{

    const char SUBJECT[] = "libquickmail test";

    const char BODY[] = "This is a test e-mail. \r\nThis mail was sent using libquickmail. \r\n";

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );
    char* SMTPSERVER = p.smtp_server;
    int SMTPPORT = p.smtp_port;
    char* SMTPUSER = p.user;
    char* SMTPPASS = p.passwd;
    char* TO = p.to;
    char* FROM = p.from;

  printf("libquickmail %s\n", quickmail_get_version());

  quickmail_initialize();
  quickmail mailobj = quickmail_create( FROM, (char *)SUBJECT );

  quickmail_add_to(mailobj, TO);

  //quickmail_add_cc(mailobj, CC);
  // quickmail_add_bcc(mailobj, BCC);

// header
  quickmail_add_header(mailobj, "Importance: Low");
  quickmail_add_header(mailobj, "X-Priority: 5");
  quickmail_add_header(mailobj, "X-MSMail-Priority: Low");

// body
  quickmail_set_body(mailobj, (char *)BODY );

  //quickmail_add_body_memory(mailobj, NULL, "This is a test e-mail.\nThis mail was sent using libquickmail.", 64, 0);
  //quickmail_add_body_memory(mailobj, "text/html", "This is a <b>test</b> e-mail.<br/>\nThis mail was sent using <u>libquickmail</u>.", 80, 0);

// attachment
  //quickmail_add_attachment_file(mailobj, "test_quickmail.c", NULL);
  //quickmail_add_attachment_file(mailobj, "test_quickmail.cbp", NULL);
  //quickmail_add_attachment_memory(mailobj, "test.log", NULL, "Test\n123", 8, 0);

// output 
  quickmail_fsave(mailobj, stdout);

  quickmail_set_debug_log(mailobj, stderr);

  const char* errmsg;
  errmsg = quickmail_send(mailobj, SMTPSERVER, SMTPPORT, SMTPUSER, SMTPPASS);

    bool is_error = false;
    if ( errmsg != NULL ) {
        is_error = true;
        fprintf(stderr, "Error sending e-mail: %s\n", errmsg);
    }

// cleanup
    quickmail_destroy(mailobj);
    quickmail_cleanup();

    if(is_error) {
        return EXIT_FAILURE;
    }

      printf("successful \n");

    return EXIT_SUCCESS;
}


// libquickmail 0.1.27
// SMTP< 220 VirtualBox ESMTP Postfix (Ubuntu)
// SMTP< 250 2.0.0 Ok: queued as 79118281EB8


