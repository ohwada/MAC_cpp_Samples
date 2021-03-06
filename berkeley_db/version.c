/**
 * berkeley_db sample
 * 2021-02-01 K.OHWADA
 */

// display version

// gcc version.c `pkg-config --cflags --libs libdb` 


#include <stdio.h>
#include <stdlib.h>
#include "db.h"

int main(void)
{

    printf( "libdb full Version: %s \n", DB_VERSION_FULL_STRING  );

    int major;
    int minor;
    int patch;

    printf( "libdb Version: %s \n",   db_version( &major, &minor, &patch )  );
    printf( "major: %d \n",  major );
    printf( "minor: %d \n",  minor );
    printf( "patch: %d \n",  patch );

    return EXIT_SUCCESS;
}


// libdb full Version: Berkeley DB Release 18.1, library version 18.1.32: (February 19, 2019) 
// libdb Version: Berkeley DB 18.1.32: (February 19, 2019) 
// major: 18 
// minor: 1 
//patch: 32 

