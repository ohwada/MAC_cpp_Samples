#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// http_post_to_memory

// original : https://curl.haxx.se/libcurl/c/http-post.html
// reference  // https://curl.haxx.se/libcurl/c/http2-pushinCurlMemory.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>


/**
 * struct CurlMemory
 */
struct CurlMemory {
  char *memory;
  size_t size;
};


// prototype
int http_post_to_memory(char* url, char* postfileds, struct CurlMemory* mem, int verbose);
size_t  curl_mem_write_cb(void *contents, size_t size, size_t nmemb, void *userp);
void init_CurlMemory(struct CurlMemory *chunk);
void printCurlMemory(struct CurlMemory mem);
int http_post_to_file(char* url, char* postfileds,  char* file, int verbose);
int http_post_to_fp(char* url, char* postfileds,  FILE* fp, int verbose);
size_t  curl_file_write_data(void *ptr, size_t size, size_t nmemb, void *stream);


/**
 *  curl_mem_write_cb
 */
 size_t  curl_mem_write_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct CurlMemory *mem = (struct CurlMemory *)userp;
  char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


/**
 * init_CurlMemory
 */
void init_CurlMemory(struct CurlMemory *chunk)
{
  chunk->memory = (char *)malloc(1);  /* grown as needed with realloc */
  chunk->size = 0;            /* no data at this point */
}



/**
 * http_post_to_memory
 */
int http_post_to_memory(char* url, char* postfileds, struct CurlMemory* mem, int verbose)
{

    CURL *curl;
    CURLcode res;
    int ret;

  /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);

    /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfileds);

  /* Switch on full protocol/debug output while testing */
        if (verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }


  /* write data to a struct  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  curl_mem_write_cb);
        init_CurlMemory(mem);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);


    /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
    /* Check for errors */  
        if(res == CURLE_OK) {
            ret = 0;
        } else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
            ret = 1;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    } // if(curl)

    curl_global_cleanup();

    return ret;
}


/**
 * printCurlMemory
 */
void printCurlMemory(struct CurlMemory mem)
{
    printf("\n" );
    printf("---------- \n" );
    printf("%s \n",  (char *)mem.memory);
    printf("---------- \n" );
}


/**
 * http_post_to_file
 */
int http_post_to_file(char* url, char* postfileds,  char* file, int verbose)
{

    FILE* fp;

  /* open the file */
    fp = fopen(file, "wb");
    if(!fp) {
        printf("fopen faild: %s \n", file);
        return 1;
    }

    return http_post_to_fp(url, postfileds,  fp, verbose);
}


/**
 * http_post_to_fp
 */
int http_post_to_fp(char* url, char* postfileds,  FILE* fp, int verbose)
{

    CURL *curl;
    CURLcode res;
    int ret;

  /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);

    /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfileds);

  /* Switch on full protocol/debug output while testing */
        if (verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

    /* write the page body to this file handle */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  curl_file_write_data);

    /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
    /* Check for errors */  
        if(res == CURLE_OK) {
            ret = 0;
        } else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
            ret = 1;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    } // if(curl)

    curl_global_cleanup();

    return ret;
}


/**
 *  curl_file_write_data
 */
size_t  curl_file_write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
