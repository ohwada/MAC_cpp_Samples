/**
 *  fontdialog2.c
 * 2022-06-01 K.OHWADA
 */

// Sample using toolbar
// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GtkWidget   *window;

// prototype
void  select_font();

/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *vbox;   
    GtkWidget *toolbar;
    GtkToolItem *font;
    GtkWidget *label;
    
    gtk_init(&argc, &argv);
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window), 
                                     "Font dialog");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    //gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 0); // 1
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    toolbar = gtk_toolbar_new       ();
    gtk_toolbar_set_style           (GTK_TOOLBAR(toolbar),
                                     GTK_TOOLBAR_ICONS);
    font    = gtk_tool_button_new_from_stock
                                    (GTK_STOCK_SELECT_FONT);
    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), font, -1);

//  0 in the 3rd and 4th arguments means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, 0, 0, 0);
             
    label   = gtk_label_new         ("GTK Font dialog");
    gtk_label_set_justify           (GTK_LABEL(label),
                                     GTK_JUSTIFY_CENTER);

// 1 in the 3rd argument means TRUE, 
// 0 in the 4th argument means FALSE
    gtk_box_pack_end(GTK_BOX(vbox), label, 1, 0, 0);
       
    g_signal_connect                (font,          "clicked",
                                     G_CALLBACK(select_font),   label);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return   0;
}


/**
 *  select_font
 */
void select_font(GtkWidget *widget, gpointer label)
{
    GtkWidget               *dialog;
    gint                    result;
    gchar                   *fontname;
    PangoFontDescription    *fontdesc;
    
    dialog  = gtk_font_chooser_dialog_new
                                    ("Select Font",
                                     GTK_WINDOW(window));
    result  = gtk_dialog_run        (GTK_DIALOG(dialog));

// -5 is defined for GTK_RESPONSE_OK 
// and -10 for GTK_RESPONS_APPLY 
    if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
    {
        fontname    = gtk_font_chooser_get_font
                                    (GTK_FONT_CHOOSER(dialog));
        fontdesc    = pango_font_description_from_string
                                    (fontname);
        gtk_widget_override_font    (GTK_WIDGET(label), fontdesc);
        g_free                      (fontname);
    }
    gtk_widget_destroy(dialog);
}
