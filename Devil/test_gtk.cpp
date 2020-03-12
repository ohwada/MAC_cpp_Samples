/**
 * Devil Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "devil_util.hpp" 

#include "parse_filename.hpp"


using namespace std;


/**
 * image_new
 */
GtkWidget* image_new(char *data, int width, int height)
{

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            (guchar* )data, 
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
		return NULL;
	}

    return gtk_image_new_from_pixbuf (pixbuf);

}

/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "Devil : gtk " << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "GTK Devil: " + fname;

	// Initialize DevIL.
	ilInit();

 // loadImage
    int width;
    int height;
    char* file_image = devil_loadImage(input, width, height);
	if (!file_image)
	{
        cerr << "loadImage Faild" << endl;
        return EXIT_FAILURE;
	}

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;


// open window
	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), win_title.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

// show Image
    GtkWidget* image = image_new(file_image, width, height);
	if (!image)
	{
        cerr << "mage_new Faild" << endl;
        return EXIT_FAILURE;
	}


	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

    devil_printError();

	return EXIT_SUCCESS;
}

