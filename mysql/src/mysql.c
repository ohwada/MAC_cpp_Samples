/**
 * mysql.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/Ki4mTaria/items/778ff9186bb4958bb667

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


/**
 * main
 */
int main(void)
{

  MYSQL *conn     = NULL;
  MYSQL_RES *resp = NULL;
  MYSQL_ROW row;
  char sql_str[255];
  char *sql_serv  = "localhost";
  char *user      = "root";
  char *passwd    = "";
  char *db_name   = "db_test";

  memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

  
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
  snprintf( &sql_str[0] , sizeof(sql_str)-1 , "select * from tb_test" );

 int ret = mysql_query( conn , &sql_str[0] );

  if( ret != 0 ) {
    fprintf(stderr, "cannot mysql_quer: %d \n", ret);
    mysql_close(conn);
    return EXIT_FAILURE;
  }

// response
  resp = mysql_use_result(conn);

  while((row = mysql_fetch_row(resp)) != NULL ){
    printf( "%d : %s\n" , atoi(row[0]) , row[1] );
  } // while


// clean up
  mysql_free_result(resp);
  mysql_close(conn);

  return EXIT_SUCCESS;
}


// 1 : aaa
// 2 : bbb
// 3 : ccc

