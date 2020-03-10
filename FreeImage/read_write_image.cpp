/**
 * Freeimage Sample
 * 2020-01-01 K.OHWADA
 *  reference : https://qiita.com/ignis_fatuus/items/a4ca7c041691fb0f8c77
 */

#include <string> 
#include<iostream>
#include<FreeImage.h>
#include <gtk/gtk.h>

#include "freeimage_util.hpp"


/**
 * loadImageWithSwap
 */
char* loadImageWithSwap(std::string filename, int &width, int &height)
{

        // Reading file   
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
        FIBITMAP* image = FreeImage_Load(format, filename.c_str());
        if(!image) {
                std::cerr << "Load Failed: " << filename << std::endl;
                return NULL;
        }


        width = FreeImage_GetWidth(image);
        height = FreeImage_GetHeight(image);

        // Convert to 32-bit image
        FIBITMAP* image32 = FreeImage_ConvertTo32Bits(image);

        //copy to buffer
    int bufsize = 4 * width * height;
    char* buffer = new char[bufsize];
        memcpy(buffer, FreeImage_GetBits(image32), bufsize);


        //Release image data
        FreeImage_Unload(image);
        FreeImage_Unload(image32);

    // swap R and B
    return swapRB(width, height, buffer);

}

saveImageWithSwapWithSwap

/**
 * saveImageWithSwap
 */
bool saveImageWithSwap(std::string fileName, char *buffer, int width, int height)
{


    // swap R and B
    char* swapped = swapRB(width, height, buffer);



        FREE_IMAGE_FORMAT format = 
        FreeImage_GetFIFFromFilename(fileName.c_str());

        FIBITMAP *image = FreeImage_ConvertFromRawBits(
            (BYTE*)swapped, 
            width,
            height, 
            (4*width),  // pitch
            32, // bpp
            0xFF000000,  // red_mask
            0x00FF0000,  // green_mask
            0x0000FF00  // blue_mask
        );


        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);

        // save as PNG
       // bool ret = FreeImage_Save(FIF_PNG, image, fileName.c_str(), 0);
        bool ret = FreeImage_Save(
            format, 
            image, 
            fileName.c_str(), 
            DEFAULT);

    return ret;
}


/**
 * swapRB
 */
char* swapRB(int width, int height, char *src)
{

// bug fix for FreeImage
// https://sourceforge.net/p/freeimage/discussion/36110/thread/28c0cdfd/

    int bufsize = 4 * width * height;
    char* buffer = new char[bufsize];

	for ( int i=0; i<bufsize; i+=4 )
	{
        buffer[i+0] = src[i+2]; // R = B
        buffer[i+1] = src[i+1]; // G
        buffer[i+2] = src[i+0]; // B = R
        buffer[i+3] = src[i+3]; // A
	}

    return buffer;
}


/**
 * image_new
 */
GtkWidget* image_new(int width, int height, char *src)
{

// do Upside down
// https://stackoverflow.com/questions/56727077/bitmap-is-loaded-mirrored-and-inverted

    int bufsize = 4 * width * height;
    guchar* buffer = new guchar[bufsize];

    for(int y = 0;  y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            gint    col     = x;
            gint    row     = height - y - 1;
            gint    index   = (row * width + col) * 4;
            gint    index2  = (row * width + (width - col)) * 4;

            buffer[(bufsize - index2) + 0] = src[index + 0]; // R
            buffer[(bufsize - index2) + 1] = src[index + 1]; // G
            buffer[(bufsize - index2) + 2] = src[index + 2]; // B
            buffer[(bufsize - index2) + 3] = src[index + 3]; // A
        }
    }

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            buffer, 
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
 * createOutputFileName
 */
string getFileTitle(string input)
{

    string dir;
    string title;
    string in_ext;
    parseFileName(input, dir, title, in_ext);

    return title;
}



/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;


    if(argc < 2) {
        cout << "Usage: " << argv[0] <<  " <inputImageFilename> "  << endl;
        return EXIT_FAILURE;
    }

    // specify file name from the command line
    string input = argv[1];

    // print Version
    cout << "FreeImage : " << FreeImage_GetVersion() << endl;

    string file_title = getFileTitle(input);

    string win_title = "FreeImage: "  + file_title;

    string output = file_title + "_copy.png";

    // read Image
    int width;
    int height;
    char * file_image = loadImageWithSwap(input, width, height);
        if(!file_image) {
                cerr << "loadImageWithSwap Failed" << endl;
                return EXIT_FAILURE;
        }

    // print file info
    string str_width = to_string(width);
    string str_height = to_string(height);
    string str_size = " ( " + str_width  + " x " + str_height + " )";
    cout << "loadImageWithSwap: " << input << str_size << endl;

// open window
	gtk_init (&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), win_title.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

// show Image
    GtkWidget* image = image_new(width, height,  file_image);
	if (image == NULL)
	{
        cerr << "mage_new Faild" << endl;
        return EXIT_FAILURE;
	}

	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

    // save Image
    bool ret = saveImageWithSwap(output, file_image, width, height);
    if(!ret) {
                cerr << "SaveImage Failed: " << output << endl;
                return EXIT_FAILURE;
    }

    cout << "saved Image: " << output << endl;

	return EXIT_SUCCESS;
}

