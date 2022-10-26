#pragma once
/**
 * post_server.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/post_example.c

#include <stdbool.h>
#include "platform.h"
#include <microhttpd.h>
#include "server.h"


/**
 * Invalid method page.
 */
#define METHOD_ERROR "<html><head><title>Illegal request</title></head><body>Go away.</body></html>"


/**
 * Invalid URL page.
 */
#define NOT_FOUND_ERROR "<html><head><title>Not found</title></head><body>Go away.</body></html>"


/**
 * Name of our cookie.
 */
#define COOKIE_NAME "session"


/**
 * State we keep for each user/session/browser.
 */
struct Session
{
  /**
   * We keep all sessions in a linked list.
   */
  struct Session *next;

  /**
   * Unique ID for this session. 
   */
  char sid[33];

  /**
   * Reference counter giving the number of connections
   * currently using this session.
   */
  unsigned int rc;

  /**
   * Time when this session was last active.
   */
  time_t start;

  /**
   * String submitted via form.
   */
  char value_1[64];

  /**
   * Another value submitted via form.
   */
  char value_2[64];

};


/**
 * Data kept per request.
 */
struct Request
{

  /**
   * Associated session.
   */
  struct Session *session;

  /**
   * Post processor handling form data (IF this is
   * a POST request).
   */
  struct MHD_PostProcessor *pp;

  /**
   * URL to serve in response to this POST (if this request 
   * was a 'POST')
   */
  const char *post_url;

};


/**
 * Type of handler that generates a reply.
 *
 * @param cls content for the page (handler-specific)
 * @param mime mime type to use
 * @param session session information
 * @param connection connection to process
 * @param MHD_YES on success, MHD_NO on failure
 */
typedef int (*PageHandler)(const void *cls,
			   const char *mime,
			   struct Session *session,
			   struct MHD_Connection *connection);


/**
 * Entry we generate for each page served.
 */ 
struct Page
{
  /**
   * Acceptable URL for this page.
   */
  const char *url;

  /**
   * Mime type to set for the page.
   */
  const char *mime;

  /**
   * Handler to call to generate response.
   */
  PageHandler handler;

  /**
   * Extra argument to handler.
   */ 
  const void *handler_cls;
};


// prototype
bool run_post_server(int port);
struct Session *
get_session(struct MHD_Connection *connection);
int fill_v1_form (const void *cls,
	      const char *mime,
	      struct Session *session,
	      struct MHD_Connection *connection);
int fill_v1_v2_form (const void *cls,
		 const char *mime,
		 struct Session *session,
		 struct MHD_Connection *connection);
void add_session_cookie (struct Session *session,
		    struct MHD_Response *response);
int serve_simple_form (const void *cls,
		   const char *mime,
		   struct Session *session,
		   struct MHD_Connection *connection);
int not_found_page (const void *cls,
		const char *mime,
		struct Session *session,
		struct MHD_Connection *connection);
void request_completed_callback (void *cls,
			    struct MHD_Connection *connection,
			    void **con_cls,
			    enum MHD_RequestTerminationCode toe);
void expire_sessions();



/**
 * Linked list of all active sessions.  Yes, O(n) but a
 * hash table would be overkill for a simple example...
 */
static struct Session *sessions;


/**
 * run_post_server
 */
