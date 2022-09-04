/**
 * fixed.c
 * 2022-06-01 K.OHWADA
 */

// fixed is a container that can hold multiple widgets at fixed positions.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new     (0);
    gtk_window_set_title        (GTK_WINDOW(window), "Fixed");
    gtk_window_set_default_size (GTK_WINDOW(window), 320, 240);

// GTK_WIN_POS_CENTER is 1
    gtk_window_set_position         (GTK_WINDOW(window), 1);
                                   fixed = gtk_fixed_new();
    gtk_container_add           (GTK_CONTAINER(window), fixed);
    
    button1 = gtk_button_new_with_label("Button 1");
    button2 = gtk_button_new_with_label("Button 2");
    button3 = gtk_button_new_with_label("Button 3");
    gtk_fixed_put               (GTK_FIXED(fixed), button1,  30,  20);
    gtk_fixed_put               (GTK_FIXED(fixed), button2, 110, 100);
    gtk_fixed_put               (GTK_FIXED(fixed), button3, 190, 180);
    gtk_widget_set_size_request (button1, 100, 25);
    gtk_widget_set_size_request (button2, 100, 25);
    gtk_widget_set_size_request (button3, 100, 25);
    
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}
    