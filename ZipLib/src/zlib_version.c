// zlib_version.c

// gcc zlib_version.c `pkg-config --cflags --libs ziplib`

#include <stdio.h>
#include "extlibs/zlib/zlib.h"

int main()
{
    printf("ZLIB_VERSION: %s \n",  ZLIB_VERSION);

    return 0;
}