/**
 *   shape.c
 * 2022-06-01 K.OHWADA
 */

// reference  https://vivacocoa.jp/cpp/gtk/gtk_graphics.php

#include <gtk/gtk.h>
#include <math.h>

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
    gtk_window_set_title            (GTK_WINDOW(window), "Shape");
    gtk_window_set_default_size     (GTK_WINDOW(window), 430, 260);
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
 *   draw_callback
 */
void draw_callback(GtkWidget *da, cairo_t *cr)
{
    GdkRGBA color;
    
    cairo_set_line_width(cr, 1.0);
    cairo_save      (cr);
    
// Oblong
    cairo_scale     (cr, 1, 0.6);
    cairo_arc       (cr, 70, 70, 50, (0.0 * (M_PI/180.0)),
                    (360.0 * (M_PI/180.0)));

// rounded rectangle
    cairo_restore   (cr);
    cairo_move_to   (cr, 150, 20);
    cairo_arc       (cr, 160, 20, 10, (180 * (M_PI/180.0)),
                    (270.0 * (M_PI/180.0)));
    cairo_line_to   (cr, 240, 10);
    cairo_arc       (cr, 240, 20, 10, (270 * (M_PI/180.0)),
                    (360.0 * (M_PI/180.0)));
    cairo_line_to   (cr, 250, 60);
    cairo_arc       (cr, 240, 60, 10, (0 * (M_PI/180.0)),
                    (90.0 * (M_PI/180.0)));
    cairo_line_to   (cr, 160, 70);
    cairo_arc       (cr, 160, 60, 10, (90 * (M_PI/180.)),
                    (180.0 * (M_PI/180.0)));
    cairo_close_path(cr);

// arc
    cairo_move_to   (cr, 280, 10);
    cairo_line_to   (cr, 340, 10);
    cairo_arc       (cr, 280, 10, 100, (0 * (M_PI/180.0)),
                    (90.0 * (M_PI/180.0)));
    cairo_close_path(cr);
    
// perfect circle
    cairo_move_to   (cr, 70, 160);
    cairo_arc       (cr, 70, 160, 50, (0 * (M_PI/180.0)),
                    (360.0 * (M_PI/180.0)));

// square
    cairo_rectangle (cr, 150, 110, 100, 100);
    
    gdk_rgba_parse  (&color, "rgb(255, 17, 17)");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_stroke_preserve(cr);
    
    gdk_rgba_parse  (&color, "rgb(17, 255, 17)");
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_fill      (cr);

// string
    gdk_rgba_parse  (&color, "#777");
    gdk_cairo_set_source_rgba(cr, &color);

    /*
    cairo_select_font_face(cr, "Sans",  CAIRO_FONT_SLANT_NORMAL,
                                        CAIRO_FONT_WEIGHT_BOLD);
    */
    cairo_set_font_size(cr, 45.0);
    cairo_move_to   (cr, 280, 210);
    cairo_show_text (cr, "Hello!"); 
    
}

