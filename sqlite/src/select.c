/**
 * select.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://linuxcommand.net/c-lang-sqlite/2/#SELECT

#include <stdio.h>
#include <stdlib.h>
#include "select.h"


/**
 * main
 */
int main(void)
{
    const char* FILEPATH = "test1.db";
 
    sqlite3 *db;
   int rc; //result codes

    rc = sqlite3_open(FILEPATH, &db);
    if(rc != SQLITE_OK){
        printf("cannot open: %s \n", FILEPATH);
        return EXIT_FAILURE;
    }

    select_testtable(db);

    sqlite3_close(db);

    return EXIT_SUCCESS;
}

// 1 aaa
// 2 bbb
// 3 ccc

