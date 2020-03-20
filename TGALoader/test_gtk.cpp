/**
 * TGALoader Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "TGALoader.hpp"

#include"parse_filename.hpp"

using namespace std;

// global
TGAImage tgaImage;


/**
 * loadImage
 */
char* loadImage(string input, int &width, int &height)
{


    bool ret = tgaImage.ReadTGA(input);
	if ( !ret ) {
		return NULL;
    }

// read image
	char* img = tgaImage.getImageData();
    width = tgaImage.getWidth();
    height = tgaImage.getHeight();

    return img;

}



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "TGALoader : gtk" << endl;


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "gtk TGALoader :  " + fname;


// load image
    int width;
    int height;
    char* data = loadImage(input, width, height);
    if(!data){
        cerr << "load Image Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    // file info
    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;


// open window
	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), win_title.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);



// create pixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            (const guchar *)data, 
            GDK_COLORSPACE_RGB, 
            TRUE, 
            8, 
            width, 
            height, 
            (4*width), 
            NULL, 
            NULL);

	if (!pixbuf )
	{
        cerr << "gdk_pixbuf_new_from_data Faild" << endl;
        return EXIT_FAILURE;
	}


// create image
    GtkWidget* gtk_image = gtk_image_new_from_pixbuf (pixbuf);
	if (!pixbuf)
	{
        cerr << "gtk_image_new_from_pixbuf Faild" << endl;
        return EXIT_FAILURE;
	}


// show Image
	gtk_container_add (GTK_CONTAINER (window), gtk_image);
	gtk_widget_show_all (window);	
	gtk_main ();

    return EXIT_SUCCESS;
}

