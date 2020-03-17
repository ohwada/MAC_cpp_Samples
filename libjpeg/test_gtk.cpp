/**
 * libjpeg Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "jpeg.h"

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
 * loadImage
 */
char* loadImage(string input, int &width, int &height)
{

    char *buf;
    try
    {
        using namespace marengo::jpeg;

        // Constructor expects a filename to load:
        Image imgOriginal( input );

        // Copy construct a second version so we can
        // shrink non-destructively. Not really necessary
        // here, but just to show it can be done :)
        Image img = imgOriginal;

        height = img.getHeight();
        width  = img.getWidth();

        int bufsize = 4*width*height;
        buf = new char[bufsize];

        for (int y = 0; y < height; ++y )
        {
            for (int x = 0; x < width; ++x )
            {

                int index = 4*width*y + 4*x;

            // The vector's
            // size will be 1 for monochrome or
            // 3 for RGB.
            // Elements will be in order R, G, B.
                auto vec = img.getPixel( x, y );
                if ( vec.size() == 3 )
                {
                        char r =vec[0];
                        char  g =vec[1];
                        char b =vec[2];
                        buf[index+0] = r;
                        buf[index+1] = g;
                        buf[index+2] = b;
                        buf[index+3] = (char)255;
                } //if

            } // x
        } // y

    }
    catch( const std::exception& e )
    {
        cerr <<  "loadImage Faild: " << e.what() << endl;
        return NULL;
    }

    return buf;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

    cout << "libjpeg : gtk " << endl;

    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    // win title
    string fname = getFileNameWithExt(input);
    string win_title = "libjpeg: " + fname;


// loadImage
    int width;
    int height;
    char* data = loadImage(input, width, height);
    if(!data)
	{
        cerr << "loadImage Faild: " << input <<  endl;
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
    GtkWidget* image = image_new(data, width, height);
	if (!image)
	{
        cerr << "mage_new Faild" << endl;
        return EXIT_FAILURE;
	}


	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();


	return EXIT_SUCCESS;
}

