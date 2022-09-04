/**
 *  review.c
 * 2022-06-01 K.OHWADA
 */

// grid arrangement using Box
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *title;
    GtkWidget *author;
    GtkWidget *review;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *textview;
    GtkWidget *swin;
    GtkWidget *frame;
    GtkWidget *hbox1;
    GtkWidget *hbox2;
    GtkWidget *hbox3;
    GtkWidget *vbox;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Review");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 20);
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL,   10);
    hbox1   = gtk_box_new           (GTK_ORIENTATION_HORIZONTAL, 10);
    hbox2   = gtk_box_new           (GTK_ORIENTATION_HORIZONTAL, 10);
    hbox3   = gtk_box_new           (GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    title       = gtk_label_new     ("Title");
    author      = gtk_label_new     ("Author");
    review      = gtk_label_new     ("Review");
    entry1      = gtk_entry_new     ();
    entry2      = gtk_entry_new     ();
    textview    = gtk_text_view_new ();
    
    gtk_widget_set_size_request     (title,  40, -1);
    gtk_widget_set_size_request     (author, 40, -1);
    gtk_widget_set_size_request     (review, 40, -1);
    gtk_label_set_xalign            (GTK_LABEL(title),  0);
    gtk_label_set_yalign            (GTK_LABEL(title),  0);
    gtk_label_set_xalign            (GTK_LABEL(author), 0);
    gtk_label_set_yalign            (GTK_LABEL(author), 0);
    gtk_label_set_xalign            (GTK_LABEL(review), 0);
    gtk_label_set_yalign            (GTK_LABEL(review), 0);
    frame       = gtk_frame_new     (NULL);
    swin        = gtk_scrolled_window_new   (NULL, NULL);
    gtk_scrolled_window_set_policy          (GTK_SCROLLED_WINDOW(swin),
                                             GTK_POLICY_AUTOMATIC,
                                             GTK_POLICY_AUTOMATIC);
    gtk_container_add               (GTK_CONTAINER(swin), textview);
    gtk_container_add               (GTK_CONTAINER(frame), swin);
    
    gtk_box_pack_start              (GTK_BOX(hbox1), title,  0, 0, 0);
    gtk_box_pack_end                (GTK_BOX(hbox1), entry1, 1, 1, 0);
    gtk_box_pack_start              (GTK_BOX(vbox), hbox1,   0, 0, 0);
    
    gtk_box_pack_start              (GTK_BOX(hbox2), author, 0, 0, 0);
    gtk_box_pack_end                (GTK_BOX(hbox2), entry2, 1, 1, 0);
    gtk_box_pack_start              (GTK_BOX(vbox),  hbox2,  0, 0, 0);
    
    gtk_box_pack_start              (GTK_BOX(hbox3), review, 0, 0, 0);
    gtk_box_pack_end                (GTK_BOX(hbox3), frame,  1, 1, 0);
    gtk_box_pack_end                (GTK_BOX(vbox), hbox3,   1, 1, 0);
    
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

