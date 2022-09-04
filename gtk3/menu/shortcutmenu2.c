/**
 *  shortcutmenu2.c
 * 2022-06-01 K.OHWADA
 */


// sample with both image and shortcut key
// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>

// prototype
void on_new();

/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    
    GtkWidget *menubar;
    GtkWidget *filemenu;
    GtkWidget *editmenu;
    GtkWidget *filemenuitem;
    GtkWidget *editmenuitem;
    GtkWidget *newmenuitem;
    GtkWidget *openmenuitem;
    GtkWidget *savemenuitem;
    GtkWidget *separator1;
    GtkWidget *quitmenuitem;
    GtkWidget *undomenuitem;
    GtkWidget *redomenuitem;
    GtkWidget *separator2;
    GtkWidget *cutmenuitem;
    GtkWidget *copymenuitem;
    GtkWidget *pastemenuitem;
    
    GtkAccelGroup * accel_group = NULL;
    
    gtk_init(&argc, &argv);
    
// the value of the GTK_WINDOW_TOPLEVEL constant is 0
    window  = gtk_window_new(0);
    
    gtk_window_set_title            (GTK_WINDOW(window), "SubMenu");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// the value of the GTK_WIN_POS_CENTER constant is 1
    gtk_window_set_position(GTK_WINDOW(window), 1);

    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
// the value of the GTK_ORIENTATION_VERTICAL constant is 1
    vbox    = gtk_box_new(1, 0);

    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    filemenu
            = gtk_menu_new          ();
    editmenu
            = gtk_menu_new          ();
    accel_group
            = gtk_accel_group_new   ();
    gtk_window_add_accel_group      (GTK_WINDOW(window), accel_group);
    
    filemenuitem
    = gtk_menu_item_new_with_label("File");
    newmenuitem
    = gtk_image_menu_item_new_from_stock("gtk-new",  accel_group);
    openmenuitem
    = gtk_image_menu_item_new_from_stock("gtk-open", accel_group);
    savemenuitem
    = gtk_image_menu_item_new_from_stock("gtk-save", accel_group);
    separator1
    = gtk_separator_menu_item_new ();
    quitmenuitem
    = gtk_image_menu_item_new_from_stock("gtk-quit", accel_group);
    editmenuitem
    = gtk_menu_item_new_with_label("Edit");
    undomenuitem
    = gtk_image_menu_item_new_from_stock("gtk-undo", accel_group);
    redomenuitem
    = gtk_image_menu_item_new_from_stock("gtk-redo", accel_group);
    separator2
    = gtk_separator_menu_item_new ();
    cutmenuitem
    = gtk_image_menu_item_new_from_stock("gtk-cut",  accel_group);
    copymenuitem
    = gtk_image_menu_item_new_from_stock("gtk-copy", accel_group);
    pastemenuitem
    = gtk_image_menu_item_new_from_stock("gtk-paste",accel_group);
    
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(filemenuitem),
                                     filemenu);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(editmenuitem),
                                     editmenu);
            
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     filemenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     editmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     newmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     openmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     savemenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     separator1);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     quitmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     undomenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     redomenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     separator2);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     cutmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     copymenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     pastemenuitem);
    
// 0 in the 3rd and 4th arguments means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), menubar, 0, 0, 0);
    
    g_signal_connect                (newmenuitem,   "activate",
                                     G_CALLBACK(on_new),        NULL);
    g_signal_connect                (quitmenuitem,  "activate",
                                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return  0;
}


/**
 * on_new
 */
void on_new()
{
    printf("New\n");
}
	