bool run_post_server(int port)
{
 struct MHD_Daemon *d;
  struct timeval tv;
  struct timeval *tvp;
  fd_set rs;
  fd_set ws;
  fd_set es;
  int max;
  unsigned MHD_LONG_LONG mhd_timeout;

  /* initialize PRNG */
  srandom ((unsigned int) time (NULL));

  d = MHD_start_daemon (MHD_USE_DEBUG,
                        port,
                        NULL, NULL, 
			(void *)&ahc_echo, NULL, 
			MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 15,
			MHD_OPTION_NOTIFY_COMPLETED, &request_completed_callback, NULL,
			MHD_OPTION_END);

    if (NULL == d) {
        return false;
    }

printf("listen port : %d \n", port);

  while (1)
    {
      expire_sessions();
      max = 0;
      FD_ZERO (&rs);
      FD_ZERO (&ws);
      FD_ZERO (&es);

      if (MHD_YES != MHD_get_fdset (d, &rs, &ws, &es, &max)) {
	break; /* fatal internal error */
      }

      if (MHD_get_timeout (d, &mhd_timeout) == MHD_YES)	
	{
	  tv.tv_sec = mhd_timeout / 1000;
	  tv.tv_usec = (mhd_timeout - (tv.tv_sec * 1000)) * 1000;
	  tvp = &tv;	  
	} else {
	    tvp = NULL;
    }

      select(max + 1, &rs, &ws, &es, tvp);
      MHD_run (d);

    } // while

  MHD_stop_daemon (d);

  return true;
}


/**
 * Return the session handle for this connection, or 
 * create one if this is a new user.
 */
struct Session *
get_session (struct MHD_Connection *connection)
{
  struct Session *ret;
  const char *cookie;

  cookie = MHD_lookup_connection_value (connection,
					MHD_COOKIE_KIND,
					COOKIE_NAME);
  if (cookie != NULL)
    {
      /* find existing session */
      ret = sessions;
      while (NULL != ret)
	{
	  if (0 == strcmp (cookie, ret->sid))
	    break;
	  ret = ret->next;
	}
      if (NULL != ret)
	{
	  ret->rc++;
	  return ret;
	}
    }
  /* create fresh session */
  ret = calloc (1, sizeof (struct Session));
  if (NULL == ret)
    {						
      fprintf (stderr, "calloc error: %s\n", strerror (errno));
      return NULL; 
    }
  /* not a super-secure way to generate a random session ID,
     but should do for a simple example... */
  snprintf (ret->sid,
	    sizeof (ret->sid),
	    "%X%X%X%X",
	    (unsigned int) random (),
	    (unsigned int) random (),
	    (unsigned int) random (),
	    (unsigned int) random ());
  ret->rc++;  
  ret->start = time (NULL);
  ret->next = sessions;
  sessions = ret;
  return ret;
}


/**
 * Handler that adds the 'v1' value to the given HTML code.
 *
 * @param cls a 'const char *' with the HTML webpage to return
 * @param mime mime type to use
 * @param session session handle 
 * @param connection connection to use
 */
int fill_v1_form (const void *cls,
	      const char *mime,
	      struct Session *session,
	      struct MHD_Connection *connection)
{
  int ret;
  const char *form = cls;
  char *reply;
  struct MHD_Response *response;

  reply = malloc (strlen (form) + strlen (session->value_1) + 1);
  snprintf (reply,
	    strlen (form) + strlen (session->value_1) + 1,
	    form,
	    session->value_1);
  /* return static form */
  response = MHD_create_response_from_buffer (strlen (reply),
					      (void *) reply,
					      MHD_RESPMEM_MUST_FREE);
  add_session_cookie (session, response);
  MHD_add_response_header (response,
			   MHD_HTTP_HEADER_CONTENT_ENCODING,
			   mime);
  ret = MHD_queue_response (connection, 
			    MHD_HTTP_OK, 
			    response);
  MHD_destroy_response (response);
  return ret;
}


/**
 * Handler that adds the 'v1' and 'v2' values to the given HTML code.
 *
 * @param cls a 'const char *' with the HTML webpage to return
 * @param mime mime type to use
 * @param session session handle 
 * @param connection connection to use
 */
int fill_v1_v2_form (const void *cls,
		 const char *mime,
		 struct Session *session,
		 struct MHD_Connection *connection)
{
  int ret;
  const char *form = cls;
  char *reply;
  struct MHD_Response *response;

