/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// example for how to use libmicrohttpd with HTTP authentication

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/authorization_example.c
/*
     This file is part of libmicrohttpd
     (C) 2008 Christian Grothoff (and other contributing authors)

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
 * @file authorization_example.c
 * @brief example for how to use libmicrohttpd with HTTP authentication
 * @author Christian Grothoff
 */

#include "platform.h"
#include <microhttpd.h>

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body><b>libmicrohttpd demo</b></body></html>"

#define DENIED "<html><head><title>Access denied</title></head><body>Access denied</body></html>"



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
  char *user;
  char *pass;
  int fail;

  if (0 != strcmp (method, "GET"))
    return MHD_NO;              /* unexpected method */
  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }
  *ptr = NULL;                  /* reset when done */

  /* require: "Aladdin" with password "open sesame" */
  pass = NULL;
  user = MHD_basic_auth_get_username_password (connection, &pass);

printf("user: %s \n", user );
printf("pass: %s \n", pass);

  fail = ( (user == NULL) || (0 != strcmp (user, "Aladdin")) || (0 != strcmp (pass, "open sesame") ) );
  if (fail)
  {
      response = MHD_create_response_from_buffer (strlen (DENIED),
						  (void *) DENIED, 
						  MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_basic_auth_fail_response (connection,"TestRealm",response);
    }
  else
    {
      response = MHD_create_response_from_buffer (strlen (me),
						  (void *) me, 
						  MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    }

  MHD_destroy_response (response);
  return ret;
}

int
main (int argc, char *const *argv)
{
  struct MHD_Daemon *d;

    int port = 8080;
    int seconds = 60;

  if (argc == 3){
      port = atoi (argv[1]);
      seconds = atoi (argv[2]);
    } else {
      printf ("%s PORT SECONDS-TO-STOP \n", argv[0]);
    }

  d = MHD_start_daemon ( MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE, MHD_OPTION_END);

    if (d == NULL){
        return 1;
    }

    sleep( seconds );

    MHD_stop_daemon (d);

    return 0;
}
