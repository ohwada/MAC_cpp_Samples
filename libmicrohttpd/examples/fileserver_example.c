/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// minimal example for how to use libmicrohttpd to serve files

// gcc fileserver_example.c `pkg-config --cflags --libs libmicrohttpd`

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

#include "platform.h"
#include <microhttpd.h>
#include <unistd.h>

#define PAGE "<html><head><title>File not found</title></head><body><b>File not found</b></body></html>"


/**
 * file_reader
 */
static ssize_t
file_reader (void *cls, uint64_t pos, char *buf, size_t max)
{
  FILE *file = cls;

  (void)  fseek (file, pos, SEEK_SET);
  return fread (buf, 1, max, file);
}


/**
 * free_callback
 */
static void
free_callback (void *cls)
{
  FILE *file = cls;
  fclose (file);
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
          const char *upload_data,
	  size_t *upload_data_size, void **ptr)
{

    const char DIR[] = "www";

    char *filename = (char *)&url[1];

    printf("filename: %s \n", filename);

    const size_t BUFSIZE = 100;
    char filepath[BUFSIZE];

    snprintf(filepath, BUFSIZE, "%s/%s",  DIR, filename );

    printf("filepath : %s \n", filepath);

  static int aptr;
  struct MHD_Response *response;
  int ret;
  FILE *file;
  struct stat buf;

  if (0 != strcmp (method, MHD_HTTP_METHOD_GET))
    return MHD_NO;              /* unexpected method */
  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }
  *ptr = NULL;                  /* reset when done */
  if (0 == stat (filepath, &buf)){
    file = fopen (filepath, "rb");
  } else {
    file = NULL;
  }

  if (file == NULL)
    {
      response = MHD_create_response_from_buffer (strlen (PAGE),
						  (void *) PAGE,
						  MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_response (connection, MHD_HTTP_NOT_FOUND, response);
      MHD_destroy_response (response);
    }
  else
    {
      response = MHD_create_response_from_callback (buf.st_size, 32 * 1024,     /* 32k page size */
                                                    &file_reader,
                                                    file,
                                                    &free_callback);
      if (response == NULL)
	{
	  fclose (file);
	  return MHD_NO;
	}
      ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
      MHD_destroy_response (response);
    }
  return ret;
}


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
      printf ("%s PORT\n", argv[0]);
    }

  d = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE, MHD_OPTION_END);

    if (d == NULL) {
        return 1;
    }

// quite when enter any key  
  (void) getc (stdin);

  MHD_stop_daemon (d);

  return 0;
}
