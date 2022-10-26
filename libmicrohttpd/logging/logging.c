/**
 * logging.c
 * 2022-06-01 K.OHWADA
 */

// original : https://www.gnu.org/software/libmicrohttpd/tutorial.html#logging_002ec

/* Feel free to use this example code in any way
   you see fit (Public Domain) */

#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8888

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body><h1>libmicrohttpd demo</h1></body></html>"


/**
 * print_out_key
 */
static enum MHD_Result
print_out_key (void *cls, enum MHD_ValueKind kind, const char *key,
               const char *value)
{
  (void) cls;    /* Unused. Silent compiler warning. */
  (void) kind;   /* Unused. Silent compiler warning. */
  printf ("%s: %s\n", key, value);
  return MHD_YES;
}


/**
 * answer_to_connection
 */
static enum MHD_Result
answer_to_connection (void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls)
{
  (void) cls;               /* Unused. Silent compiler warning. */
  (void) version;           /* Unused. Silent compiler warning. */
  (void) upload_data;       /* Unused. Silent compiler warning. */
  (void) upload_data_size;  /* Unused. Silent compiler warning. */
  (void) con_cls;           /* Unused. Silent compiler warning. */
  printf ("\n New %s request for %s using version %s\n", method, url, version);

  MHD_get_connection_values (connection, MHD_HEADER_KIND, print_out_key,
                             NULL);

  // return MHD_NO;

  const char* text = PAGE;
  struct MHD_Response *response;
  response = MHD_create_response_from_buffer (strlen (text),
					      (void *)text,
					      MHD_RESPMEM_PERSISTENT);
  int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);
  return ret;
}


/**
 * main
 */
int main ()
{
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                             &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;

printf("listen port: %d \n", PORT);

  (void) getchar ();

  MHD_stop_daemon (daemon);
  return 0;
}

