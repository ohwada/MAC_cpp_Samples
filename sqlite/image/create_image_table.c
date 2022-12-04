/**
 * create_image_table.c
 * 2022-06-01 K.OHWADA
 */

//  create_image_table in image.db

// reference : https://linuxcommand.net/c-lang-sqlite/2/#CREATE_TABLE

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


/**
 * callback
 */
int callback(void *NotUsed, int result_num, char **result_value, char **ColName)
{
    int i;
    int *notused;

    notused = NotUsed;
    
    for(i = 0; i < result_num; i++)
    {
        char* name = ColName[i];
        char* value = result_value[i] ? result_value[i] : "NULL";
        printf("%s : %s\n", name, value);
    } // for
    printf("\n");
    return 0;
}


/**
 * main
 */
int main(void)
{

    const char* db_name = "image.db";

    sqlite3 *db;
    int rc; //result codes

    rc = sqlite3_open(db_name, &db);

    if(rc != SQLITE_OK){
            fprintf(stderr, "sqlite3_open: %s: %s \n", db_name, sqlite3_errstr(rc));
            return EXIT_FAILURE;
    }

  
// execute CREATE TABLE statement

    char* query1 = "CREATE TABLE image_table(id INTEGER PRIMARY KEY, name TEXT, data BLOB)";

    rc = sqlite3_exec(db, query1, NULL, NULL, NULL);
    if(rc != SQLITE_OK){
        fprintf(stderr, "ERROR(%d) %s\n",rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

// display the table of the entire database

    char* query2 = "SELECT * FROM sqlite_master WHERE type='table' ";

    rc = sqlite3_exec(db,  query2, callback, NULL, NULL);
    if(rc != SQLITE_OK){
        fprintf(stderr, "ERROR(%d) %s\n",rc, sqlite3_errmsg(db) );
        sqlite3_close(db);
            return EXIT_FAILURE;
    }

// clean up
    sqlite3_close(db);

    return EXIT_SUCCESS;
}


// type : table
// name : image_table
// tbl_name : image_table
// rootpage : 2
// sql : CREATE TABLE image_table(id INTEGER PRIMARY KEY, name TEXT, data BLOB)



