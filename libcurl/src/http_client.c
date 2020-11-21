/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// very simple HTTP Client
// Get from example.com
// https://curl.haxx.se/libcurl/c/simple.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2018, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 * Very simple HTTP GET
 * </DESC>
 */


#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>


/** 
 * main
 */
int main(int argc, char *argv[])
{

    char *host = "example.com";

   if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] \n",  argv[0] );
    }

    fprintf(stderr, "host: %s \n",  host );


    CURL *curl;
    CURLcode res;
    int ret;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, host);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    /* Check for errors */
     if(res == CURLE_OK){
            ret = EXIT_SUCCESS;
     } else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
            ret = EXIT_FAILURE;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

    return ret;
}


// <title>Example Domain</title>
