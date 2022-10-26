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

int response_file (
    struct MHD_Connection *connection,
    FILE *fp, size_t file_size, char* mime );

int response_not_found (
    struct MHD_Connection *connection);


#define PAGE_NOT_FOUND "<html><head><title>File not found</title></head><body><b>File not found</b></body></html>"


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
// printf("file_reader \n");
// printf("pos : %llu \n", pos);
// printf("max : %zu \n", max);

  FILE *file = cls;

  (void)  fseek (file, pos, SEEK_SET);
  return fread (buf, 1, max, file);
}


/**
 * free_callback
 */
void free_callback (void *cls)
{
printf("free_callback \n");
  FILE *file = cls;
  fclose (file);
}


/**
 * ahc_echo
 */
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data,
	  size_t *upload_data_size, void **ptr)
{
const char DIR[] = "www";

    char *filename = (char *)&url[1];

    printf("filename: %s \n", filename);

    if( strlen(filename) == 0) {
        filename = "index.html";
    }

    const size_t BUFSIZE = 100;
    char filepath[BUFSIZE];

    snprintf(filepath, BUFSIZE, "%s/%s",  DIR, filename );

    printf("filepath : %s \n", filepath);

  static int aptr;
  struct MHD_Response *response;
  int ret;
  FILE *file;
  struct stat buf;

  if (0 != strcmp (method, MHD_HTTP_METHOD_GET))
    return MHD_NO;              /* unexpected method */
  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }
  *ptr = NULL;                  /* reset when done */

  int ret1 = stat(filepath, &buf);

  if (ret1 == 0){
    file = fopen (filepath, "rb");
  } else {
    file = NULL;
  }

  if (file == NULL)
    {
      response = MHD_create_response_from_buffer (strlen (PAGE),
						  (void *) PAGE,
						  MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_response (connection, MHD_HTTP_NOT_FOUND, response);
      MHD_destroy_response (response);
    }
  else
    {
    size_t file_size = buf.st_size;
    char* mime = get_mime(filepath);
    ret = response_file ( connection,
    file, file_size, mime );
    }

  return ret;
}


/**
 * response_not_found
 */
int response_not_found (
    struct MHD_Connection *connection)
{
printf(" response_not_found \n");

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


/**
 * response_file
 */
int response_file (
    struct MHD_Connection *connection,
    FILE *fp, size_t file_size, char* mime )
{
printf(" response_file \n");

    struct MHD_Response *response;

      response = MHD_create_response_from_callback (file_size, 32 * 1024,     /* 32k page size */
                                                    (void *)&file_reader,
                                                    fp,
                                                    &free_callback);

    if (response == NULL) {
        fprintf(stderr, "cannot create response \n");
	    fclose(fp);
	    return MHD_NO;
    }



    MHD_add_response_header (response, "Content-Type", (char *)mime);

      int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);

      MHD_destroy_response (response);
	  fclose (fp);

    return ret;
}

