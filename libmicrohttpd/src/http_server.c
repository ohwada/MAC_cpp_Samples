/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Server

// gcc src/http_server.c `pkg-config --cflags --libs libmicrohttpd`

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/fileserver_example.c

/*
     This file is part of libmicrohttpd
     (C) 2007 Christian Grothoff (and other contributing authors)

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
 * @file fileserver_example.c
 * @brief minimal example for how to use libmicrohttpd to serve files
 * @author Christian Grothoff
 */

#include <stdio.h>
#include <stdlib.h>
#include "server.h"


/**
 * main
 */
int main (int argc, char *const *argv)
{
  struct MHD_Daemon *d;

    int port = 8080;

    if (argc == 2) {
        port = atoi( argv[1] );
    } else {
      printf ("Usage: %s [port] \n", argv[0]);
    }

  d = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE, MHD_OPTION_END);

    if (d == NULL) {
        fprintf (stderr, "Error: failed to start daemon \n");
        return EXIT_FAILURE;
    }

    printf ("MHD daemon listening on port %d\n", port );

// quite when enter any key  
  (void) getc (stdin);

  MHD_stop_daemon (d);

    return EXIT_SUCCESS;
}
