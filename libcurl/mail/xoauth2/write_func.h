#pragma once
/**
 * write_func.h
 * 2020-07-01 K.OHWADA
 */

// http to file or memory

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
size_t  curl_mem_write_cb(void *contents, size_t size, size_t nmemb, void *userp);
size_t  curl_file_write_data(void *ptr, size_t size, size_t nmemb, void *stream);
void initCurlMemory(struct CurlMemory *chunk);
void printCurlMemory(struct CurlMemory mem);



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
 *  curl_file_write_data
 */
size_t  curl_file_write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}


/**
 * initCurlMemory
 */
void initCurlMemory(struct CurlMemory *chunk)
{
   chunk->memory = (char *)malloc(1);  /* grown as needed with realloc */
  chunk->size = 0;            /* no data at this point */
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
