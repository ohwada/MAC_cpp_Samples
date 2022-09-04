/**
 *   radiobutton.c
 * 2022-06-01 K.OHWADA
 */

// Radio buttons are used to select one from multiple buttons (choices).
// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// may be required depending on the environment.
//#include <glib.h>

// prototype
void on_toggle();


/**
 *   main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *frame;
    GtkWidget *vbox;;
    GtkWidget *hbox;
    GtkWidget *red;
    GtkWidget *green;
    GtkWidget *blue;
    GSList    *group = NULL;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "RadioButton");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    frame   = gtk_frame_new         ("Red");
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL,   0);
    hbox    = gtk_box_new           (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add               (GTK_CONTAINER(window), frame);
    gtk_container_add               (GTK_CONTAINER(frame),  vbox);
    gtk_box_pack_start              (GTK_BOX(vbox), hbox,   1, 0, 0);
    
    red     = gtk_radio_button_new_with_label
                                    (group,                 "Red");
    green   = gtk_radio_button_new_with_label_from_widget
                                    (GTK_RADIO_BUTTON(red), "Green");
    blue    = gtk_radio_button_new_with_label_from_widget
                                    (GTK_RADIO_BUTTON(red), "Blue");
    
    gtk_box_pack_start              (GTK_BOX(hbox), red,    1, 0, 0);
    gtk_box_pack_start              (GTK_BOX(hbox), green,  1, 0, 0);
    gtk_box_pack_start              (GTK_BOX(hbox), blue,   1, 0, 0);
    
    g_signal_connect                (red,           "toggled",
                                     G_CALLBACK(on_toggle),     frame);
    g_signal_connect                (green,         "toggled",
                                     G_CALLBACK(on_toggle),     frame);
    g_signal_connect                (blue,          "toggled",
                                     G_CALLBACK(on_toggle),     frame);
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *   on_toggle
 */
void on_toggle(GtkButton *button, GtkFrame *frame)
{
    const gchar * label = gtk_button_get_label(button);
    gtk_frame_set_label(frame, label);
}

	