/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// get list from IMAP server with SSL

// original : https://curl.haxx.se/libcurl/c/imap-ssl.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 * IMAP example using SSL
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "mail_json.h"


/* This is a simple example showing how to fetch mail using libcurl's IMAP
 * capabilities. It builds on the imap-fetch.c example adding transport
 * security to protect the authentication details from being snooped.
 *
 * Note that this example requires libcurl 7.30.0 or above.
 */


int main(void)
{

    const bool is_verbose = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const long ssl_verify= 0L;

    struct MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    char * IMAP_URL = p.imap_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;

    CURL *curl;
    CURLcode res = CURLE_OK;
    int ret;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, USER );
    curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWD);

    /* This will fetch message 1 from the user's inbox. Note the use of
    * imaps:// rather than imap:// to request a SSL based connection. */
    curl_easy_setopt(curl, CURLOPT_URL,  IMAP_URL );

 
    /* If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you. */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, ssl_verify);

    /* If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure. */
#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Since the traffic will be encrypted, it is very useful to turn on debug
     * information within libcurl to see what is happening during the
     * transfer */
    if (is_verbose){
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    /* Perform the fetch */
    res = curl_easy_perform(curl);

    /* Check for errors */
        if(res == CURLE_OK){
            ret = EXIT_SUCCESS;
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
            ret = EXIT_FAILURE;
        }
 
    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return ret;
}

 
// Connected to ubuntu (192.168.99.100) port 993 (#0)
// < * LIST (\HasNoChildren) "/" INBOX
// < A003 OK List completed (0.001 + 0.000 secs).

