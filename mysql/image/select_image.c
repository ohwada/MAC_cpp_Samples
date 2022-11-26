/**
 * select_image.c
 * 2022-06-01 K.OHWADA
 */

// select image data from mysql table
// and save image into file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>
#include "file_util.h"
#include "blob_type.h"
#include "base64.h"
#include "bin_hex.h"


/**
 * main
 */
int main(int argc, char* argv[])
{
    const size_t BUFSIZE = 255;
    char sql_str[BUFSIZE];
    char fpath[ BUFSIZE];
    char error[ BUFSIZE];

    const int ZERO = 0x00;

  MYSQL *conn     = NULL;
  char *sql_serv  = "localhost";
  char *user      = "root";
  char *passwd    = "";
  char *db_name   = "db_test";

  MYSQL_RES *resp = NULL;
  MYSQL_ROW row;

    int ret = 0;

// clear query string
  memset( &sql_str[0] , ZERO, sizeof(sql_str) );

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

// query execution
    char* query1 = "SELECT id, type, name FROM tb_image";

 ret = mysql_query( conn , query1 );

  if( ret != 0 ) {
    fprintf(stderr, "cannot mysql_query: %s \n", mysql_error(conn));
    mysql_close(conn);
    return EXIT_FAILURE;
  }

// response
  resp = mysql_use_result(conn);

  while((row = mysql_fetch_row(resp)) != NULL ){
        int id = atoi(row[0]);
        int type = atoi(row[1]);
        char* name = row[2];
        char* str_type = type_to_string(type);
        printf( "%d : %s, %s \n" , id ,str_type , name );
  } // while

    printf("select id(0: quit) >");

    int select;
    scanf("%d", &select);

    if(select == 0){
        printf("bye \n");
        mysql_free_result(resp);
        mysql_close(conn);
        return EXIT_SUCCESS;
 }

// query
    char* FORMAT =
"SELECT id, type, name, image FROM tb_image where id = %d";

snprintf(sql_str, BUFSIZE, FORMAT, select);

printf("sql: %s \n", sql_str);

 ret = mysql_query( conn ,  sql_str );

  if( ret != 0 ) {
    fprintf(stderr, "cannot mysql_query: %s \n", mysql_error(conn));
    mysql_close(conn);
    return EXIT_FAILURE;
  }

// response
    resp = mysql_use_result(conn);

    row = mysql_fetch_row(resp);
    if(!row)  {
        fprintf(stderr, "mysql_fetch_row failed: %s \n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    int id = atoi(row[0]);
    int type = atoi(row[1]);
    char* name = (char *)row[2];
    char* blob = (char *)row[3];
    size_t blob_len = strlen(blob);
    char* str_type = type_to_string(type);
    printf("%d: %s, %s \n", id, str_type, name );

    printf("blob len:%lu \n", blob_len);

    char* dir = "out";

    make_path(dir, name, (char *)fpath);

    printf("fpath: %s \n", fpath);

    size_t img_size = 0;
    char* img_data = NULL;
    bool is_img_data = false;

    if(type == TYPE_BASE64) {
            img_data = base64Decode( (char *)blob, &img_size,  BASE64_TYPE_STANDARD);
            is_img_data = true;
    } else if (type == TYPE_HEX) {
        size_t bin_size = blob_len/2;
        char bin_data[bin_size];
        hex2bin( (char *)blob, (char *)bin_data, bin_size);
        img_data =  (char *)bin_data;
        img_size = bin_size;
    }

    printf("img size: %zu \n", img_size);

    bool ret2 = file_binary_write( (char *)fpath,  img_data, img_size, (char *)error );
    if(!ret2){
        fprintf(stderr, "file_binary_write: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("save to: %s \n", fpath);

// clean up
    mysql_free_result(resp);
    mysql_close(conn);
    if( is_img_data){
        free(img_data);
    }

  return EXIT_SUCCESS;
}


// save to: out/mysql_logo.png 
