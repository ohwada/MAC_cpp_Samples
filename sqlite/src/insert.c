/**
 * insert.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://linuxcommand.net/c-lang-sqlite/2/#INSERT

#include <stdio.h>
#include <stdlib.h>
#include "select.h"


/**
 * main
 */
int main(void)
{
    const char* FILEPATH = "test2.db";

   sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc; //result codes

    rc = sqlite3_open(FILEPATH, &db);

    if(rc != SQLITE_OK){
        printf("cannot open: %s \n", FILEPATH);
        return EXIT_FAILURE;
    }

// prepare the INSERT statement
    rc = sqlite3_prepare_v2(db,"INSERT INTO testtable(id,name) VALUES "
                                "(4,'ddd')",
                                -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
    
//execute INSERT statement
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    select_testtable(db);

    sqlite3_close(db);

    return EXIT_SUCCESS;
}

// 1 aaa
// 2 bbb
// 3 ccc
// 4 ddd
