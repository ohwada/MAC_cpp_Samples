/**
 *  colordialog2.c
 * 2022-06-01 K.OHWADA
 */

// Sample using toolbar
// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GdkRGBA     color;

// prototype
void        select_color();
void        draw_callback();
void        select_color();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget   *window;
    GtkWidget   *vbox;
    GtkWidget   *toolbar;
    GtkToolItem *coloritem;
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
    
    toolbar = gtk_toolbar_new       ();

// 0 in the 3rd and 4th arguments means FALSE. 
// the fifth argument is the number 0
    gtk_box_pack_start (GTK_BOX(vbox), toolbar, 0, 0, 0);

    // this function and the GTK_STOCK constant are deprecated.
// runs fine 
    coloritem
            = gtk_tool_button_new_from_stock
                                    (GTK_STOCK_SELECT_COLOR);

    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), coloritem,
                                     -1);
    
    darea   = gtk_drawing_area_new  ();
    frame   = gtk_frame_new         (NULL);
    gtk_container_set_border_width  (GTK_CONTAINER(frame), 15);
    gtk_container_add               (GTK_CONTAINER(frame), darea);

//  1 in the 3rd and 4th arguments means TRUE. 
// the fifth argument is the number 0
    gtk_box_pack_end  (GTK_BOX(vbox), frame, 1, 1, 0);
    
    gdk_rgba_parse                  (&color ,"rgb(127, 127, 127)");
    
    g_signal_connect                (darea,         "draw",
                                     G_CALLBACK(draw_callback), NULL);
    
    g_signal_connect                (coloritem,     "clicked",
                                     G_CALLBACK(select_color), window);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return   0;
}


/**
 *  draw_callback
 */
void    draw_callback(GtkWidget *darea, cairo_t *cr)
{
    gdk_cairo_set_source_rgba       (cr, &color);
    cairo_paint                     (cr);
}


/**
 *  select_color
 */
void    select_color(GtkWidget *widget, gpointer window)
{
    GtkWidget   *dialog;
    gint        result;
    
    dialog  = gtk_color_chooser_dialog_new
                                    ("Select color",
                                     GTK_WINDOW(window));
    
    result = gtk_dialog_run         (GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK)
    {
        gtk_color_chooser_get_rgba  (GTK_COLOR_CHOOSER(dialog),
                                     &color);
        gtk_widget_queue_draw       (window);
    }
    gtk_widget_destroy              (dialog);
}
	
