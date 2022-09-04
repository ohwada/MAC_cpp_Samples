/**
 *  scale.c
 * 2022-06-01 K.OHWADA
 */

// sliders are called scales in gtk, 
// reference : https://vivacocoa.jp/cpp/gtk/gtk_control.php

#include <gtk/gtk.h>

// prototype
void value_changed(GtkRange *range, gpointer label);


/**
 * main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *scale;
    GtkWidget *label;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (0);
    gtk_window_set_title            (GTK_WINDOW(window), "Scale");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), 1);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    scale   = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL,
                                     0, 100, 1);
    gtk_scale_set_draw_value        (GTK_SCALE(scale), FALSE);
    label   = gtk_label_new         ("0");
    
    hbox    = gtk_box_new           (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start              (GTK_BOX(hbox),scale, 1, 1, 0);
    gtk_box_pack_start              (GTK_BOX(hbox),label, 0, 0, 0);
    gtk_widget_set_valign           (hbox, GTK_ALIGN_CENTER);
    gtk_container_add               (GTK_CONTAINER(window), hbox);
    
    g_signal_connect                (scale,  "value-changed",
                                     G_CALLBACK(value_changed), label);
    
    g_signal_connect                (window, "destroy",
                                     gtk_main_quit,             NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 * value_changed
 */
void value_changed(GtkRange *range, gpointer label)
{
    gdouble val     = gtk_range_get_value(range);
    gchar   *str    = g_strdup_printf("%.f", val);
    gtk_label_set_text(GTK_LABEL(label), str);
    g_free(str);
}


    