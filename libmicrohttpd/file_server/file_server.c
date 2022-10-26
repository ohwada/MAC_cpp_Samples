/**
 * http_file_server.c
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include "file_server.h"


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

    const size_t BUFSIZE = 512;
    char filepath[BUFSIZE];

    char DIR[] = "www";

    printf("\n method: %s \n", method);
   printf("url: %s \n", url);

    char *filename = (char *)&url[1];

    printf("filename: %s \n", filename);

    if( strlen(filename) == 0) {
        filename = "index.html";
    }

    make_path(DIR, filename, (char *)filepath);

    printf("filepath : %s \n", filepath);

  static int aptr;
  struct MHD_Response *response;
  int ret;

  if (0 != strcmp (method, MHD_HTTP_METHOD_GET))
    return MHD_NO;              /* unexpected method */
  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }
  *ptr = NULL;                  /* reset when done */


if( file_exists( (char* )filepath) ){
// file exists
    response = response_file(filepath);

      if (response == NULL) {
	        return MHD_NO;
	   }

      ret = MHD_queue_response (connection, MHD_HTTP_OK, response);

      MHD_destroy_response (response);

  } else {
// file not found
        ret = response_not_found ( connection);
  }

  return ret;
}


/**
 * main
 */
int main (int argc, char *const *argv)
{

    int port = 8080;

    if (argc == 2) {
        port = atoi( argv[1] );
    } else {
      printf ("Usage: %s [port] \n", argv[0]);
    }

    printf ("port: %d \n", port);

    bool ret = run_server_poling(port);

    if (!ret) {
        fprintf (stderr, "Error: failed to start daemon \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
