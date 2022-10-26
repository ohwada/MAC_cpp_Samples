/**
 * form_server.c
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/querystring_example.c

#include "server.h"
#include "index_html.h"


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

  const char* FORMAT =  "<h1>Form Server</h1><font size='+2'>%s = &quot;%s&quot; </font>";

    const size_t BUFSIZE = 512;
    char text[BUFSIZE];
    char error[BUFSIZE];
    char buf[BUFSIZE];

  printf("\n method: %s \n", method);
  printf("url: %s \n", url);

  static int aptr;
  const char *val;


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

const char* Q = "name" ;
char* mime = "text/html";

val = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, Q);

printf("val %s \n", val);

    if (val == NULL) 
    {

        get_index_html( (char *)text, (char *)error);
        return response_text_copy( connection, text, mime);
    }

    snprintf (buf, BUFSIZE, FORMAT, Q, val);

    printf("buf: %s \n", buf);

    return response_text_copy( connection, buf, mime);
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
