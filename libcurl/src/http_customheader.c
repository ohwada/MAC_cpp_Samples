/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// http request to postman echo server
// with custom headers
// reference : https://curl.haxx.se/libcurl/c/httpcustomheader.html

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
 * HTTP request with custom modified, removed and added headers
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>


/**
 * main
 */
int main(void)
{

    const char URL[] = "https://postman-echo.com/headers";

    CURL *curl;
    CURLcode res;
    int ret;

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;

    /* Remove a header curl would otherwise add by itself */
    chunk = curl_slist_append(chunk, "Accept:");

    /* Add a custom header */
    chunk = curl_slist_append(chunk, "Another: yes");

    /* Modify a header curl otherwise adds differently */
    chunk = curl_slist_append(chunk, "Host: example.com");

    /* Add a header with "blank" contents to the right of the colon. Note that
       we're then using a semicolon in the string we pass to curl! */
    chunk = curl_slist_append(chunk, "X-silly-header;");

    /* set our custom set of headers */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res == CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        ret = EXIT_SUCCESS;
    } else {
        ret = EXIT_FAILURE;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* free the custom headers */
    curl_slist_free_all(chunk);
  }

    return ret;
}


// {"headers":{"x-forwarded-proto":"https","x-forwarded-port":"443","host":"example.com","x-amzn-trace-id":"Root=1-5f851355-2e8b6c2778b399315317123c","another":"yes","x-silly-header":""}}

