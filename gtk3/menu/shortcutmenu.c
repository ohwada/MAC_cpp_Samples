/**
 *  shortcutmenu.c
 * 2022-06-01 K.OHWADA
 */

// sample of only shortcut keys without images
// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>

// prototype
void select_menuitem();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget       *window;
    GtkWidget       *vbox;
    GtkWidget       *menubar;
    GtkWidget       *filemenu;
    GtkWidget       *filemenuitem;
    GtkWidget       *newmenuitem;
    GtkWidget       *openmenuitem;
    GtkWidget       *savemenuitem;
    GtkWidget       *separator;
    GtkWidget       *quitmenuitem;
    GtkWidget       *label;
    GtkAccelGroup   *accel_group;
    
    gtk_init(&argc, &argv);

    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "Shourtcut menu");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    filemenu
            = gtk_menu_new          ();
    filemenuitem
            = gtk_menu_item_new_with_label  ("File");
    newmenuitem
            = gtk_menu_item_new_with_label  ("New");
    openmenuitem
            = gtk_menu_item_new_with_label  ("Open");
    savemenuitem
            = gtk_menu_item_new_with_label  ("Save");
    separator
            = gtk_separator_menu_item_new   ();
    quitmenuitem
            = gtk_menu_item_new_with_label  ("Quit");
    
    label   = gtk_label_new                 ("Unselected");        
    
    accel_group = gtk_accel_group_new ();
    gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

    gtk_box_pack_start              (GTK_BOX(vbox), menubar, 0, 0, 0);
    gtk_box_pack_end                (GTK_BOX(vbox), label,   1, 0, 0);
    
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     filemenuitem);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(filemenuitem),
                                     filemenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     newmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     openmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     savemenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     separator);
    gtk_menu_shell_append           (GTK_MENU_SHELL(filemenu),
                                     quitmenuitem);
    gtk_widget_add_accelerator  (newmenuitem,  "activate", accel_group,
                                 GDK_KEY_n, GDK_CONTROL_MASK,
                                 GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator  (openmenuitem, "activate", accel_group,
                                 GDK_KEY_o, GDK_CONTROL_MASK,
                                 GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator  (savemenuitem, "activate", accel_group,
                                 GDK_KEY_s, GDK_CONTROL_MASK, 
                                 GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator  (quitmenuitem, "activate", accel_group,
                                 GDK_KEY_q, GDK_CONTROL_MASK,
                                 GTK_ACCEL_VISIBLE);
    g_signal_connect            (newmenuitem,   "activate",
                                 G_CALLBACK(select_menuitem),   label);
    g_signal_connect            (openmenuitem,  "activate",
                                 G_CALLBACK(select_menuitem),   label);
    g_signal_connect            (savemenuitem,  "activate",
                                 G_CALLBACK(select_menuitem),   label);
    g_signal_connect            (quitmenuitem,  "activate",
                                 G_CALLBACK(gtk_main_quit),     NULL);
    g_signal_connect            (window,        "destroy",
                                 G_CALLBACK(gtk_main_quit),     NULL);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


/**
 * select_menuitem
 */
void select_menuitem(GtkWidget *widget, gpointer label)
{
    const gchar *name = gtk_menu_item_get_label(GTK_MENU_ITEM(widget));
    gtk_label_set_label(label, name);
}

