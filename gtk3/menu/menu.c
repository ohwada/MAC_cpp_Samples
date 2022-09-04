/**
 *  menu.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *menubar;
    GtkWidget *filemenu;
    GtkWidget *filemenuitem;
    GtkWidget *quitmenuitem;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Menu");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);

    /* 
Do not set border because it interferes with the menu
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    */
    
// the value of the GTK_ORIENTATION_VERTICAL constant is 1
    vbox    = gtk_box_new(1, 0);

    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    filemenu
            = gtk_menu_new          ();
    
    filemenuitem
            = gtk_menu_item_new_with_label("File");
    quitmenuitem
            = gtk_menu_item_new_with_label("Quit");
            
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     filemenuitem);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(filemenuitem),
                                     filemenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     quitmenuitem);
    

// 0 in the 3rd and 4th arguments means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), menubar, 0, 0, 0);

    g_signal_connect                (quitmenuitem,  "activate",
                                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}

