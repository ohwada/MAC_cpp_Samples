/**
 *  table.c
 * 2022-06-01 K.OHWADA
 */

// Table is container for arranging widgets in a grid.
// Table has been deprecated in favor of Grid.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *title;
    GtkWidget *author;
    GtkWidget *review;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *textview;
    GtkWidget *swin;
    GtkWidget *frame;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new         (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Table");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    table       = gtk_table_new     (3, 2, FALSE);
    gtk_container_add               (GTK_CONTAINER(window), table);
    
    title       = gtk_label_new     ("Title");
    author      = gtk_label_new     ("Author");
    review      = gtk_label_new     ("Review");
    entry1      = gtk_entry_new     ();
    entry2      = gtk_entry_new     ();
    textview    = gtk_text_view_new ();
    gtk_label_set_xalign            (GTK_LABEL(title),  0);
    gtk_label_set_yalign            (GTK_LABEL(title),  0);
    gtk_label_set_xalign            (GTK_LABEL(author), 0);
    gtk_label_set_yalign            (GTK_LABEL(author),  0);
    gtk_label_set_xalign            (GTK_LABEL(review), 0);
    gtk_label_set_yalign            (GTK_LABEL(review), 0);
    frame       = gtk_frame_new     (NULL);
    swin        = gtk_scrolled_window_new   (NULL, NULL);
    gtk_scrolled_window_set_policy  (GTK_SCROLLED_WINDOW(swin),
                                     GTK_POLICY_AUTOMATIC,
                                     GTK_POLICY_AUTOMATIC);
    gtk_container_add               (GTK_CONTAINER(swin),   textview);                                        
    gtk_container_add               (GTK_CONTAINER(frame),  swin);
    
    gtk_table_attach    (GTK_TABLE(table), title, 0, 1, 0, 1,
                         GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach    (GTK_TABLE(table), author, 0, 1, 1, 2,
                         GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach    (GTK_TABLE(table), review, 0, 1, 2, 3,
                         GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach    (GTK_TABLE(table), entry1, 1, 2, 0, 1,
                         GTK_EXPAND|GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach    (GTK_TABLE(table), entry2, 1, 2, 1, 2,
                         GTK_EXPAND|GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach    (GTK_TABLE(table), frame,   1, 2, 2, 3,
                         GTK_EXPAND|GTK_FILL,
                         GTK_EXPAND|GTK_FILL, 5, 5);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

