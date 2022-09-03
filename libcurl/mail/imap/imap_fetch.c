/**
 * imap_fetch.c
 * 2020-07-01 K.OHWADA
 */

// original : https://curl.se/libcurl/c/imap-fetch.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2022, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/

/* <DESC>
 * IMAP example showing how to retreieve emails
 * </DESC>
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "mail_json.h"

/* This is a simple example showing how to fetch mail using libcurl's IMAP
 * capabilities.
 *
 * Note that this example requires libcurl 7.30.0 or above.
 */


/**
 * main
 */
int main(void)
{
    const long ssl_verify= 0L;

    const int BUFSIZE = 256;
    char url[BUFSIZE];

    struct MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    char * IMAP_URL = p.imap_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;

    strcpy(url, IMAP_URL);
    strcat(url, "/INBOX/;UID=1");
    printf("%s \n", url);

  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, USER);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWD);

    /* This will fetch message 1 from the user's inbox */
    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, ssl_verify);

    /* Perform the fetch */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}

// failed: Remote file not found// 