  reply = malloc (strlen (form) + strlen (session->value_1) + strlen (session->value_2) + 1);
  snprintf (reply,
	    strlen (form) + strlen (session->value_1) + strlen (session->value_2) + 1,
	    form,
	    session->value_1);
  /* return static form */
  response = MHD_create_response_from_buffer (strlen (reply),
					      (void *) reply,
					      MHD_RESPMEM_MUST_FREE);
  add_session_cookie (session, response);
  MHD_add_response_header (response,
			   MHD_HTTP_HEADER_CONTENT_ENCODING,
			   mime);
  ret = MHD_queue_response (connection, 
			    MHD_HTTP_OK, 
			    response);
  MHD_destroy_response (response);
  return ret;
}


/**
 * Add header to response to set a session cookie.
 *
 * @param session session to use
 * @param response response to modify
 */ 
void add_session_cookie (struct Session *session,
		    struct MHD_Response *response)
{
  char cstr[256];
  snprintf (cstr,
	    sizeof (cstr),
	    "%s=%s",
	    COOKIE_NAME,
	    session->sid);
  if (MHD_NO == 
      MHD_add_response_header (response,
			       MHD_HTTP_HEADER_SET_COOKIE,
			       cstr))
    {
      fprintf (stderr, 
	       "Failed to set session cookie header!\n");
    }
}


/**
 * Handler that returns a simple static HTTP page that
 * is passed in via 'cls'.
 *
 * @param cls a 'const char *' with the HTML webpage to return
 * @param mime mime type to use
 * @param session session handle 
 * @param connection connection to use
 */
int serve_simple_form (const void *cls,
		   const char *mime,
		   struct Session *session,
		   struct MHD_Connection *connection)
{
  int ret;
  const char *form = cls;
  struct MHD_Response *response;

  /* return static form */
  response = MHD_create_response_from_buffer (strlen (form),
					      (void *) form,
					      MHD_RESPMEM_PERSISTENT);
  add_session_cookie (session, response);
  MHD_add_response_header (response,
			   MHD_HTTP_HEADER_CONTENT_ENCODING,
			   mime);
  ret = MHD_queue_response (connection, 
			    MHD_HTTP_OK, 
			    response);
  MHD_destroy_response (response);
  return ret;
}


/**
 * Handler used to generate a 404 reply.
 *
 * @param cls a 'const char *' with the HTML webpage to return
 * @param mime mime type to use
 * @param session session handle 
 * @param connection connection to use
 */
int not_found_page (const void *cls,
		const char *mime,
		struct Session *session,
		struct MHD_Connection *connection)
{
  int ret;
  struct MHD_Response *response;

  /* unsupported HTTP method */
  response = MHD_create_response_from_buffer (strlen (NOT_FOUND_ERROR),
					      (void *) NOT_FOUND_ERROR,
					      MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response (connection, 
			    MHD_HTTP_NOT_FOUND, 
			    response);
  MHD_add_response_header (response,
			   MHD_HTTP_HEADER_CONTENT_ENCODING,
			   mime);
  MHD_destroy_response (response);
  return ret;
}


/**
 * Callback called upon completion of a request.
 * Decrements session reference counter.
 *
 * @param cls not used
 * @param connection connection that completed
 * @param con_cls session handle
 * @param toe status code
 */
void request_completed_callback (void *cls,
			    struct MHD_Connection *connection,
			    void **con_cls,
			    enum MHD_RequestTerminationCode toe)
{
  struct Request *request = *con_cls;

  if (NULL == request)
    return;
  if (NULL != request->session)
    request->session->rc--;
  if (NULL != request->pp)
    MHD_destroy_post_processor (request->pp);
  free (request);
}


/**
 * Clean up handles of sessions that have been idle for
 * too long.
 */
void expire_sessions()
{
  struct Session *pos;
  struct Session *prev;
  struct Session *next;
  time_t now;

  now = time (NULL);
  prev = NULL;
  pos = sessions;
  while (NULL != pos)
    {
      next = pos->next;
      if (now - pos->start > 60 * 60)
	{
	  /* expire sessions after 1h */
	  if (NULL == prev)
	    sessions = pos->next;
	  else
	    prev->next = next;
	  free (pos);
	}
      else
        prev = pos;
      pos = next;
    }      
}


