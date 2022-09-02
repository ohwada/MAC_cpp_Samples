/**
 * transaction.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://linuxcommand.net/c-lang-sqlite/2/#TRANSACTION

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


/**
 * main
 */
int main(void)
{
    const char* FILEPATH = "testdb6.db";

    sqlite3 *db;
    int rc,rc1,rc2,rc3; //result codes

    rc = sqlite3_open(FILEPATH, &db);

    if(rc != SQLITE_OK){
            printf("cannot open: %s \n", FILEPATH);
            return EXIT_FAILURE;
    }

    
//Start of TRANSACTION
    sqlite3_exec(db,"BEGIN TRANSACTION",0,0,0);

    rc1 = sqlite3_exec(db,"INSERT INTO testtable(id,name) VALUES (4,'ddd')",0,0,0);
    rc2 = sqlite3_exec(db,"INSERT INTO testtable(id,name) VALUES (5,'eee')",0,0,0);
    rc3 = sqlite3_exec(db,"INSERT INTO testtable(id,name) VALUES (6,'fff')",0,0,0);

    if((rc1 == SQLITE_OK) && 
       (rc2 == SQLITE_OK) &&
       (rc3 == SQLITE_OK)) {
// normal process
        sqlite3_exec(db,"COMMIT",0,0,0);
        printf("COMMIT \n");
    }else{
// error handling
        sqlite3_exec(db,"ROLLBACK",0,0,0);
        printf("ROLLBACK \n");
    }


    sqlite3_close(db);

        return EXIT_SUCCESS;
}

// ROLLBACK 
