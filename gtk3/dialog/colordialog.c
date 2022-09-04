/**
 *  colordialog.c
 * 2022-06-01 K.OHWADA
 */

// https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GdkRGBA     color;

// prototype
void    select_color();
void    draw_callback();
void    select_color();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget   *window;
    GtkWidget   *vbox;
    GtkWidget   *menubar;
    GtkWidget   *editmenu;
    GtkWidget   *editmenuitem;
    GtkWidget   *colormenuitem;
    GtkWidget   *darea;
    GtkWidget   *frame;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "Color dialog");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    
    editmenu
            = gtk_menu_new          ();
    editmenuitem
            = gtk_menu_item_new_with_label("Edit");
    colormenuitem
            = gtk_menu_item_new_with_label("Color");
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     editmenuitem);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(editmenuitem),
                                     editmenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     colormenuitem);
    
    darea   = gtk_drawing_area_new  ();
    frame   = gtk_frame_new         (NULL);
    gtk_container_set_border_width  (GTK_CONTAINER(frame), 15);
    gtk_container_add               (GTK_CONTAINER(frame), darea);

// 1 in the 3rd and 4th arguments means TRUE. 
// the fifth argument is the number 0
    gtk_box_pack_end (GTK_BOX(vbox), frame, 1, 1, 0);
 
// 0 in the 3rd and 4th arguments means FALSE. 
// the fifth argument is the number 0
    gtk_box_pack_start (GTK_BOX(vbox), menubar, 0, 0, 0);

    gdk_rgba_parse                  (&color ,"rgb(127, 127, 127)");
    
    g_signal_connect                (darea,         "draw",
                                     G_CALLBACK(draw_callback), NULL);
    
    g_signal_connect                (colormenuitem, "activate",
                                     G_CALLBACK(select_color), window);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return    0;
}


/**
 *  draw_callback
 */
void  draw_callback(GtkWidget *darea, cairo_t *cr)
{
    gdk_cairo_set_source_rgba       (cr, &color);
    cairo_paint                     (cr);
}


/**
 *   select_color
 */
void  select_color(GtkWidget *widget, gpointer window)
{
    GtkWidget   *dialog;
    gint        result;
    
    dialog  = gtk_color_chooser_dialog_new
                                    ("Select color",
                                     GTK_WINDOW(window));
    
    result = gtk_dialog_run         (GTK_DIALOG(dialog));
    //printf("%d\n", GTK_RESPONSE_OK);
    if (result == GTK_RESPONSE_OK)
    {
        gtk_color_chooser_get_rgba  (GTK_COLOR_CHOOSER(dialog),
                                     &color);
        gtk_widget_queue_draw       (window);
    }
    gtk_widget_destroy              (dialog);
}
    