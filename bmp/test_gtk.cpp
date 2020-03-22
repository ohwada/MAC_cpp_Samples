/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include"bitmap.h"

#include"parse_filename.hpp"

using namespace std;



/**
 * loadImage
 * @return  R G B without alpha
 */
char* loadImage(string input, int &width, int &height)
{

// read image
	Image *img  = Read_Bmp( (char *)input.c_str() );
    if(!img){
        return NULL;
    }

    width = img->width;
    height = img->height;

    int bufsize = 3*width*height;
    char* buf = new char[bufsize]; 

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            int src_index = width*y + x;
	        Rgb pix = img->data[src_index];
            char r = pix.r;
            char g = pix.g;
            char b = pix.b;

            int buf_index = 3*width*y + 3*x;
            buf[buf_index+0] = r;
            buf[buf_index+1] = g;
            buf[buf_index+2] = b;

        } // x
    } // y

	Free_Image(img);

    return buf;
}



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "bmp : gtk" << endl;


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "bmp: " + fname;


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
            FALSE, 
            8, 
            width, 
            height, 
            (3*width), 
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

