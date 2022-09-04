/**
 * box.c
 * 2022-06-01 K.OHWADA
 */

// Box is a container that allows widgets to be arranged horizontally or vertically.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *textview;
    GtkWidget *swin;
    GtkWidget *frame;
    GtkWidget *ok;
    GtkWidget *cancel;
    GtkWidget *hbox;
    GtkWidget *vbox;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new         (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Box");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    
    textview    = gtk_text_view_new         ();
    swin        = gtk_scrolled_window_new   (NULL, NULL);
    gtk_scrolled_window_set_policy          (GTK_SCROLLED_WINDOW(swin),
                                             GTK_POLICY_AUTOMATIC,
                                             GTK_POLICY_AUTOMATIC);
    frame       = gtk_frame_new             (NULL);
    gtk_container_add                       (GTK_CONTAINER(swin),
                                             textview);
    gtk_container_add                       (GTK_CONTAINER(frame),
                                             swin);
    
    ok          = gtk_button_new_with_label ("OK");
    cancel      = gtk_button_new_with_label ("Cancel");
    gtk_widget_set_size_request             (ok,     100, 25);
    gtk_widget_set_size_request             (cancel, 100, 25);
    
    hbox        = gtk_box_new       (GTK_ORIENTATION_HORIZONTAL, 15);

// 0 in the 2nd and 3rd arguments means FALSE. 
// The fourth argument is the number 0 */
    gtk_box_pack_start(GTK_BOX(hbox), ok,     0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), cancel, 0, 0, 0);


    gtk_widget_set_halign           (hbox, GTK_ALIGN_END);
    
    vbox        = gtk_box_new       (GTK_ORIENTATION_VERTICAL, 15);

    gtk_box_pack_start(GTK_BOX(vbox), frame,  1, 1, 0);
     
    gtk_box_pack_start(GTK_BOX(vbox), hbox,   0, 0, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    g_signal_connect                (G_OBJECT(window), "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
    
