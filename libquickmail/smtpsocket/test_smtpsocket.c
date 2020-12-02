/**
 * libquickmail sample
 * 2020-07-01 K.OHWADA
 */

// test for smtpsocket.c
// send mail to SMTP Server

// gcc test_smtpsocket.c smtpsocket.c

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
#include <string.h>
#include "smtpsocket.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    const char SUBJECT[] = "smtpsocket test";

    const char BODY[] = "This is a test mail. \r\nThis mail was sent using libquickmail smtpsocket. \r\n";

    const char EHLO_FORMAT[] = "EHLO %s";

    const char LOCAL_HOSTNAME[] = "localhost";

    const char MAIL_FROM_FORMAT[] = 
    "MAIL FROM: %s ";

    const char RCPT_TO_FORMAT[] = 
    "RCPT TO: %s ";

    const char CMD_DATA[] = "DATA";

    const char END_OF_DATA[] = "\r\n.";

    const char CMD_QUIT[] = "QUIT";

    const size_t BUFSIZE = 1024;
    char message[BUFSIZE];

    char * server = "ubuntu";
    unsigned int  port = 25;
    char * to =  "taro";
    char * from = "hoge@example.com";

  if(argc == 4){
        server = argv[1];
        port = atoi( argv[2]);
        to = argv[3];
} else {
     printf("Usage: %s [host] [port] [to] \n",  argv[0] );
}

    printf( "server: %s \n", server );
    printf( "port: %d \n", port );
    printf( "to: %s \n", to );


// build massage
    snprintf(message, BUFSIZE, "From: %s \r\n To: %s \r\nSubject: %s \r\n\r\n %s ", from, to, (char *)SUBJECT, (char *)BODY);

    printf( "%s \n", message );

  //connect
  SOCKET sock;
  char* errmsg = NULL;

    sock = socket_open( server, port, &errmsg);
    if ( sock == INVALID_SOCKET) {
            fprintf(stderr, "socket_open: %s\n", errmsg);
            return EXIT_FAILURE;
    }

    printf( "connected: %s : %d \n", server, port );

    //talk with SMTP server
    FILE* debuglog = stderr;
    int statuscode;
    statuscode = socket_smtp_command(sock, debuglog, NULL);

    if ( statuscode >= 400 ) {
        errmsg = "SMTP server returned an error on connection";
        goto label_error;
    }


// send EHLO
    statuscode = socket_smtp_command(sock, debuglog, (char *)EHLO_FORMAT, (char *)LOCAL_HOSTNAME );

    if(  statuscode >= 400 ) {
            errmsg = "SMTP EHLO/HELO returned error";
            goto label_error;
    }


//send originator e-mail address
    statuscode = socket_smtp_command(sock, debuglog, 
    (char *)MAIL_FROM_FORMAT, from );

    if ( statuscode >= 400 ) {
            errmsg = "SMTP server did not accept sender";
            goto label_error;
    }


// send recipent address
    statuscode = socket_smtp_command(sock, debuglog, 
    (char *)RCPT_TO_FORMAT, to );

    if( statuscode >= 400 ) {
            errmsg = "SMTP server did not accept e-mail address (To)";
            goto label_error;
    }


//prepare to send mail message
    statuscode = socket_smtp_command(sock, debuglog,  (char *)CMD_DATA );

    if ( statuscode >= 400 ) {
        errmsg = "SMTP DATA returned error";
        goto label_error;
    }


//send mail message
    int send_size = socket_send(sock, message, strlen(message) );

if( send_size <= 0 ){
         errmsg = "socket_send failed";
        goto label_error;
}

//send end of data
    statuscode = socket_smtp_command(sock, debuglog, (char *)END_OF_DATA);

    if ( statuscode >= 400 ) {
            errmsg = "SMTP error after sending message data";
            fprintf(stderr, "Error: %s\n", errmsg);
            return EXIT_FAILURE;
    }

//log out
    statuscode = socket_smtp_command(sock, debuglog, (char *)CMD_QUIT );

    if ( statuscode >= 400 ) {
         errmsg = "SMTP error after sending QUIT";
        fprintf(stderr, "Error: %s\n", errmsg);
    }

//close socket
    socket_close(sock);

  // quickmail_destroy(mailobj);
  // quickmail_cleanup();

      printf("successful \n");

    return EXIT_SUCCESS;


label_error:

    if(sock){
        socket_close(sock);
    }

    if( errmsg){
        fprintf(stderr, "Error: %s\n", errmsg);
    }

    return EXIT_FAILURE;
}


// connected: ubuntu : 25
// SMTP< 220 VirtualBox ESMTP Postfix (Ubuntu)


