/**
 * gdk_pixbuf_ne.cppw_from_file.c
 * 2022-06-01 K.OHWADA
 */

// load image from file using
// gdk_pixbuf_ne.cppw_from_file
// reference :  https://fut-nis.hatenadiary.jp/entry/20121113/1352810731

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


/*
 * main
 */
int main(int argc, char** argv)
{

const char* WIN_TITLE = "GTK3: gdk";
 
char* file = "images/vegetables.jpg";



    if(argc == 2) {
    		file = argv[1];
	} else {
        printf("Usage: %s <imageFile> \n", argv[0] );
    }

        printf("%s \n", file );

	gtk_init (&argc, &argv);

	GError *error = NULL;

// read image
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (file, &error);
	if (pixbuf == NULL)
	{
		printf("Error:\t%s\n", error->message);
		g_error_free (error);
		return EXIT_FAILURE;
	}

	int width = gdk_pixbuf_get_width (pixbuf);
	int height = gdk_pixbuf_get_height (pixbuf);

printf("w=%d, h=%d \n", width, height);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    

	GtkWidget *image = gtk_image_new_from_pixbuf (pixbuf);
	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);	
	gtk_main ();

	return EXIT_SUCCESS;
}
