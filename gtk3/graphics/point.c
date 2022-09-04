/**
 *  point.c
 * 2022-06-01 K.OHWADA
 */

// reference  https://vivacocoa.jp/cpp/gtk/gtk_graphics.php

#include <gtk/gtk.h>
#include <time.h>

// prototype
void draw_callback();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *da;
    
    gtk_init(&argc, &argv);
    
    srand(time(NULL));
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Point");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    da      = gtk_drawing_area_new  ();
    gtk_container_add               (GTK_CONTAINER(window), da);
    
    g_signal_connect                (da,        "draw",
                                     G_CALLBACK(draw_callback), NULL);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();
    return                          0;
}


/**
 *  draw_callback
 */
void draw_callback(GtkWidget *da, cairo_t *cr)
{
    GdkRGBA color;
    guint x = 0, y = 0, width = 0, height = 0;
    width   = gtk_widget_get_allocated_width    (da);
    height  = gtk_widget_get_allocated_height   (da);
    
    gdk_rgba_parse              (&color, "#00f");
    gdk_cairo_set_source_rgba   (cr, &color);
    cairo_paint                 (cr);
    
    
    gdk_rgba_parse              (&color, "#fff");
    gdk_cairo_set_source_rgba   (cr, &color);
    cairo_set_line_width        (cr, 1.0);
    
    for (int i = 0; i < 1000; i++)
    {
        x = rand() % width  + 1;
        y = rand() % height + 1;
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x+1, y);
    }
    cairo_stroke(cr);
}
 