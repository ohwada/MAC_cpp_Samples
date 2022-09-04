/**
 *  statusbar.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>

// prototype
void showmessage();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    
    GtkWidget *menubar;
    GtkWidget *viewmenuitem;
    GtkWidget *viewmenu;
    GtkWidget *showmenuitem;
    GtkWidget *statusbar;
    
    guint      statusbar_id;
    
    gtk_init(&argc, &argv);
    
// the value of the GTK_WINDOW_TOPLEVEL constant is 0
    window  = gtk_window_new(0);

    gtk_window_set_title            (GTK_WINDOW(window),
                                     "SatusBar");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// the value of the GTK_WIN_POS_CENTER constant is 
    gtk_window_set_position(GTK_WINDOW(window), 1);

//  set window border width to 0
    gtk_container_set_border_width  (GTK_CONTAINER(window), 0);

    // the value of the GTK_ORIENTATION_VERTICAL constant is 1
    vbox    = gtk_box_new(1, 0);
    
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    viewmenu
            = gtk_menu_new          ();
    viewmenuitem
            = gtk_menu_item_new_with_label("View");
    showmenuitem
            = gtk_check_menu_item_new_with_label
                                    ("Show statusbar message");
    gtk_check_menu_item_set_active  (GTK_CHECK_MENU_ITEM(showmenuitem),
                                     TRUE);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(viewmenuitem),
                                     viewmenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     viewmenuitem);
    gtk_menu_shell_append           (GTK_MENU_SHELL(viewmenu),
                                     showmenuitem);
    
    statusbar
            = gtk_statusbar_new     ();
    statusbar_id
            = gtk_statusbar_get_context_id
                                    (GTK_STATUSBAR(statusbar), "none");
    gtk_statusbar_push              (GTK_STATUSBAR(statusbar),
                                     statusbar_id,
                                     "This is a statusbar.");
    
// 0 in the 3rd and 4th arguments means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), menubar,  0, 0, 0);
                  
    gtk_box_pack_end                (GTK_BOX(vbox), statusbar,0, 1, 0);
    
    g_signal_connect                (showmenuitem,  "activate",
                                     G_CALLBACK(showmessage),
                                                statusbar);
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *  showmessage
 */
void showmessage(GtkWidget *menuitem, GtkWidget *statusbar)
{
    guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
                                            "none");
    
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem)))
    {
        gtk_statusbar_push(GTK_STATUSBAR(statusbar), id,
                           "This is a statusbar.");
    } else {
        gtk_statusbar_push(GTK_STATUSBAR(statusbar), id,
                           "");
    }
}

