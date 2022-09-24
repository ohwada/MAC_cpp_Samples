/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// function for HTTP Server'

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
#include <unistd.h>
#include <microhttpd.h>
#include "platform.h"

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body><b>not found</b></body></html>"


//prototype
size_t file_reader(void *cls, uint64_t pos, char *buf, size_t max);
void free_callback (void *cls);
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data,
	  size_t *upload_data_size, void **ptr);

char* readTextFile(char *file, char *error);


/**
 * file_reader
 */
size_t
file_reader(void *cls, uint64_t pos, char *buf, size_t max)
{
  FILE *file = cls;

  (void)  fseek (file, pos, SEEK_SET);
  return fread (buf, 1, max, file);
}


/**
 * free_callback
 */
void free_callback (void *cls)
{
  FILE *file = cls;
  fclose (file);
}


/**
 * ahc_echo
 */
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data,
	  size_t *upload_data_size, void **ptr)
{

    const char DIR[] = "../www";

    char *filename = (char *)&url[1];

    printf("filename: %s \n", filename);

    if( strlen(filename) == 0) {
        filename = "index.html";
    }

    const size_t BUFSIZE = 100;
    char filepath[BUFSIZE];

    snprintf(filepath, BUFSIZE, "%s/%s",  (char *)DIR, filename );

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
                                                    (void *)&file_reader,
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
 * readTextFile
 */
char* readTextFile(char *file, char *error)
{

    const char CHAR_NULL = '\0';

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
     
    int file_size = ftell(fp);

    rewind(fp);

// one big size for the null end than file size
    char* buffer = (char*) malloc(sizeof(char) * (file_size + 1) );

    int read_size = fread(buffer, sizeof(char), file_size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[file_size] = CHAR_NULL;

    if (file_size != read_size){

           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    fclose(fp);

    return buffer;
}
