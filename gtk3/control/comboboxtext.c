/**
 *  comboboxtext.c
 * 2022-06-01 K.OHWADA
 */

// Widget that allows You to select any item from a list of strings
// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// prototype
void combo_selected();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *combo;
    GtkWidget *label;
    GtkWidget *vbox;
    
    gtk_init(&argc, &argv);
    
// GTK_WINDOW_TOPLEVEL is 0
    window  = gtk_window_new(0);
    
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "ComboBoxText");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// GTK_WIN_POS_CENTER is 1
    gtk_window_set_position(GTK_WINDOW(window), 1);
    
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    combo   = gtk_combo_box_text_new();
    gtk_combo_box_text_append       (GTK_COMBO_BOX_TEXT(combo), NULL,
                                     "Windows");
    gtk_combo_box_text_append       (GTK_COMBO_BOX_TEXT(combo), NULL,
                                     "macOS");
    gtk_combo_box_text_append       (GTK_COMBO_BOX_TEXT(combo), NULL,
                                     "Ubuntu");
    gtk_combo_box_text_append       (GTK_COMBO_BOX_TEXT(combo), NULL,
                                     "Fedora");

    label   = gtk_label_new("Unselected");
    
    vbox    = gtk_box_new           (1, 0);

// GTK_ORIENTATION_HORIZONTAL is 0, // GTK_ORIENTATION_VERTICAL is 1 
    gtk_box_pack_start(GTK_BOX(vbox), combo, 0, 0, 0);

    
// the 3rd and 4th arguments describe TRUE as 1 and FALSE as 0 
    gtk_box_pack_end(GTK_BOX(vbox), label, 1, 0, 0);


// It can also be placed from the back 
// with tk_box_pack_end function
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    g_signal_connect                (combo,     "changed",
                                     G_CALLBACK(combo_selected),label);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *  combo_selected
 */
void combo_selected(GtkComboBoxText *combo, GtkLabel *label)
{
    gchar *os;
    os = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    gtk_label_set_text(label, os);
    /* label引数をGtkWidget型とし、GTK_LABEL(label)とキャストすることも可 */
    //printf("%s\n", os);
}
	