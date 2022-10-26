#pragma once
/**
 * file_server.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/fileserver_example.c


#include "server.h"
#include "file_util.h"
#include "mime.h"


//prototype
bool run_server_poling(int port);
size_t file_reader(void *cls, uint64_t pos, char *buf, size_t max);
void free_callback (void *cls);
struct MHD_Response* 
response_file(char *filepath);
int response_not_found (
struct MHD_Connection *connection);


#define PAGE_NOT_FOUND "<html><head><title>File not found</title></head><body><b>File not found</b></body></html>"


const bool is_verbose = true;


/**
 * run_server
 */
bool run_server_poling(int port)
{
  struct MHD_Daemon *d;

  d = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE_NOT_FOUND, MHD_OPTION_END);

  if (d == NULL) {
    return false;
}

printf("listen port : %d \n", port);

// quite when enter any key  
(void) getc (stdin);

  MHD_stop_daemon (d);

  return true;
}


/**
 * file_reader
 */
size_t
file_reader(void *cls, uint64_t pos, char *buf, size_t max)
{
    if(is_verbose){
        printf("file_reader \n");
        printf("pos: %llu, max: %zu \n", pos, max);
    }

  FILE *file = cls;

  (void)  fseek (file, pos, SEEK_SET);
  return fread (buf, 1, max, file);
}


/**
 * free_callback
 */
void free_callback (void *cls)
{
    if(is_verbose){
        printf("free_callback \n");
    }

  FILE *file = cls;
  fclose (file);
}



struct MHD_Response* 
response_file(char *filepath)
{
struct MHD_Response* response;
  FILE *file;
    file = fopen (filepath, "rb");
    size_t file_size = get_file_size(filepath);
    char* mime = get_mime(filepath);

    if(is_verbose){
        printf("file size: %zu \n", file_size);
        printf("mime: %s \n", mime);
    }

      if (file == NULL) {
	    return NULL;
	}

    response =  MHD_create_response_from_callback (
file_size, 32 * 1024,     /* 32k page size */
                                                     (void *)&file_reader,
                                                    file,
                                                    &free_callback);

      if (response == NULL) {
	    fclose (file);
	    return NULL;
	}

   MHD_add_response_header (response, "Content-Type", mime);

    return response;
}


/**
 * response_not_found
 */
int response_not_found (
    struct MHD_Connection *connection)
{
    if(is_verbose){
        printf(" response_not_found \n");
    }

    struct MHD_Response *response;

      response = MHD_create_response_from_buffer (strlen (PAGE_NOT_FOUND),
						  (void *) PAGE_NOT_FOUND,
						  MHD_RESPMEM_PERSISTENT);

    if (response == NULL) {
	    return MHD_NO;
	}

    char *mime = "text/html";
    MHD_add_response_header (response, "Content-Type", mime);

      int ret = MHD_queue_response (connection, MHD_HTTP_NOT_FOUND, response);

      MHD_destroy_response (response);

    return ret;
}

