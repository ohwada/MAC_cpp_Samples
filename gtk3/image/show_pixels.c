/**
 * show_pixels.c
 * 2022-06-01 K.OHWADA
 */

//show image. from pixel bitmap

#include <stdio.h> 
#include <gtk/gtk.h>
#include "pixels.h"


/**
 * main
 */
int main(int argc, char** argv)
{
const char* WIN_TITLE = "GTK3: ColorMatrix";

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    // 256 x 256
    int size = 2;
    int scale = 128;

    if (argc == 3) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        printf("Usage: %s [size] [scale]  \n", argv[0]);
    }

    printf("size: %d \n", size);
    printf("scale: %d \n", scale);

    // image size
    int width = size * scale;
    int height = size * scale;

    printf("w=%d, h=%d \n", width, height);

    // create Pixel
    guchar *data = 
        (guchar *)createColorMatrixPixel(size, scale, true);


// open window
	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), 
         WIN_TITLE );
    gtk_window_set_default_size(GTK_WINDOW(window), 
        WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);


// create pixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            data, 
            GDK_COLORSPACE_RGB, 
            true, 
            8, 
            width, 
            height, 
            (4*width), 
            NULL, 
            NULL);
	if (pixbuf == NULL)
	{
        printf("gdk_pixbuf_new_from_data Faild \n");
        return EXIT_FAILURE;
	}


// create image
    GtkWidget* image = gtk_image_new_from_pixbuf (pixbuf);
	if (pixbuf == NULL)
	{
        printf("gtk_image_new_from_pixbuf  Faild \n");
        return EXIT_FAILURE;
	}


// show Image
	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

	return EXIT_SUCCESS;
}

