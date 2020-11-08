/**
 * sqlite sample
 * 2020-07-01 K.OHWADA
 */

// select records from database 

// reference : http://www.kuma-de.com/blog/2012-02-08/3192


// Preparation
// Prepare sample record in database
// % sqlite3 hello.db
// sqlite> create table hello (id integer primary key, message text);
// sqlite> insert into hello (message) values ('Sierra');
// sqlite> insert into hello (message) values ('Mojave');
// sqlite> insert into hello (message) values ('Catalina');
// sqlite> select * from hello;
// sqlite> .exit;


// gcc select_record.c `pkg-config --cflags --libs sqlite3`


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
 

/**
 * main
 */
int main(void)
{

    const size_t SQL_SIZE = 100;
    char sql[SQL_SIZE];

    const char *db_name = "hello.db";
    const char *tbl_name = "hello";


    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    // record
    int id;
    char *message;


    result = sqlite3_open_v2( db_name , &db, SQLITE_OPEN_READONLY, NULL);

    if(result == SQLITE_OK){
        printf("opened: %s \n", db_name);
    } else {
        printf("can not open: %s \n", db_name);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
 


    snprintf(sql,  SQL_SIZE, "select * from %s;", (char *)tbl_name);
    printf("sql: %s \n", sql);

    result = sqlite3_prepare_v2(db, (char *)sql,  strlen(sql), &stmt, NULL);
 
    if(result != SQLITE_OK){
        printf("sql error: %s \n", sql);
        return EXIT_FAILURE;
    }
 
    result = sqlite3_step(stmt);
    while(result == SQLITE_ROW){
        id = sqlite3_column_int(stmt, 0);
        message = (char *)sqlite3_column_text(stmt, 1);
        printf("id = %d, message = %s\n", id, message);
        result = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return EXIT_SUCCESS;
}


// opened: hello.db
// sql: select * from hello;  
// id = 1, message = Sierra
// id = 2, message = Mojave
// id = 3, message = Catalina

