/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTP POST using the easy interface
// post to postman-echo.com

// original : https://curl.se/libcurl/c/http-post.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2020, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 ***************************************************************************/
/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>


/** 
 * main
 */
int main(void)
{

    const char URL[] = 
     "http://postman-echo.com/post";

    const char POSTFILEDS[] = "project=curl_mem&name=daniel&age=20";

  CURL *curl;
  CURLcode res;
    int exit;

    bool is_verbose = true;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt( curl, CURLOPT_URL, (char *)URL );

    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (char *)POSTFILEDS );

  /* Switch on full protocol/debug output while testing */
        if (is_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

        /* Check for errors */
        if(res == CURLE_OK) {
            exit =  EXIT_SUCCESS;
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
            exit = EXIT_FAILURE;
        }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return exit;
}


// Connected to postman-echo.com (52.7.61.87) port 80 
// {"project":"curl_mem","name":"daniel","age":"20"}

