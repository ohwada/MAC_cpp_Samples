/**
 * hello.c
 * 2022-06-01 K.OHWADA
 */

// show hello window
// reference : https://vivacocoa.jp/cpp/gtk/gtk_firststep.php

#include <gtk/gtk.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget * window;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show(window);
    gtk_main();

    return 0;
}


    
