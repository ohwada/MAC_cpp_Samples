/**
 * gtk.cpp
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>
#include <png++/png.hpp>
#include <gtk/gtk.h>

#include "png_util.h"
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

   string input("images/uparrow.png");


    if(argc == 2) {
        input = argv[1];
    } else {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
    }

 
    cout<< input << endl;

    string fname = getFileNameWithExt(input);

    string win_title = "png++: " + fname;


// loadImage
    int width;
    int height;
    char* data = loadImage2(input, width, height);

    if(!data){
        cerr << "loadImage Faild: " << input  << endl;
        return 1;
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
    GtkWidget* gtk_image = image_new(data, width, height);

	if (!gtk_image)
	{
            cerr << "mage_new Faild" << endl;
            return 1;
	}


	gtk_container_add (GTK_CONTAINER (window), gtk_image);
	gtk_widget_show_all (window);	
	gtk_main ();



	return 0;
}

