/**
 * insert_image.c
 * 2022-06-01 K.OHWADA
 */

// inset image data into mysql table
// with base64 encoding
// by loading image from file


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "file_util.h"
#include "c_parse_filename.h"
#include "blob_type.h"
#include "base64.h"
#include "bin_hex.h"


/**
 * main
 */
int main(int argc, char* argv[])
{
    const size_t BUFSIZE = 255;
    char fname[ BUFSIZE];
    char error[ BUFSIZE];

    const int ZERO = 0x00;

char* fpath = "images/mysql_logo.png";

unsigned short type = TYPE_BASE64;

    if(argc == 3) {
      	fpath = argv[1];
      	type = atoi(argv[2]);
    } else if(argc == 2) {
      	fpath = argv[1];
    } else {
        printf("Usage: %s [imgFile] [type] \n",  argv[0]);
    }

    printf("fpath: %s \n", fpath);
    printf("type: %d , %s \n", type, type_to_string(type) );

    strcpy( fname, get_filename_with_ext(fpath) );
    printf("fname: %s \n", fname);

// === file ===

    size_t img_size;

    char* img_data = file_binary_read( fpath, &img_size, (char *)error);
    if( !img_data ||(img_size == 0) ){
        fprintf(stderr, "file_binary_read: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("img size: %zu \n", img_size);

    char* data;

    if(type == TYPE_BASE64) {
        data = base64Encode(img_data, img_size, BASE64_TYPE_STANDARD);
    } else if(type == TYPE_HEX) {
        data = bin2hex(img_data, img_size);
    }

    free(img_data);

// === mysql ===

  MYSQL *conn     = NULL;
  char *sql_serv  = "localhost";
  char *user      = "root";
  char *passwd    = "";
  char *db_name   = "db_test";


size_t  data_len = strlen(data);
printf("data len: %zu \n", data_len);

size_t  sql_size = data_len + 128;
char sql_str[sql_size];

// clear query string
  memset( &sql_str[0] , ZERO, sql_size );

// mysql connection
  conn = mysql_init(NULL);

unsigned int port = 0;
const char *unix_socket = NULL;
 unsigned long client_flag = 0;

MYSQL *mysql = mysql_real_connect(conn, sql_serv, user, passwd, db_name, port, unix_socket, client_flag);

  if( !mysql ){
        fprintf(stderr, "cannot mysql_real_connect \n");
        return EXIT_FAILURE;
  }


// query
    char FORMAT[] =
"INSERT INTO tb_image( id, type, name, image ) VALUES ( %d, %d, '%s', '%s' )";

    printf("sql: %s \n", FORMAT);

    int id = 0;

// query execution
    snprintf( (char *)sql_str , sql_size , (char *)FORMAT, id, type,  (char *)fname,  (char *)data );

     int ret = mysql_query( conn,  (char *)sql_str );

    if( ret != 0 ) {
        fprintf(stderr, "mysql_query: %s \n", mysql_error(conn) );
        mysql_close(conn);
        free(data);
        return EXIT_FAILURE;
    }

    printf("inserted : %s into tb_image, id: %llu \n", fname, mysql_insert_id(conn) );

// clean up
    mysql_close(conn);
    free(data);

  return EXIT_SUCCESS;
}


// inserted : mysql_logo.png into tb_image, id: 1 

