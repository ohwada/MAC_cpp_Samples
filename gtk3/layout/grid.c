/**
 * grid.c
 * 2022-06-01 K.OHWADA
 */

// // Grid is container for arranging widgets in a grid.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_layout.php

#include <gtk/gtk.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *title;
    GtkWidget *author;
    GtkWidget *review;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *textview;
    GtkWidget *swin;
    GtkWidget *frame;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Grid");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 20);
    
    grid    = gtk_grid_new          ();
    gtk_container_add               (GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing     (GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing        (GTK_GRID(grid), 10);
    
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
    gtk_scrolled_window_set_policy          (GTK_SCROLLED_WINDOW(swin),
                                             GTK_POLICY_AUTOMATIC,
                                             GTK_POLICY_AUTOMATIC);
    gtk_container_add               (GTK_CONTAINER(swin), textview);
    gtk_container_add               (GTK_CONTAINER(frame), swin);
        
    gtk_grid_attach         (GTK_GRID(grid), title,  0, 0,  1, 1);
    gtk_grid_attach         (GTK_GRID(grid), entry1, 1, 0,  1, 1);
    gtk_grid_attach         (GTK_GRID(grid), author, 0, 1,  1, 1);
    gtk_grid_attach         (GTK_GRID(grid), entry2, 1, 1,  1, 1);
    gtk_grid_attach         (GTK_GRID(grid), review, 0, 2,  1, 1);
    gtk_grid_attach         (GTK_GRID(grid), frame,  1, 2,  1, 1);
    gtk_entry_set_max_width_chars   (GTK_ENTRY(entry1), 10000);
        
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
	
