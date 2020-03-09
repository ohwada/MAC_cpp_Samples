/**
 * GTK Sample
 * 2020-01-01 K.OHWADA
 *  reference :  https://fut-nis.hatenadiary.jp/entry/20121113/1352810731
 */


#include <stdlib.h>
#include <string>
#include<iostream>

#include <gtk/gtk.h>

#include "parse_filename.hpp"

using namespace std;



/*
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

	GError *error = NULL;

    cout << "GTK: image file" << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
		return EXIT_FAILURE;
    }

    string input = argv[1];

    string fname = getFileNameWithExt(input);
    string win_title = "GTK: " + fname;


	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), win_title.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

// read image
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (input.c_str(), &error);
	if (pixbuf == NULL)
	{
		g_print ("Error:\t%s\n", error->message);
		g_error_free (error);
		error = NULL;
		return EXIT_FAILURE;
	}

    cout << "load image: " << input << endl;

    // file info
	g_print ("Number of channels:\t%d\n", gdk_pixbuf_get_n_channels (pixbuf));
	g_print ("Has Alpha channel:\t%d\n", gdk_pixbuf_get_has_alpha (pixbuf));
	g_print ("Bits per sample:\t%d\n", gdk_pixbuf_get_bits_per_sample (pixbuf));
	g_print ("Width:\t%d\n", gdk_pixbuf_get_width (pixbuf));
	g_print ("Height:\t%d\n", gdk_pixbuf_get_height (pixbuf));
	g_print ("Bytes of row:\t%d\n", gdk_pixbuf_get_rowstride (pixbuf));

	GtkWidget *image = gtk_image_new_from_pixbuf (pixbuf);
	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

	return EXIT_SUCCESS;
}
