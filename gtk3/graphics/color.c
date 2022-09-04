/**
 *  color.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_graphics.php

#include <gtk/gtk.h>

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
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Color");
    gtk_window_set_default_size     (GTK_WINDOW(window), 410, 240);
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
 *  draw_callback
 */
void draw_callback(GtkWidget *da, cairo_t *cr)
{
    GdkRGBA color;
    
    cairo_rectangle(cr,  20, 20,  100, 75);
    gdk_rgba_parse (&color, "#0ff");        // シアン(cyan)
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill(cr);
    
    cairo_rectangle(cr, 140, 20,  100, 75);
    gdk_rgba_parse (&color, "#f0f");        // マジェンタ(magenta)
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill(cr);
    
    cairo_rectangle(cr, 260, 20,  100, 75);
    gdk_rgba_parse (&color, "#ff0");        // イエロー(yellow)
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill(cr);
    
    cairo_rectangle(cr,  20, 115, 100, 75);
    gdk_rgba_parse (&color, "#f00");        // レッド(red)
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill(cr);
    
    cairo_rectangle(cr, 140, 115, 100, 75);
    gdk_rgba_parse (&color, "#0f0");        // グリーン(green)
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill(cr);
    
    cairo_rectangle(cr, 260, 115, 100, 75);
    gdk_rgba_parse (&color, "#00f");        // ブルー(blue)
    gdk_cairo_set_source_rgba(cr,&color);
    cairo_stroke(cr);
}
	

