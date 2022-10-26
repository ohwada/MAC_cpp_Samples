/**
 * https_server.c
 * 2022-06-01 K.OHWADA
 */

// HTTPS Server
// reference : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/https_fileserver_example.c

// curl -v -k https://localhost:8081

// TODO:
// Error: received handshake message out of context.

#include <stdio.h>
#include <stdlib.h>
#include "https_server.h"


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

    char *text = "Hello HTTPS World";
    char *mime = "text/plain";

 return response_text_persistent( connection, text, mime);
}


/**
 * main
 */
int main (int argc, char const *argv[])
{
  
    int port = 8081;

  if (argc == 2) {
        port = atoi (argv[1]);
    } else {
      printf ( "Usage: %s [port] \n", argv[0] );
    }

    printf ("port: %d \n", port);

    const char FILE_KEY[] = "cert/server.key";

    const char FILE_CERT[] = "cert/server.pem";

    run_https_server_file(port, (char *)FILE_KEY, (char *)FILE_CERT);

    return 0;
}
