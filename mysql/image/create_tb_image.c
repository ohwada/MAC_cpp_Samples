/**
 * create_tb_image.c
 * 2022-06-01 K.OHWADA
 */


// create table for inserting image data


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


/**
 * main
 */
int main(void)
{
    const size_t BUFSIZE = 255;
    char sql_str[ BUFSIZE];

    const int ZERO = 0x00;

  MYSQL *conn     = NULL;
  char *sql_serv  = "localhost";
  char *user      = "root";
  char *passwd    = "";
  char *db_name   = "db_test";

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


// clearquery string
  memset( &sql_str[0] , ZERO, sizeof(sql_str) );

// query
 // longblob: max 4GB
char QUERY[] =
"CREATE TABLE tb_image \
(id INT AUTO_INCREMENT, \
type TINYINT, \
name VARCHAR(40), \
image MEDIUMBLOB NOT NULL, \
PRIMARY KEY (id) )";

printf("%s \n", QUERY);


 int ret = mysql_query( conn ,  (char *)QUERY );
  if( ret != 0 ) {
    fprintf(stderr, "mysql_query: %s \n", mysql_error(conn) );
    mysql_close(conn);
    return EXIT_FAILURE;
  }

printf("created tb_image \n");

// clean up
  mysql_close(conn);

  return EXIT_SUCCESS;
}


// CREATE TABLE tb_image (id INT AUTO_INCREMENT, name VARCHAR(40), image MEDIUMBLOB NOT NULL, PRIMARY KEY (id) ) 
// created tb_image

