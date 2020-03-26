/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <gtk/gtk.h>

#include "bmp.h"

#include"parse_filename.hpp"

using namespace std;


/**
 *  bmp_image_rgb_to_rgba_data
 */
char* bmp_image_rgb_to_rgba_data( image_t *img)
{

     int width = img->width;
     int height = img->height;

    int bufsize = 4*width*height;
    char* buf = new char[bufsize]; 

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {

            pixcel_t pix = img->map[y][x];

            color_t c = pix.c;

            char r = c.r;
            char g = c.g;
            char b = c.b;
            char a = c.a;

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
 * loadImage
 */
char* loadImage(string input, int &width, int &height)
{

// read image
        image_t *img = read_bmp_file(input.c_str());
    if (!img) {
        cerr << "read_bmp_file faild:" << input << endl;
        return NULL;
    }

    width = img->width;
    height = img->height;
    int type = img->color_type;

    char *data;

if(type == COLOR_TYPE_INDEX){
        cout << "color type: index " << endl;
        image_t *img2 = image_index_to_rgb(img);
        data = bmp_image_rgb_to_rgba_data(img2);
}else if(type == COLOR_TYPE_RGB){
        cout << "color type: RGB " << endl;
        data = bmp_image_rgb_to_rgba_data(img);
}else if(type == COLOR_TYPE_RGBA){
            cout << "color type: RGBA " << endl;
            data = bmp_image_rgb_to_rgba_data(img);
}else if(type == COLOR_TYPE_GRAY){
            cout << "Error: color type: gray"  << endl;
} else {
            cout << "Error: color type: unkown"  << endl;
 }

    return data;

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

