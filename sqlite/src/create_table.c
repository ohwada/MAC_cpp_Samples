/**
 * create_table.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://linuxcommand.net/c-lang-sqlite/2/#CREATE_TABLE

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


/**
 * callback
 */
int callback(void *NotUsed, int result_num, char **result_value, char **ColName){
    int i;
    int *notused;

    notused = NotUsed;
    
    for(i = 0; i < result_num; i++){
        printf("%s = %s\n", ColName[i], result_value[i] ? result_value[i] : "NULL");
    }
    printf("\n");
    return 0;
}


/**
 * main
 */
int main(void)
{

    const char* FILEPATH = "test5.db";

    sqlite3 *db;
    int rc; //result codes

    rc = sqlite3_open(FILEPATH, &db);

    if(rc != SQLITE_OK){
            printf("cannot open: %s \n", FILEPATH);
            return EXIT_FAILURE;
    }

  
// execute CREATE TABLE statement
    rc = sqlite3_exec(db, "CREATE TABLE testtable2 (id2 integer primary key, name2 text)", NULL, NULL, NULL);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

// display the table of the entire database
    rc = sqlite3_exec(db, "SELECT * from sqlite_master where type='table'", callback, NULL, NULL);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));
        sqlite3_close(db);
            return EXIT_FAILURE;
    }

    sqlite3_close(db);

    return EXIT_SUCCESS;
}


// tbl_name = testtable2
// rootpage = 3
// sql = CREATE TABLE testtable2 (id2 integer primary key, name2 text)


