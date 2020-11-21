/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS Server

// gcc src/https_server.c `pkg-config --cflags --libs libmicrohttpd` `pkg-config --cflags --libs gnutls`


// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/https_fileserver_example.c
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
 * @file https_server_example.c
 * @brief a simple HTTPS file server using TLS.
 *
 * Usage :
 *
 *  'http_fileserver_example HTTP-PORT SECONDS-TO-RUN'
 *
 * The certificate & key are required by the server to operate,  Omitting the
 * path arguments will cause the server to use the hard coded example certificate & key.
 *
 * 'certtool' may be used to generate these if required.
 *
 * @author Sagie Amir
 */


#include <stdio.h>
#include <stdlib.h>
#include <gnutls/gnutls.h>
#include <gcrypt.h>
#include "server.h"


/**
 * main
 */
int main (int argc, char const *argv[])
{
  struct MHD_Daemon *TLS_daemon;

    int port = 8081;

  if (argc == 2) {
        port = atoi (argv[1]);
    } else {
      printf ( "Usage: %s [port] \n", argv[0] );
    }

    const char FILE_KEY[] = "cert/server.key";

    const char FILE_CERT[] = "cert/server.pem";

    char error[100];

    char* key_pem = readTextFile( (char *)FILE_KEY, (char *)error );
    if(!key_pem){
        fprintf(stderr, "readTextFile: %s: %s \n", FILE_KEY, error );
        return EXIT_FAILURE;
    }

    char* cert_pem = readTextFile( (char *)FILE_CERT, (char *)error );
    if(!cert_pem){
        fprintf( stderr, "readTextFile: %s: %s \n", FILE_CERT, error );
        return EXIT_FAILURE;
    }

      TLS_daemon =
        MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG |
                          MHD_USE_SSL, port, NULL, NULL, (void *)&ahc_echo,
                          NULL, MHD_OPTION_CONNECTION_TIMEOUT, 256,
                          MHD_OPTION_HTTPS_MEM_KEY, key_pem,
                          MHD_OPTION_HTTPS_MEM_CERT, cert_pem,
                          MHD_OPTION_END);


  if (TLS_daemon == NULL)
    {
      fprintf (stderr, "Error: failed to start TLS_daemon\n");
      return EXIT_FAILURE;
    }
  
    printf ("MHD daemon listening on port %d\n", port );
    
// quite when enter any key  
  (void) getc (stdin);

  MHD_stop_daemon (TLS_daemon);

    return EXIT_SUCCESS;
}
