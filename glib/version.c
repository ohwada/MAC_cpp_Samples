/**
 * glib sample
 * 2020-07-01 K.OHWADA
 */

// display glib version

// gcc version.c `pkg-config --cflags --libs glib-2.0`

#include<stdio.h>
#include<stdlib.h>
#include <glib.h>


/**
 * main
 */
int main(void)
{

    printf("GLib version: %d.%d.%d \n", 
    GLIB_MAJOR_VERSION,
    GLIB_MINOR_VERSION,
    GLIB_MICRO_VERSION);

    return EXIT_SUCCESS;
}


// GLib version: 2.66.2 

