/**
 *  filedialog2.c
 * 2022-06-01 K.OHWADA
 */

// Sample using toolbar
// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// global
GtkWidget   *label;

// prototype
void  select_file();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget   *window;
    GtkWidget   *vbox;
    GtkWidget   *toolbar;
    GtkToolItem *fileitem;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "File dialog");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 0); // 1
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    toolbar = gtk_toolbar_new       ();
    gtk_box_pack_start              (GTK_BOX(vbox), toolbar, 0, 0, 0);
    /* 第3引数と第4引数の 0 は、FALSEの意味です。第5引数は数値の 0 です */
    
    fileitem
            = gtk_tool_button_new_from_stock
                                    (GTK_STOCK_FILE);
    /*この関数とGTK_STOCK定数は非推奨(deprecated)です。実行に問題はありません*/
    /*macOSでは、GTK_STOCK_FILEは読み込めません                         */
    
    gtk_toolbar_insert              (GTK_TOOLBAR(toolbar), fileitem,
                                     -1);
    
    label   = gtk_label_new         ("未選択");
    gtk_label_set_justify           (GTK_LABEL(label),
                                     GTK_JUSTIFY_CENTER);   // 2
    
    gtk_box_pack_end                (GTK_BOX(vbox), label, 1, 0, 0);
    /*第3引数の 1 はTRUE、第4引数の 0 はFALSE、第5引数は数値の0という意味です*/
    
    g_signal_connect                (fileitem,      "clicked",
                                     G_CALLBACK(select_file), window);
    
    g_signal_connect                (window,        "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return  0;
}


/**
 *  select_file
 */
void    select_file(GtkWidget *widget, gpointer window)
{
    GtkWidget   *dialog;
    gint        result;
    
    dialog  = gtk_file_chooser_dialog_new
                                    ("Select File",
                                     window,
                                     GTK_FILE_CHOOSER_ACTION_OPEN,
// For save dialog, 
// set to GTK_FILE_CHOOSER_ACTION_SAVE
                                     ("Cancel"),
                                     GTK_RESPONSE_CANCEL,
                                     ("Select"),
                                     GTK_RESPONSE_ACCEPT,
                                     NULL);
    
    result  = gtk_dialog_run        (GTK_DIALOG(dialog));
    
    if (result == GTK_RESPONSE_ACCEPT)
    /* GTK_RESPONSE_ACCEPT定数は -3 です */
    {
        char *filename;
        GtkFileChooser *chooser
            = GTK_FILE_CHOOSER(dialog);
        filename
            = gtk_file_chooser_get_filename
                                    (chooser);
        
        gtk_label_set_text          (GTK_LABEL(label), filename);
        g_free                      (filename);
    } else {
        gtk_label_set_text          (GTK_LABEL(label), "未選択");
    }
    gtk_widget_destroy              (dialog);
}

    