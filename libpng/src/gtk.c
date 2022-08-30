/**
 * gtk.c
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <gtk/gtk.h>
#include "png_util.h"
#include "c_parse_filename.h"


/**
 *  gtk_show
 */
bool gtk_show(GtkWidget *window, 
    unsigned char *data,
    int width,
    int height,
    int ch)
{

// show Image
  gboolean has_alpha = (ch==4)? true: false;
  int rowstride = ch*width;
 
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
            (guchar* )data, 
            GDK_COLORSPACE_RGB, 
            has_alpha, 
            8, 
            width, 
            height, 
            rowstride, 
            NULL, 
            NULL);

	if (pixbuf == NULL)
	{
        printf("gdk_pixbuf_new_from_data Faild \n");
		return false;
	}

    GtkWidget* gtk_image = gtk_image_new_from_pixbuf (pixbuf);

	if (!gtk_image)
	{
            printf("mage_new Faild \n");
            return false;
	}


	gtk_container_add (GTK_CONTAINER (window), gtk_image);
	gtk_widget_show_all (window);	
	gtk_main();

	return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{
     const int BUFSIZE = 256;
  char title[BUFSIZE];

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;

  char* file = "images/uparrow.png";

    if(argc == 2){
        file = argv[1];
    } else {
        printf("Usage %s <pngFile> \n",  argv[0]);
    }

    printf("%s \n",  file);

    char* fname = get_filename_with_ext(file);
    strcpy(title, "libpng: ");
    strcat(title, fname);
    printf("%s \n",  title);

BITMAPDATA_t bitmap;

  if( !pngFileReadDecode(&bitmap, file) ){
    printf("pngFileReadDecode error\n");
    return false;
  }

 int width = bitmap.width;
  int height = bitmap.height;
 int ch = bitmap.ch;

  printf("width = %d\n", width);
  printf("height = %d\n", height);
  printf("ch = %d\n", ch);


// open window
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), WIN_WIDTH, WIN_HEIGHT);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

bool ret = gtk_show(window, bitmap.data, width, height, ch);
    if( !ret) {
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
