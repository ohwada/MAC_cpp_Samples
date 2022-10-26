/**
 * hello_server.c
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/minimal_example.c

#include <stdio.h>
#include <string.h>
#include "server.h"


/**
 * ahc_echo
 */
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{

    printf("\n cls: %s \n", cls);
  printf("url: %s \n", url);
  printf("method: %s \n", method);
  printf("version: %s \n", version);
  printf("upload_data: %s \n", upload_data);

  static int aptr;

  if (0 != strcmp (method, "GET")) {
    return MHD_NO;              /* unexpected method */
}

  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }

  *ptr = NULL;                  /* reset when done */

  char *text = "Hello World";
  char *mime = "text/plain";

 return response_text_persistent( connection, text, mime);
}


/**
 * main
 */
int main (int argc, char *const *argv)
{

    int port = 8080;

    if (argc == 2) {
        port = atoi ( argv[1] );
    } else {
        printf ("%s [port] \n", argv[0]);
    }

    printf ("port: %d \n", port);

    run_server(port);

  return 0;
}
