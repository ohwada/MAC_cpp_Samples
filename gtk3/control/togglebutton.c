/**
 *   togglebutton.c
 * 2022-06-01 K.OHWADA
 */

// Toggle button is a button that has a pressed and an unpressed state.
// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// global
guchar  r = 0;
guchar  g = 0;
guchar  b = 0;

// prototype
void    draw_callback();
void    togglered();
void    togglegreen();
void    toggleblue();


/*
void draw_callback  (GtkWidget *da, cairo_t *cr);
void togglered      (GtkToggleButton *red,   GtkWidget *da);
void togglegreen    (GtkToggleButton *green, GtkWidget *da);
void toggleblue     (GtkToggleButton *blue,  GtkWidget *da);
*/


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *da;
    GtkWidget *red;
    GtkWidget *green;
    GtkWidget *blue;
    GtkWidget *frame;
    GtkWidget *fixed;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new         (0);
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "ToggleButton");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    red     = gtk_toggle_button_new_with_label("Red");
    green   = gtk_toggle_button_new_with_label("Green");
    blue    = gtk_toggle_button_new_with_label("Blue");
    da      = gtk_drawing_area_new  ();
    frame   = gtk_frame_new         (NULL);
    gtk_container_add               (GTK_CONTAINER(frame), da);
    gtk_widget_set_size_request     (red,   100,  25);
    gtk_widget_set_size_request     (green, 100,  25);
    gtk_widget_set_size_request     (blue,  100,  25);
    gtk_widget_set_size_request     (da,    110, 110);
    
    fixed   = gtk_fixed_new         ();
    gtk_container_add               (GTK_CONTAINER(window), fixed);
    gtk_fixed_put                   (GTK_FIXED(fixed), red,   20,  20);
    gtk_fixed_put                   (GTK_FIXED(fixed), green, 20,  70);
    gtk_fixed_put                   (GTK_FIXED(fixed), blue,  20, 120);
    gtk_fixed_put                   (GTK_FIXED(fixed), frame,150,  20);
    
    g_signal_connect                (G_OBJECT(da),    "draw",
                                     G_CALLBACK(draw_callback), NULL);
    g_signal_connect                (G_OBJECT(red),   "toggled",
                                     G_CALLBACK(togglered),     da);
    g_signal_connect                (G_OBJECT(green), "toggled",
                                     G_CALLBACK(togglegreen),   da);
    g_signal_connect                (G_OBJECT(blue),  "toggled",
                                     G_CALLBACK(toggleblue),    da);
    g_signal_connect                (window,          "destroy",
                                     gtk_main_quit,             NULL);
                                     
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 * draw_callback
 */
void draw_callback(GtkWidget *da, cairo_t *cr)
{
    guint width, height;
    GdkRGBA color;
    gchar *rgb;
        
    width = gtk_widget_get_allocated_width (da);
    height = gtk_widget_get_allocated_height (da);
    cairo_rectangle(cr, 0, 0, width, height);
    rgb = g_strdup_printf("rgb(%d,%d,%d)",r, g, b);
    gdk_rgba_parse(&color, rgb);
    g_free(rgb);
    gdk_cairo_set_source_rgba (cr, &color);
    cairo_fill (cr);
    
    //printf("%s\n", gdk_rgba_to_string(&color));
}


/**
 * togglered
 */
void togglered(GtkToggleButton *red, GtkWidget *da)
{
    if (gtk_toggle_button_get_active(red))
    {
        r = 255;
    } else {
        r = 0;
    }
    gtk_widget_queue_draw(da);
}


/**
 * togglegreen
 */
void togglegreen(GtkToggleButton *green, GtkWidget *da)
{
    if (gtk_toggle_button_get_active(green))
    {
        g = 255;
    } else {
        g = 0;
    }
    gtk_widget_queue_draw(da);
}


/**
 * toggleblue
 */
void toggleblue(GtkToggleButton *blue, GtkWidget *da)
{
    if (gtk_toggle_button_get_active(blue))
    {
        b = 255;
    } else {
        b = 0;
    }
    gtk_widget_queue_draw(da);
}
	