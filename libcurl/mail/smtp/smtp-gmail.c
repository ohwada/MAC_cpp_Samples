/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server 
// gcc src/smtp-gmail.c `pkg-config --cflags --libs json-c` -lcurl -o gmail

// original : https://curl.haxx.se/libcurl/c/smtp-tls.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2019, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

/* <DESC>
 * SMTP example using TLS
 * </DESC>
 */


#include <stdio.h>
#include "smtp.h"


/* This is a simple example showing how to send mail using libcurl's SMTP
 * capabilities. It builds on the smtp-mail.c example to add authentication
 * and, more importantly, transport security to protect the authentication
 * details from being snooped.
 *
 * Note that this example requires libcurl 7.20.0 or above.
 */

// global
const int g_verbose = 1;


/**
 * payload_source
 */
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    return payload_source_base(ptr, size, nmemb, userp, g_verbose );
}


/**
 *  main
 */
int main(void)
{

    const char SUBJECT[] = "libcurl test";
  
    const long ssl_verify = 1L;

    struct MailParam  p = getGmailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;
    char * FROM = p.from;
    char * TO =  p.to;

  CURL *curl;
  CURLcode res = CURLE_OK;

 struct upload_status upload_ctx = buildUploadStatus((char *)SUBJECT,  FROM,  TO);

  curl = curl_easy_init();
  if(curl) {
    /* We're using a callback function to specify the payload (the headers and
     * body of the message). You could just use the CURLOPT_READDATA option to
     * specify a FILE pointer to read from. */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

    res = sendMail(curl,  URL,USER, PASSWD, FROM, TO, ssl_verify,  g_verbose );

  }

  return (int)res;
}

// < 220 smtp.gmail.com ESMTP q23sm7579351pfl.162 - gsmtp
// > AUTH PLAIN
// < 235 2.7.0 Accepted
