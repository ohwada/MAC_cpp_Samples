/**
 * version.c
 * 2020-07-01 K.OHWADA
 */

// gcc version.c -o bin/version `pkg-config --cflags --libs sqlite3`


#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


/**
 * main
 */
int main(void)
{

    printf( "SQLITE_VERSION: %s \n", SQLITE_VERSION );

    printf( "sqlite3_libversion: %s \n", sqlite3_libversion() );

    return EXIT_SUCCESS;
}


// gcc version.c -lsqlite3
// SQLITE_VERSION: 3.28.0 
// sqlite3_libversion: 3.28.0 

// gcc version.c `pkg-config --cflags --libs sqlite3`
// SQLITE_VERSION: 3.39.2 
// sqlite3_libversion: 3.39.2 


