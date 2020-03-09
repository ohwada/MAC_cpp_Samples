/**
 * GTK Sample
 * 2020-01-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "pixels.h"


using namespace std;



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "GTK: ColorMatrix" << endl;

    // 256 x 256
    int size = 2;
    int scale = 128;

    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] "  << endl;
    }


    // image size
    int width = size * scale;
    int height = size * scale;
    string image_size = to_string(width) + " x " + to_string(height);
    string win_title = "ColorMatrix: " + image_size;

        cout <<  win_title  << endl;


    // create Pixel
    const guchar *data = 
        (const guchar *)createColorMatrixPixel(size, scale);


// open window
	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), 
        win_title.c_str());
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
        cerr << "gdk_pixbuf_new_from_data Faild" << endl;
        return EXIT_FAILURE;
	}


// create image
    GtkWidget* image = gtk_image_new_from_pixbuf (pixbuf);
	if (pixbuf == NULL)
	{
        cerr << "gtk_image_new_from_pixbuf  Faild" << endl;
        return EXIT_FAILURE;
	}


// show Image
	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

	return EXIT_SUCCESS;
}

