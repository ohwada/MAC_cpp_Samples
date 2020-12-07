/**
 * glib gio sample
 * 2020-07-01 K.OHWADA
 */

// read and write text file like copying file

// gcc gio/read_write_text_file.c `pkg-config --cflags --libs gio-2.0`

// reference : https://stackoverflow.com/questions/40884738/file-handling-using-gio

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <gio/gio.h>


// prototype
  gboolean read_text_file(char *filepath, char *buf, size_t bufsize, char *error);
  gboolean write_text_file(char *filepath, gchar *buf,   gboolean is_overwrite, char *error);


/**
 * read_text_file
 */
  gboolean read_text_file(char *filepath, char *buf, size_t bufsize, char *error)
{
    const gchar CHAR_NULL = '\0';

    GFile *file = g_file_new_for_path(filepath);

    GError *err = NULL;

    GFileInputStream *in = g_file_read(file, NULL, &err );
    if(!in){
        strcpy(error, err->message);
        return FALSE;
    }

    gboolean is_error = FALSE;

    while (TRUE)
    {
        gssize size = g_input_stream_read( G_INPUT_STREAM(in), (gchar *)buf, (bufsize - 1), NULL, &err );

        if ( size > 0 ) {
        // null terminated string
            buf[size] = CHAR_NULL;
        } else if ( size < 0 ) {
            is_error = TRUE;
            strcpy(error, err->message);
            break;
        } else {
            break;
        }

    } // while

    g_object_unref(file);
    g_object_unref(in);

    return !is_error;
}


/**
 * write_text_file
 */
  gboolean write_text_file(char *filepath, gchar *buf,   gboolean is_overwrite, char *error)
{

// TODO:
// g_file_create
//  occur error when file exists
// check before execution
// The overwriting error message was: File exists


    GFile *file = g_file_new_for_path(filepath);

    GError *err = NULL;

    GFileOutputStream  *out;

    gboolean make_backup = FALSE;

    if( is_overwrite ) {
        out = g_file_replace( file, NULL, G_FILE_CREATE_NONE, make_backup, NULL, &err );
    } else {
        out = g_file_create( file,  G_FILE_CREATE_NONE, NULL, &err );
    }

    if(!out){
        strcpy(error, err->message);
        return FALSE;
    }

    gboolean ret;

    gssize size = g_output_stream_write( G_OUTPUT_STREAM(out),
                (gchar *)buf, strlen(buf), NULL, &err );
    if ( size> 0 ) {
        ret =  TRUE;
    } else {
        strcpy(error, (char *)err->message);
        ret =  FALSE;
    }

    g_object_unref(file);

    g_object_unref(out);

    return ret;
}


/**
 * main
 */
int main(int argc, char *argv[])
{

    char *input = "data/sample.txt";
    char *output = "sample_out.txt";

    gboolean is_overwrite = FALSE;

    if(argc == 4){
      	input = argv[1];
      	output = argv[2];
      	is_overwrite = (gboolean)atoi(argv[3]);
    } else {
        fprintf(stderr, "Usage: %s [input file] [output file] [overwrite] \n",  argv[0] );
    }

    printf("input: %s \n", input);
     printf("output: %s \n", output);
     printf("is_overwrite: %d \n", (int)is_overwrite);

    const size_t BUFSIZE = 1000;
    char buf[BUFSIZE];

    char error[100];

    gboolean ret1 = read_text_file( (char *)input, (char *)buf, BUFSIZE, (char *)error);
    if(!ret1){
        fprintf(stderr, "read file: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("%s \n", buf);

    gboolean ret2 = write_text_file( (char *)output, 
    (char *)buf, is_overwrite, (char *)error );

    if(!ret2){
        fprintf(stderr, "write file: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("write to : %s \n", output);

    return EXIT_SUCCESS;
}
