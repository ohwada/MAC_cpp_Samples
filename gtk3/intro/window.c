/**
 * window.c
 * 2022-06-01 K.OHWADA
 */

// show window witj button
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    
    gtk_init(&argc, &argv);
    
// GTK_WINDOW_TOPLEVEL is 0
    window = gtk_window_new(0); 

    gtk_window_set_title            (GTK_WINDOW(window), "Window");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// GTK_WIN_POS_CENTER is 1
    gtk_window_set_position         (GTK_WINDOW(window), 1);

    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    button = gtk_button_new_with_label("Button");
    gtk_container_add(GTK_CONTAINER(window), button);
    
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}
