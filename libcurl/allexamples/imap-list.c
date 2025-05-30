/**
 * limap_list.c
 * 2020-07-01 K.OHWADA
 */


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
 * IMAP example to list the folders within a mailbox
 * </DESC>
 */

#include <stdio.h>
#include <curl/curl.h>
#include "mail_json.h"

/* This is a simple example showing how to list the folders within an IMAP
 * mailbox.
 *
 * Note that this example requires libcurl 7.30.0 or above.
 */


/**
 * main
 */
int main(void)
{
    struct MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    char * IMAP_URL = p.imap_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;

  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, USER);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWD);

    /* This will list the folders within the user's mailbox. If you want to
     * list the folders within a specific folder, for example the inbox, then
     * specify the folder as a path in the URL such as /INBOX */
    curl_easy_setopt(curl, CURLOPT_URL, IMAP_URL);

    /* Perform the list */
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
