/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// minimal example for how to use libmicrohttpd to server files

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/fileserver_example_external_select.c
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
 * @file fileserver_example_external_select.c
 * @brief minimal example for how to use libmicrohttpd to server files
 * @author Christian Grothoff
 */

#include "platform.h"
#include <microhttpd.h>
#include <sys/stat.h>
#include <unistd.h>

#define PAGE "<html><head><title>File not found</title></head><body><b>File not found</b></body></html>"

static ssize_t
file_reader (void *cls, uint64_t pos, char *buf, size_t max)
{
  FILE *file = cls;

  (void) fseek (file, pos, SEEK_SET);
  return fread (buf, 1, max, file);
}

static void
free_callback (void *cls)
{
  FILE *file = cls;
  fclose (file);
}

static int
ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data,
	  size_t *upload_data_size, void **ptr)
{

    char *filename = (char *)&url[1];

    printf("filename: %s \n", filename);

    const size_t BUFSIZE = 100;
    char filepath[BUFSIZE];

    snprintf(filepath, BUFSIZE, "files/%s",  filename );

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
  if ( (0 == stat ( filepath, &buf)) &&
       (S_ISREG (buf.st_mode)) )
    file = fopen ( filepath, "rb");
  else
    file = NULL;
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

int
main (int argc, char *const *argv)
{
  struct MHD_Daemon *d;
  time_t end;
  time_t t;
  struct timeval tv;
  fd_set rs;
  fd_set ws;
  fd_set es;
  int max;
  unsigned MHD_LONG_LONG mhd_timeout;

    int port = 8080;

    int sconds = 60;

    if (argc == 3){
        port = atoi (argv[1]);
        sconds = atoi (argv[2]);
    } else {
      printf ("%s PORT SECONDS-TO-STOP \n", argv[0]);
    }

  d = MHD_start_daemon (MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE, MHD_OPTION_END);

    if (d == NULL) {
        return 1;
    }

  end = time (NULL) + sconds;

  while ((t = time (NULL)) < end)
    {
      tv.tv_sec = end - t;
      tv.tv_usec = 0;
      max = 0;
      FD_ZERO (&rs);
      FD_ZERO (&ws);
      FD_ZERO (&es);
      if (MHD_YES != MHD_get_fdset (d, &rs, &ws, &es, &max))
	break; /* fatal internal error */
      if (MHD_get_timeout (d, &mhd_timeout) == MHD_YES)

        {
          if (tv.tv_sec * 1000 < mhd_timeout)
            {
              tv.tv_sec = mhd_timeout / 1000;
              tv.tv_usec = (mhd_timeout - (tv.tv_sec * 1000)) * 1000;
            }
        }
      select (max + 1, &rs, &ws, &es, &tv);
      MHD_run (d);

    } // while

  MHD_stop_daemon (d);

  return 0;
}
