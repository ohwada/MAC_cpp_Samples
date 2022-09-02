/**
 * insert.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://linuxcommand.net/c-lang-sqlite/2/#SELECT

#include <stdio.h>
#include <stdbool.h>
#include "sqlite3.h"

// prototype
bool select_testtable(sqlite3 *db );


/**
 *  select_testtable
 */
bool select_testtable(sqlite3 *db )
{
    sqlite3_stmt *stmt;
    int rc; //result codes

// generate prepared statement
    rc = sqlite3_prepare_v2(db,"SELECT id, name FROM testtable", -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }
    
// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        printf("%d %s",
                sqlite3_column_int(stmt, 0),
                sqlite3_column_text(stmt, 1));
        printf("\n");
        rc = sqlite3_step(stmt);
    }

// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}
