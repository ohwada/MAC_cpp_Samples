/**
 *  toolbar2.c
 * 2022-06-01 K.OHWADA
 */

// Sample for GTK2
// Toolbar icons are not displayed correctly on macOS
// reference : https://vivacocoa.jp/cpp/gtk/gtk_menu.php

#include <gtk/gtk.h>

// global
GtkToolItem *undo;
GtkToolItem *redo;

// prototype
void undo_redo();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    
    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *quit;
    GtkWidget *label;
        
    gtk_init(&argc, &argv);
    
// the value of the GTK_WINDOW_TOPLEVEL constant is 0
    window  = gtk_window_new(0);
    
    gtk_window_set_title            (GTK_WINDOW(window), "ToolBar");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);

//  1 is the value of the GTK_WIN_POS_CENTER constant
    gtk_window_set_position(GTK_WINDOW(window), 1);

// when setting menus and toolbars, 
// it is better not to have borders
    //gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
// 1 is the value of the GTK_ORIENTATION_VERTICAL constant
    vbox    = gtk_box_new(1, 0);
    
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    toolbar = gtk_toolbar_new       ();

// It seems that the icon is displayed by default even if it is not set
    //gtk_toolbar_set_style           (GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    gtk_container_set_border_width  (GTK_CONTAINER(toolbar), 0);
    
    undo    = gtk_tool_button_new_from_stock("gtk-undo");

// this function is not required, 
// but we will use the name later to distinguish the tool buttons
    gtk_widget_set_name(GTK_WIDGET(undo), "undo");

    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), undo, -1);
    
    redo    = gtk_tool_button_new_from_stock("gtk-redo");

// this function is not required, 
// but we will use the name later to distinguish the tool buttons
    gtk_widget_set_name(GTK_WIDGET(redo), "redo");

    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), redo, -1);
    gtk_widget_set_sensitive        (GTK_WIDGET(redo), FALSE);
    
    sep     = gtk_separator_tool_item_new();
    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), sep,  -1);
    
    quit    = gtk_tool_button_new_from_stock("gtk-quit");
    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), quit, -1);
    
    label   = gtk_label_new         ("4");
    
// 0 in the 3rd and 4th arguments of the gtk_box_pack_start function means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, 0, 0, 0);

// 1 in the 3rd and 4th arguments of the tk_box_pack_end function means TRUE
    gtk_box_pack_end(GTK_BOX(vbox), label,   1, 1, 0);
    
    g_signal_connect                (undo,      "clicked",
                                     G_CALLBACK(undo_redo),    label);
     
     g_signal_connect               (redo,      "clicked",
                                     G_CALLBACK(undo_redo),    label);
    
    g_signal_connect                (quit,      "clicked",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 * undo_redo
 */
void undo_redo(GtkWidget *widget, GtkLabel *label)
{
    const gchar *text = gtk_label_get_text(label);
    const gchar *name = gtk_widget_get_name(widget);
    guchar       num  = atoi(text);
    
// there is also a function called g_strcmp0
    if (strcmp(name, "undo") == 0)
    {
        num--;
        switch (num)
        {
        case 0:
            gtk_widget_set_sensitive(GTK_WIDGET(undo), FALSE);
            break;
        case 3:
            gtk_widget_set_sensitive(GTK_WIDGET(redo), TRUE);
            break;
        }
    } else {
        num++;
        switch (num)
        {
        case 1:
            gtk_widget_set_sensitive(GTK_WIDGET(undo), TRUE);
            break;
        case 4:
            gtk_widget_set_sensitive(GTK_WIDGET(redo), FALSE);
            break;
        }
    }
    gchar *str = g_strdup_printf("%d", num);
    gtk_label_set_text(label, str);
    g_free(str);
}
	