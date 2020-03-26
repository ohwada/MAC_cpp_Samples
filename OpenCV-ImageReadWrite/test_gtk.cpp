/**
 * OpenCV Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <gtk/gtk.h>

#include "parse_filename.hpp"

using namespace std;
using namespace cv;


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

    // load as BGR color
    Mat m = imread(input, IMREAD_COLOR);

    if(m.empty())
    {
        cerr << "loadImage Faild: " << input << endl;
        return NULL;
    }

    width = m.cols;
    height = m.rows;
    unsigned char *data = m.data;

    int bufsize = 4*width*height;
    char *buf = new char[bufsize];
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int buf_index = 4*width*y + 4*x;
            int src_index = 3*width*y + 3*x;
            buf[buf_index+0] = data[src_index+2]; // R
            buf[buf_index+1] = data[src_index+1];  // G
            buf[buf_index+2] = data[src_index+0]; // B
            buf[buf_index+3] = (char)255; // A
        }
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

    cout << "OpenCV with GTK: " << endl;


    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    string input = argv[1];


    string fname = getFileNameWithExt(input);
    string win_title = "gtk: "  + fname;


//loadImage
    int width;
    int height;
    char* data = loadImage(input, width, height);
	if (!data)
	{
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

// show Image
    GtkWidget* image = image_new(
        data, width, height);
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

