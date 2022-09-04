/**
 *  listbox.c
 * 2022-06-01 K.OHWADA
 */

// Widget that displays List.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// prototype
void list_selected();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *listbox;
    GtkWidget *label;
    GtkWidget *vbox;
    
    gtk_init(&argc, &argv);
    
// GTK_WINDOW_TOPLEVEL constant is 0 
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "ListBox");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// GTK_WIN_POS_CENTER constant is 1 
    gtk_window_set_position(GTK_WINDOW(window), 1);

    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    listbox = gtk_list_box_new      ();
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Windows"),  -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("macOS"),    -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Ubuntu"),   -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Fedora"),   -1);
    
    label   = gtk_label_new         (NULL);
    
    vbox    = gtk_box_new           (1, 15);

// GTK_ORIENTATION_HORIZONTAL is 0, 
// GTK_ORIENTATION_VERTICAL is 1 */
    gtk_box_pack_start(GTK_BOX(vbox), listbox, 1, 1, 0);

// the 3rd and 4th arguments describe TRUE as 1 and FALSE as 0 
    gtk_box_pack_end(GTK_BOX(vbox), label,   0, 0, 0);

    
// It can also be placed from the back 
// with gtk_box_pack_end function.
    gtk_container_add(GTK_CONTAINER(window), vbox);
    

// You can also use the event "row-activated"
    g_signal_connect( listbox,   "row_selected",
                                     G_CALLBACK(list_selected), label);

    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *  list_selected
 */
void
list_selected(GtkListBox *list, GtkListBoxRow * row, GtkLabel *label)
{
    GtkWidget *child = gtk_bin_get_child(GTK_BIN(row));
    gtk_label_set_text(label, gtk_label_get_text(GTK_LABEL(child)));
}

