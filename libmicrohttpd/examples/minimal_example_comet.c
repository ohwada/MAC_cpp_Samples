/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// minimal example for how to generate an infinite stream with libmicrohttpd

// Comet
// https://en.wikipedia.org/wiki/Comet_(programming)

// gcc minimal_example_comet.c `pkg-config --cflags --libs libmicrohttpd`

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/minimal_example_comet.c

/*
     This file is part of libmicrohttpd
     (C) 2007, 2008 Christian Grothoff (and other contributing authors)

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
 * @file minimal_example.c
 * @brief minimal example for how to generate an infinite stream with libmicrohttpd
 * @author Christian Grothoff
 */

#include "platform.h"
#include <microhttpd.h>


/**
 * data_generator
 */
static ssize_t
data_generator (void *cls, uint64_t pos, char *buf, size_t max)
{
    if (max < 80) {
        return 0;
    }

  memset (buf, 'A', max - 1);
  buf[79] = '\n';
  return 80;
}


/**
 * ahc_echo
 */
static int
ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{
  static int aptr;
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
  response = MHD_create_response_from_callback (MHD_SIZE_UNKNOWN,
                                                80,
                                                &data_generator, NULL, NULL);
  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);
  return ret;
}


/**
 * main
 */
int main (int argc, char *const *argv)
{

  struct MHD_Daemon *d;

    int port = 8080;

  if (argc == 2){
        port = atoi (argv[1]);
    } else {
      printf ("%s PORT\n", argv[0]);
    }

  d = MHD_start_daemon( 
    MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, NULL, MHD_OPTION_END);

    if (d == NULL) {
        return 1;
    }

// quite when enter any key  
  (void) getc (stdin);

  MHD_stop_daemon (d);

  return 0;
}
