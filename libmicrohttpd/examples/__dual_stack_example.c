/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// how to use MHD with both IPv4 and IPv6 support (dual-stack)

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/dual_stack_example.c
/*
     This file is part of libmicrohttpd
     (C) 2007, 2012 Christian Grothoff (and other contributing authors)

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
/**
 * @file dual_stack_example.c
 * @brief how to use MHD with both IPv4 and IPv6 support (dual-stack)
 * @author Christian Grothoff
 */

#include "platform.h"
#include <microhttpd.h>

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body><h1>libmicrohttpd demo</h1></body></html>"

static int
ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{
  static int aptr;
  const char *me = cls;
  struct MHD_Response *response;
  int ret;

  if (0 != strcmp (method, "GET"))
    return MHD_NO;              /* unexpected method */
  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }
  *ptr = NULL;                  /* reset when done */
  response = MHD_create_response_from_buffer (strlen (me),
					      (void *) me,
					      MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);
  return ret;
}

int
main (int argc, char *const *argv)
{
  struct MHD_Daemon *d4;
  struct MHD_Daemon *d6;

    int port = 8080;

    if (argc == 2) {
        port = atoi (argv[1]);
    } else {
        printf ("%s PORT\n", argv[0]);
    }

  d4 = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
			 port,
			 NULL, NULL, (void *)&ahc_echo, PAGE,
			 MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 120,
			 MHD_OPTION_END);

  d6 = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_IPv6,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE,
			MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 120,
			MHD_OPTION_END);

// quite when enter any key 
  (void) getc (stdin);

  MHD_stop_daemon (d4);
  MHD_stop_daemon (d6);

  return 0;
}
