/**
 * libtiff Sample
 * 2020-02-01 K.OHWADA
 */

// reference : http://maptools-org.996276.n3.nabble.com/reading-rgb-values-from-16-bits-tif-images-td3390.html

#include <string> 
#include<iostream>

#include <tiffio.h>

#include <gtk/gtk.h>

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
 * reverse UpsideDown
 */
char* reverseUpsideDown(char *src, int width, int height)
{

    int bufsize = 4 * width * height;
    char* buff = new char[bufsize];

    for(int y = 0;  y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            int col     = x;
            int row     = height - y - 1;
            int src_index   = (row * width + col) * 4;
            int index_rev  = (row * width + (width - col)) * 4;
            int buf_index = bufsize - index_rev;
            buff[buf_index + 0] = src[src_index + 0]; // R
            buff[buf_index + 1] = src[src_index + 1]; // G
            buff[buf_index + 2] = src[src_index + 2]; // B
            buff[buf_index + 3] = src[src_index + 3]; // A
        }
    }

    return buff;
}


/**
 * loadImage
 */
char* loadImage(string input, int &width, int &height)
{

    char *buf;

  // Open the TIFF image
    TIFF* tif = TIFFOpen(input.c_str(), "r");

    if(!tif){
        cout << "TIFFOpen Faild: " << input << endl;
        return NULL;
    }

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

	size_t npixels = width * height;
	uint32* raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));

    if(!raster){
        cout << "TIFFmalloc Faild: "  << endl;
        return NULL;
    }

    TIFFReadRGBAImage(tif, width, height, raster, 0);

        int bufsize = 4*width*height;
        buf = new char[bufsize];

        for(int y=0; y<height; y++){
            for(int x=0; x<height; x++){

                    int src_index = width*y + x;
                    int buf_index = 4*width*y + 4*x;

                    uint32 pixel = raster[src_index];

                    char r = TIFFGetR(pixel);
                    char g = TIFFGetG(pixel);
                    char b = TIFFGetB(pixel);
                    char a = TIFFGetA(pixel);

                    buf[buf_index +0] = r;
                    buf[buf_index +1] = g;
                    buf[buf_index +2] = b;
                    buf[buf_index +3] = a;

            } // x
        } // y

    // reverse UpsideDown
    // because TIFF image origin is letf bottom
    return reverseUpsideDown(buf, width, height);

}


/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "libtiff : gtk " << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title = "libtiff: " + fname;


// loadImage
    int width;
    int height;
    char* file_image = loadImage(input, width, height);

    if(!file_image){
        cerr << "loadImage Faild: " << input  << endl;
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
    GtkWidget* gtk_image = image_new(file_image, width, height);

	if (!gtk_image)
	{
            cerr << "mage_new Faild" << endl;
            return EXIT_FAILURE;
	}


	gtk_container_add (GTK_CONTAINER (window), gtk_image);
	gtk_widget_show_all (window);	
	gtk_main ();



	return EXIT_SUCCESS;
}

