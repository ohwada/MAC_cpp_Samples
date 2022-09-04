/**
 *  button.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Button");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    button  = gtk_button_new_with_label ("Quit");
    gtk_widget_set_size_request     (button, 100, 25);
    gtk_widget_set_halign           (button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign           (button, GTK_ALIGN_CENTER);
    gtk_container_add               (GTK_CONTAINER(window), button);
    
    g_signal_connect                (G_OBJECT(button), "clicked",
                                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect                (G_OBJECT(window), "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
