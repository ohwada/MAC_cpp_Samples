/**
 *  fontdialog.c
 * 2022-06-01 K.OHWADA
 */


// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GtkWidget   *window;

// prototype
void        select_font();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *vbox;   
    GtkWidget *menubar;
    GtkWidget *editmenu;
    GtkWidget *editmenuitem;
    GtkWidget *fontmenuitem;
    GtkWidget *label;
    
    gtk_init(&argc, &argv);
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window), 
                                     "Font dialog");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 0); // 1
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    menubar = gtk_menu_bar_new      ();
    editmenu
            = gtk_menu_new          ();
    editmenuitem
            = gtk_menu_item_new_with_label("Edit");
    fontmenuitem
            = gtk_menu_item_new_with_label("Font");
    
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),
                                     editmenuitem);
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(editmenuitem),
                                     editmenu);
    gtk_menu_shell_append           (GTK_MENU_SHELL(editmenu),
                                     fontmenuitem);
    
//  0 in the 3rd and 4th arguments means FALSE
    gtk_box_pack_start(GTK_BOX(vbox), menubar, 0, 0, 0);
    
    label   = gtk_label_new         ("GTK Font dialog");
    gtk_label_set_justify           (GTK_LABEL(label),
                                     GTK_JUSTIFY_CENTER);
        
// 1 in the 3rd argument means TRUE, 0 in the 4th argument means FALSE                           
    gtk_box_pack_end(GTK_BOX(vbox), label, 1, 0, 0);
    
    g_signal_connect                (fontmenuitem,  "activate",
                                     G_CALLBACK(select_font),   label);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();
    return                          0;
}


/**
 *   select_font
 */
void select_font(GtkWidget *widget, gpointer label)
{
    GtkWidget               *dialog;
    gint                    result;
    GtkCssProvider          *provider;
    PangoFontDescription    *desc;
    const char              *family;
    gint                    size;
    PangoStyle              style;
    PangoWeight             weight;
    GtkStyleContext         *context;
    
    
    dialog  = gtk_font_chooser_dialog_new
                                    ("Select Font",
                                     GTK_WINDOW(window));
    
    result  = gtk_dialog_run        (GTK_DIALOG(dialog));

// -5 is defined for GTK_RESPONSE_OK 
// and -10 for GTK_RESPONS_APPLY 
    if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
    {
        provider    = gtk_css_provider_new();
        desc        = gtk_font_chooser_get_font_desc
                                    (GTK_FONT_CHOOSER(dialog));
        
        family      = pango_font_description_get_family(desc);
        size        = pango_font_description_get_size(desc)/1000;
        weight      = pango_font_description_get_weight(desc);
        style       = pango_font_description_get_style(desc);
                
        gchar *str  = g_strdup_printf
                    ("window label {font-family: \"%s\";\
                                    font-size: %dpx;\
                                    font-weight: %d;\
                                    font-style: %s;}",
                                    family, size, weight,
                                    style ? "italic" : "normal");
        
        gtk_css_provider_load_from_data(provider,str, -1, NULL);
        context     = gtk_widget_get_style_context(label);
        gtk_style_context_add_provider(context,
                                       GTK_STYLE_PROVIDER(provider),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER
                                       );
        
        g_free                      (str);
    }
    gtk_widget_destroy(dialog);
}
    
