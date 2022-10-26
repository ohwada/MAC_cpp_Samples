/**
 * post_session_server.c
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/post_example.c

#include "post_server.h"


/**
 * Front page. (/)
 */
#define MAIN_PAGE "<html><head><title>Welcome</title></head><body><h2>libmicrohttpd POST Server</h2><form action=\"/2\" method=\"post\">What is your name? <input type=\"text\" name=\"v1\" value=\"%s\" /><input type=\"submit\" value=\"Next\" /></form></body></html>"


/**
 * Second page. (/2)
 */
#define SECOND_PAGE "<html><head><title>Tell me more</title></head><body><a href=\"/\">previous</a> <form action=\"/S\" method=\"post\">%s, what is your job? <input type=\"text\" name=\"v2\" value=\"%s\" /><input type=\"submit\" value=\"Next\" /></body></html>"


/**
 * Second page (/S)
 */
#define SUBMIT_PAGE "<html><head><title>Ready to submit?</title></head><body><form action=\"/F\" method=\"post\"><a href=\"/2\">previous </a> <input type=\"hidden\" name=\"DONE\" value=\"yes\" /><input type=\"submit\" value=\"Submit\" /></body></html>"


/**
 * Last page.
 */
#define LAST_PAGE "<html><head><title>Thank you</title></head><body><b>Thank you.</b></body></html>"


/**
 * List of all pages served by this HTTP server.
 */
static struct Page pages[] = 
  {
    { "/", "text/html",  &fill_v1_form, MAIN_PAGE },
    { "/2", "text/html", &fill_v1_v2_form, SECOND_PAGE },
    { "/S", "text/html", &serve_simple_form, SUBMIT_PAGE },
    { "/F", "text/html", &serve_simple_form, LAST_PAGE },
    { NULL, NULL, &not_found_page, NULL } /* 404 */
  };


/**
 * Iterator over key-value pairs where the value
 * maybe made available in increments and/or may
 * not be zero-terminated.  Used for processing
 * POST data.
 *
 * @param cls user-specified closure
 * @param kind type of the value
 * @param key 0-terminated key for the value
 * @param filename name of the uploaded file, NULL if not known
 * @param content_type mime-type of the data, NULL if not known
 * @param transfer_encoding encoding of the data, NULL if not known
 * @param data pointer to size bytes of data at the
 *              specified offset
 * @param off offset of data in the overall value
 * @param size number of bytes in data available
 * @return MHD_YES to continue iterating,
 *         MHD_NO to abort the iteration
 */
static int
post_iterator (void *cls,
	       enum MHD_ValueKind kind,
	       const char *key,
	       const char *filename,
	       const char *content_type,
	       const char *transfer_encoding,
	       const char *data, uint64_t off, size_t size)
{
  struct Request *request = cls;
  struct Session *session = request->session;

  if (0 == strcmp ("DONE", key))
    {
      fprintf (stdout,
	       "Session: `%s' submitted name: `%s', job: `%s' \n",
	       session->sid,
	       session->value_1,
	       session->value_2);

      return MHD_YES;
    }
  if (0 == strcmp ("v1", key))
    {
      if (size + off > sizeof(session->value_1))
	size = sizeof (session->value_1) - off;
      memcpy (&session->value_1[off],
	      data,
	      size);
      if (size + off < sizeof (session->value_1))
	session->value_1[size+off] = '\0';
      return MHD_YES;
    }
  if (0 == strcmp ("v2", key))
    {
      if (size + off > sizeof(session->value_2))
	size = sizeof (session->value_2) - off;
      memcpy (&session->value_2[off],
	      data,
	      size);
      if (size + off < sizeof (session->value_2))
	session->value_2[size+off] = '\0';
      return MHD_YES;
    }
  fprintf (stderr, "Unsupported form value `%s'\n", key);
  return MHD_YES;
}


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

struct MHD_Response *response;
  struct Request *request;
  struct Session *session;
  int ret;
  unsigned int i;

  request = *ptr;
  if (NULL == request)
    {
      request = calloc (1, sizeof (struct Request));
      if (NULL == request)
	{
	  fprintf (stderr, "calloc error: %s\n", strerror (errno));
	  return MHD_NO;
	}
      *ptr = request;
      if (0 == strcmp (method, MHD_HTTP_METHOD_POST))
	{
	  request->pp = MHD_create_post_processor (connection, 1024,
						   (void *)&post_iterator, request );

	  if (NULL == request->pp)
	    {
	      fprintf (stderr, "Failed to setup post processor for `%s'\n",
		       url);
	      return MHD_NO; /* internal error */
	    }
	}
      return MHD_YES;
    }
  if (NULL == request->session)
    {
      request->session = get_session(connection);
      if (NULL == request->session)
	{
	  fprintf (stderr, "Failed to setup session for `%s'\n",
		   url);
	  return MHD_NO; /* internal error */
	}
    }
  session = request->session;
  session->start = time (NULL);
  if (0 == strcmp (method, MHD_HTTP_METHOD_POST))
    {      
      /* evaluate POST data */
      MHD_post_process (request->pp,
			upload_data,
			*upload_data_size);
      if (0 != *upload_data_size)
	{
	  *upload_data_size = 0;
	  return MHD_YES;
	}
      /* done with POST data, serve response */
      MHD_destroy_post_processor (request->pp);
      request->pp = NULL;
      method = MHD_HTTP_METHOD_GET; /* fake 'GET' */
      if (NULL != request->post_url)
	url = request->post_url;
    }

  if ( (0 == strcmp (method, MHD_HTTP_METHOD_GET)) ||
       (0 == strcmp (method, MHD_HTTP_METHOD_HEAD)) )
    {
      /* find out which page to serve */
      i=0;
      while ( (pages[i].url != NULL) &&
	      (0 != strcmp (pages[i].url, url)) )
	i++;
      ret = pages[i].handler (pages[i].handler_cls, 
			      pages[i].mime,
			      session, connection);
      if (ret != MHD_YES)
	fprintf (stderr, "Failed to create page for `%s'\n",
		 url);
      return ret;
    }
  /* unsupported HTTP method */
  response = MHD_create_response_from_buffer (strlen (METHOD_ERROR),
					      (void *) METHOD_ERROR,
					      MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response (connection, 
			    MHD_HTTP_NOT_ACCEPTABLE, 
			    response);

  MHD_destroy_response (response);

  return ret;
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

    run_post_server(port);

  return 0;
}
