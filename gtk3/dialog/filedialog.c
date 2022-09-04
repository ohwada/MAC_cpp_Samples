/**
 *  filedialog.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GtkWidget   *label;

// prototype
void        select_file();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget   *window;
    GtkWidget   *vbox;
    GtkWidget   *menubar;
    GtkWidget   *filemenu;
    GtkWidget   *filemenuitem;
    GtkWidget   *openmenuitem;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "File dialog");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    
// The value of the GTK_ORIENTATION_VERTICAL constant is 1 
    vbox    = gtk_box_new           (1, 0); // 1

    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    filemenu
            = gtk_menu_new          ();
            
    filemenuitem
            = gtk_menu_item_new_with_label("File");
    openmenuitem
            = gtk_menu_item_new_with_label("Open");
    
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     filemenuitem);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(filemenuitem),
                                     filemenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     openmenuitem);
    
    label   = gtk_label_new         ("Unselected");
    gtk_label_set_justify           (GTK_LABEL(label),
                                     GTK_JUSTIFY_CENTER);   // 2
    
    gtk_box_pack_start              (GTK_BOX(vbox), menubar, 0, 0, 0);

// 0 means FALSE and 1 means TRUE in the 3rd and 4th arguments. 
// the fifth argument is the number 0 
    gtk_box_pack_end (GTK_BOX(vbox), label,   1, 0, 0);

    
    g_signal_connect                (openmenuitem,  "activate",
                                     G_CALLBACK(select_file), window);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();
    return                          0;
}


/**
 *  select_file
 */
void    select_file(GtkWidget *widget, gpointer window)
{
    GtkWidget   *dialog;
    gint        result;
    
    dialog  = gtk_file_chooser_dialog_new
                                    ("Select File",
                                     window,
                                     GTK_FILE_CHOOSER_ACTION_OPEN,
// For save dialog, set to GTK_FILE_CHOOSER_ACTION_SAVE
                                     ("Cancel"),
                                     GTK_RESPONSE_CANCEL,
                                     ("Select"),
                                     GTK_RESPONSE_ACCEPT,
                                     NULL);
    
    result  = gtk_dialog_run        (GTK_DIALOG(dialog));
    
// GTK_RESPONSE_ACCEPT constant is -3
    if (result == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser
            = GTK_FILE_CHOOSER(dialog);
        filename
            = gtk_file_chooser_get_filename
                                    (chooser);
        
        gtk_label_set_text          (GTK_LABEL(label), filename);
        g_free                      (filename);
    } else {
        gtk_label_set_text          (GTK_LABEL(label), "Unselected");
    }
    gtk_widget_destroy              (dialog);
}
    

