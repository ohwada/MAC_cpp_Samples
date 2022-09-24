/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// function for gio stream

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>


// prototype
gboolean stream_write(GOutputStream * ostream, char *data, char *error);
gssize stream_read(  GInputStream * istream, char *buf, size_t bufsize, char *error);


/**
 * stream_write
 */
gboolean stream_write(GOutputStream * ostream, char *data, char *error)
{

  GError * err = NULL;

  gssize size = g_output_stream_write(ostream,
                          data, /* your message goes here */
                          strlen(data), /* length of your message */
                          NULL,
                          &err);
  /* don't forget to check for errors */
    if(size <= 0){
         if (err != NULL)
         {
            strcpy( error, err->message);
        }
    return FALSE;
  }

    return TRUE;
}


/**
 * stream_read
 */
gssize stream_read(  GInputStream * istream, char *buf, size_t bufsize, char *error)
{

    const char CHAR_NULL = '\0';

   GError *err;

// zero clear
    memset(buf, 0, bufsize);

    gssize read_size = g_input_stream_read(istream,
                        (void *)buf,
                        (bufsize -1),
                        NULL,
                        &err);

    if(read_size > 0) {
    // null terminated string
        buf[read_size] = CHAR_NULL;
    } else if( read_size < 0) {
        strcpy( error, err->message );
    }

    return read_size;
}

