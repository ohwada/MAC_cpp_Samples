/**
 * cairo sample
 * 2020-03-01 K.OHWADA
 */

// draw arc to png file
// reference : https://www.cairographics.org/samples/

#include <cairo.h>
#include <stdio.h>
#include <math.h>


/**
 * printCairoVersion
 */
void printCairoVersion()
{
    printf("cairo version: %d.%d.%d \n", 
    CAIRO_VERSION_MAJOR, 
    CAIRO_VERSION_MINOR, 
    CAIRO_VERSION_MICRO
    );
}

/**
 * main
 */
int main(int argc, char **argv)
{
    const int WIDTH  = 500;
    const int HEIGHT = 500;
   const char* FILENAME = "cairo.png";

    double xc = WIDTH/2;
    double yc = HEIGHT/2;
    double ARC_RADIUS = 200.0;
    double ARC_ANGLE1 = 45.0  * (M_PI/180.0);  /* angles are specified */
    double ARC_ANGLE2 = 180.0 * (M_PI/180.0);  /* in radians           */

    printCairoVersion();

    cairo_surface_t *surface;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
					  WIDTH, HEIGHT);

    cairo_t *cr;
    cr = cairo_create (surface);

    cairo_set_line_width (cr, 10.0);

    cairo_arc (cr, xc, yc, ARC_RADIUS, ARC_ANGLE1, ARC_ANGLE2);

    cairo_stroke (cr);

/* draw helping lines */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6); // red
    cairo_set_line_width (cr, 6.0);

    cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
    cairo_fill (cr);

    cairo_arc (cr, xc, yc, ARC_RADIUS, ARC_ANGLE1, ARC_ANGLE1);
    cairo_line_to (cr, xc, yc);

    cairo_arc (cr, xc, yc, ARC_RADIUS, ARC_ANGLE2, ARC_ANGLE2);
    cairo_line_to (cr, xc, yc);
    cairo_stroke (cr);

    cairo_surface_write_to_png (surface, FILENAME);
    cairo_destroy(cr);
    printf("saved: %s \n", FILENAME);

    return 0;
}

