/**
 * stb Sample
 * 2020-02-01 K.OHWADA
 */

// support format : png, jpg, bmp, tga, gif
// NOT support : tif

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include"parse_filename.hpp"

using namespace std;



/**
 * loadImage
 */
uint8_t* loadImage(string input, int &width, int &height)
{

     int channels;

// read image
    uint8_t* pixels = (uint8_t*)stbi_load(input.c_str(), &width, &height, &channels, 0);

    if(!pixels){
        return NULL;
    }

    cout << "channels = " << channels << endl;

    int bufsize = 4*width*height;
    uint8_t* buf = new uint8_t[bufsize]; 

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            int src_index = channels*width*y + channels*x;

	        uint8_t r = pixels[src_index+0];
	        uint8_t g = pixels[src_index+1];
	        uint8_t b = pixels[src_index+2];
	        uint8_t a = (uint8_t)255;

            if(channels == 4){
	            a = pixels[src_index+3];
            }

            int buf_index = 4*width*y + 4*x;
            buf[buf_index+0] = r;
            buf[buf_index+1] = g;
            buf[buf_index+2] = b;
            buf[buf_index+3] = a;

        } // x
    } // y

    return buf;
}



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "stb : gtk" << endl;


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "stb: " + fname;


// load image
    int width;
   int height;
    uint8_t* data = loadImage(input, width, height);
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
            true, 
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

