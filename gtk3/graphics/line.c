/**
 * line.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_graphics.php

#include <gtk/gtk.h>

// prototype
void draw_callback();


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *da;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Line");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    da      = gtk_drawing_area_new  ();
    gtk_container_add               (GTK_CONTAINER(window), da);
    
    g_signal_connect                (da,     "draw",
                                     G_CALLBACK(draw_callback), NULL);
    g_signal_connect                (window, "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 * draw_callback
 */
void draw_callback(GtkWidget *da, cairo_t *cr)
{
    GdkRGBA color;
    gdouble dashes[]= {50.0, 10.0, 10.0, 10.0};
    guchar  num     = sizeof(dashes) / sizeof(dashes[0]);
    
    cairo_move_to(cr, 0, 10);
    cairo_line_to(cr, 300, 10);
    cairo_stroke(cr);
    
    cairo_move_to(cr, 0, 50);
    cairo_line_to(cr, 300, 50);
    gdk_rgba_parse(&color, "#f00");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_set_dash(cr, dashes, num, 0.0);
    cairo_set_line_width(cr, 1.0);
    cairo_stroke(cr);
    
    cairo_move_to(cr, 0, 90);
    cairo_line_to(cr, 300, 90);
    cairo_set_dash(cr, dashes, num, 25.0);
    gdk_rgba_parse(&color, "#0f0");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_stroke(cr);
    
    cairo_move_to(cr, 20, 130);
    cairo_line_to(cr, 250, 130);
    cairo_set_dash(cr, dashes, 0, 25.0);
    gdk_rgba_parse(&color, "#00f");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_width(cr, 20.0);
    cairo_stroke(cr);
    
    cairo_move_to(cr, 20, 170);
    cairo_line_to(cr, 250, 170);
    gdk_rgba_parse(&color, "#f0f");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
    cairo_stroke(cr);
    
    cairo_move_to(cr, 20, 200);
    cairo_line_to(cr, 250, 200);
    gdk_rgba_parse(&color, "#ff0");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_stroke(cr);
}

