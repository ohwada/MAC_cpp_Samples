/**
 *  checkbutton.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// prototype
void toggle_title(GtkWidget *widget, gpointer window);


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *check;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "CheckButton");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    check   = gtk_check_button_new_with_label   ("Show title");
    gtk_widget_set_halign           (check, GTK_ALIGN_CENTER);
    gtk_widget_set_valign           (check, GTK_ALIGN_CENTER);
    gtk_toggle_button_set_active    (GTK_TOGGLE_BUTTON(check), TRUE);
    
    gtk_container_add               (GTK_CONTAINER(window), check);
    
    g_signal_connect                (G_OBJECT(check), "clicked",
                                     G_CALLBACK(toggle_title), window);
    g_signal_connect                (G_OBJECT(window), "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
                                     
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *   toggle_title
 */
void toggle_title(GtkWidget *widget, gpointer window)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
        gtk_window_set_title(window, "CheckButton");
    } else {
        gtk_window_set_title(window, "");
    }
}


