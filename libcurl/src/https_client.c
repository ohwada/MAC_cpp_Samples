/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// Simple HTTPS Client
// Get web from example.com

// original : https://curl.haxx.se/libcurl/c/https.html

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
 * Simple HTTPS GET
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>


/**
 * main
 */
int main(int argc, char *argv[])
{

    char *host = "example.com";

    bool is_verify = true;

  if(argc == 3) {
      	host = argv[1];
      	is_verify = (bool)atoi(argv[2]);
  } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] \n",  argv[0] );
    }

// add URI scheme "https"
    const size_t BUFSIZE = 100;
    char url[BUFSIZE];

    snprintf(url, BUFSIZE, "https://%s", (char *)host );

    fprintf(stderr, "host: %s \n",  host );
    fprintf(stderr, "url: %s \n",  url );

    CURL *curl;
    CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

    int exit;

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,  (char *)url);

        if (is_verify) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        } else {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res == CURLE_OK) {
        exit = EXIT_SUCCESS;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        exit = EXIT_FAILURE;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

  } //   if(curl) 

  curl_global_cleanup();

    return exit;
}


// <title>Example Domain</title>

