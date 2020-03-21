/**
 * RawLoader Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "RawLoader.h"

#include"parse_raw_filename.hpp"

using namespace std;

//　global
RAWImage rawImage;



/**
 * loadImage
 */
char* loadImage(string input, int &width, int &height)
{

// parse_file_param
	bool alphaFlag;
	bool ret1 = parse_raw_file_param(input, width, height, alphaFlag);
	if(!ret1){
        cerr << "parse_file_param Faild: " << input << endl;
		return NULL;
	}


// read image
	bool ret2 = rawImage.ReadRAW(input, width, height, alphaFlag);
    if(!ret2){
        return NULL;
    }

    char* imageData = rawImage.getImageData();

    int bufsize = 4*width*height;
    char* buf = new char[bufsize]; 


    int src_index;
    char a;

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            int buf_index = 4*width*y + 4*x;

            if(alphaFlag){
                    src_index = buf_index;
            } else{
                    src_index = 3*width*y + 3*x;
            }

	         buf[buf_index+0] = imageData[src_index+0];
	         buf[buf_index+1] = imageData[src_index+1];
	         buf[buf_index+2] = imageData[src_index+2];

            if(alphaFlag){
	            a = imageData[src_index+3];
            } else{
                a = (char)255;
            }
	         buf[buf_index+3] = a;

        } // x
    } // y

	// delete unnecessary memory
	delete [] imageData;
	imageData = NULL;

    return buf;
}



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "RawLoader : gtk" << endl;


    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

   string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "gtk RawLoader: " + fname;





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

