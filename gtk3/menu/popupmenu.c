/**
 *  popupmenu.c
 * 2022-06-01 K.OHWADA
 */

// Pop-up menu is a menu that appears when You right-click.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>

// prototype
void show_popup();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    
    GtkWidget *menu;
    GtkWidget *ebox;
    GtkWidget *minimize;
    GtkWidget *quit;
    
    gtk_init(&argc, &argv);
    
// the value of the GTK_WINDOW_TOPLEVEL constant is 0
    window  = gtk_window_new(0);

    gtk_window_set_title            (GTK_WINDOW(window), "PopupMenu");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

// the value of the GTK_WIN_POS_CENTER constant is 1
    gtk_window_set_position(GTK_WINDOW(window), 1);
    
// border is not set this time
    //gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    ebox    = gtk_event_box_new     ();
    gtk_container_add               (GTK_CONTAINER(window), ebox);
    
    menu    = gtk_menu_new          ();
    minimize
            = gtk_menu_item_new_with_label
                                    ("Minimize");
    quit    = gtk_menu_item_new_with_label
                                    ("Quit");
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu), minimize);
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu), quit);
    gtk_widget_show                 (minimize);
    gtk_widget_show                 (quit);
    
    g_signal_connect_swapped        (minimize,  "activate",
                                     G_CALLBACK(gtk_window_iconify),
                                                              window);
    g_signal_connect                (quit,      "activate",
                                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect_swapped        (ebox,      "button-press-event",
                                     G_CALLBACK(show_popup),    menu);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *   show_popup
 */
void show_popup(GtkWidget *widget, GdkEvent *event)
{
    const gint RIGHT_CLICK = 3;
    
    GdkEventButton *eventbutton = (GdkEventButton *)event;
    if (eventbutton->button == RIGHT_CLICK)
    {
        gtk_menu_popup_at_pointer(GTK_MENU(widget), event);
    }
}
	