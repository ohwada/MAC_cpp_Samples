// original : https://vivacocoa.jp/cpp/gtk/gtk_texteditor.php

/************************************
    texteditor.c
    copyright    :   vivacocoa.jp
    last modified:   Jan. 4, 2020
************************************/   

#include <gtk/gtk.h>
#include <string.h>     // for strcmp

    /*  Prototypes      */
void        new_file        ();
void        open_file       ();
void        save_file       ();
void        change_buffer   ();
void        closin_buffer   ();
void        comfirm_save    ();

    /*  Global variables*/
GtkWidget   *window;
char        *filename       =   "";
gint        edited          =   FALSE;

int main(int argc, char *argv[])
{
    /*  Varialbes       */
    GtkWidget       *vbox;
    GtkWidget       *menubar;
    GtkWidget       *fileitem;
    GtkWidget       *menu;
    GtkWidget       *newitem;
    GtkWidget       *openitem;
    GtkWidget       *saveitem;
    GtkWidget       *separator;
    GtkWidget       *quititem;
    GtkWidget       *textview;
    GtkWidget       *swin;
    GtkWidget       *frame;
    GtkAccelGroup   *accel_group;
    GtkTextBuffer   *buffer;
    
    gtk_init(&argc, &argv);
    
    /*  Window          */
    window      = gtk_window_new    (0);
    gtk_window_set_title            (GTK_WINDOW(window),"Text Editor");
    gtk_window_set_default_size     (GTK_WINDOW(window), 500, 500    );
    gtk_window_set_position         (GTK_WINDOW(window), 1           );
    vbox        = gtk_box_new       (GTK_ORIENTATION_VERTICAL, 0     );
    gtk_container_add               (GTK_CONTAINER(window), vbox     );
    
    /*  Menubar         */
    menubar     = gtk_menu_bar_new  ();
    fileitem    = gtk_menu_item_new_with_label  ("File");
    gtk_menu_shell_append           (GTK_MENU_SHELL(menubar),fileitem);
    gtk_box_pack_start              (GTK_BOX(vbox), menubar, 0, 0, 0 );
    menu        = gtk_menu_new      ();
    gtk_menu_item_set_submenu       (GTK_MENU_ITEM(fileitem),   menu );
    
    /*  MenuItems       */
    newitem     = gtk_menu_item_new_with_label  ("New" );
    openitem    = gtk_menu_item_new_with_label  ("Open");
    saveitem    = gtk_menu_item_new_with_label  ("Save");
    separator   = gtk_separator_menu_item_new   ();
    quititem    = gtk_menu_item_new_with_label  ("Quit");
    
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu),  newitem  );
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu),  openitem );
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu),  saveitem );
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu),  separator);
    gtk_menu_shell_append           (GTK_MENU_SHELL(menu),  quititem );
    
    /*  Accel group     */                  // GDK_SHIFT_MASK      1
                                            // GDK_CONTROL_MASK    4 
                                            // GDK_MOD1_MASK       8
                                            // GTK_ACCEL_VISIBLE   1
    accel_group = gtk_accel_group_new           ();
    gtk_window_add_accel_group      (GTK_WINDOW(window), accel_group );
    gtk_widget_add_accelerator      (newitem,  "activate", accel_group,
                                     GDK_KEY_n, GDK_CONTROL_MASK,   1);
    gtk_widget_add_accelerator      (openitem, "activate", accel_group,
                                     GDK_KEY_o, GDK_CONTROL_MASK,   1);
    gtk_widget_add_accelerator      (saveitem, "activate", accel_group,
                                     GDK_KEY_s, GDK_CONTROL_MASK,   1);
    gtk_widget_add_accelerator      (quititem, "activate", accel_group,
                                     GDK_KEY_q, GDK_CONTROL_MASK,   1);
    
    /*  Textview        */
    textview    = gtk_text_view_new ();
    swin        = gtk_scrolled_window_new   (NULL, NULL);
    buffer      = gtk_text_view_get_buffer  (GTK_TEXT_VIEW(textview) );
    gtk_scrolled_window_set_policy  (GTK_SCROLLED_WINDOW(swin), 1, 1 );
    frame       = gtk_frame_new     (NULL);
    gtk_container_add               (GTK_CONTAINER(swin),   textview );
    gtk_container_add               (GTK_CONTAINER(frame),  swin     );
    gtk_box_pack_end                (GTK_BOX(vbox), frame, 1, 1, 0   );
    gtk_text_view_set_monospace     (GTK_TEXT_VIEW(textview),   TRUE );
    
    /*  Events          */
    g_signal_connect                (newitem,   "activate",
                                     G_CALLBACK(new_file),     buffer);
    g_signal_connect                (openitem,  "activate",
                                     G_CALLBACK(open_file),    buffer);
    g_signal_connect                (saveitem,  "activate",
                                     G_CALLBACK(save_file),    buffer);
    g_signal_connect                (buffer,    "changed",
                                     G_CALLBACK(change_buffer), NULL );
    g_signal_connect                (quititem,  "activate",
                                     G_CALLBACK(closin_buffer),buffer);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL );
    
    /*  Main loop       */
    gtk_widget_show_all             (window);
    gtk_main                        ();
    return                          0;
}

    /*  New file        */
void new_file(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    
    filename    =   "Untitled";
    gtk_text_buffer_set_text        (buffer, "", -1);
    gtk_window_set_title            (GTK_WINDOW(window), filename    );
    edited      =   FALSE;
}
 
    /*  Open file       */      // GTK_FILE_CHOOSER_ACTION_OPEN    0
                                // GTK_FILE_CHOOSER_ACTION_SAVE    1
                                // GTK_RESPONSE_ACCEPT            -3
                                // GTK_RESPONSE_CANCEL            -6
void open_file(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    
    GtkWidget   *dialog;
    gint        result;
    dialog  = gtk_file_chooser_dialog_new
                                    ("Open File", GTK_WINDOW(window),
                                     GTK_FILE_CHOOSER_ACTION_OPEN, 
                                     "Cancel", GTK_RESPONSE_CANCEL,
                                     "Open", GTK_RESPONSE_ACCEPT,
                                     NULL);
    result  = gtk_dialog_run        (GTK_DIALOG(dialog)              );
    if (result == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser  *chooser;
        FILE            *fp;
        char            str[256];
        GtkTextIter     iter;
        chooser     = GTK_FILE_CHOOSER(dialog);
        filename    = gtk_file_chooser_get_filename(chooser);
        gtk_text_buffer_set_text(buffer, "", -1);
        
        fp          = fopen(filename, "r");
        if (fp != NULL)
        {
            while ((fgets(str, 256, fp)) != NULL)
            {
                gtk_text_buffer_get_end_iter(buffer, &iter);
                gtk_text_buffer_insert(buffer,&iter,str,-1);
                edited  =   FALSE;
            }
        } else {
            gtk_text_buffer_set_text(buffer, "error", -1);
        }
        fclose(fp);
        gtk_window_set_title        (GTK_WINDOW(window), filename    );
    }
    gtk_widget_destroy(dialog);
}

    /*  Save file       */
void save_file(GtkWidget *widget, gpointer buffer)
{
    gchar       *text;
    GtkTextIter startiter;
    GtkTextIter enditer;
    FILE        *fp;
    if (edited && strcmp("Untitled", filename))
    {
        fp  =   fopen(filename, "w");
        if (fp != NULL)
        {
            gtk_text_buffer_get_start_iter  (buffer, &startiter );
            gtk_text_buffer_get_end_iter    (buffer, &enditer   );
            text    =   gtk_text_buffer_get_text
                                            (buffer, &startiter,
                                             &enditer, FALSE    );
            fprintf(fp, "%s", text);
            edited  =   FALSE;
        gtk_window_set_title        (GTK_WINDOW(window), filename    );
        } else {
            gtk_text_buffer_set_text        (buffer, "error", -1);
        }
        fclose(fp);
        g_free(text);
    } else if (edited) {
        GtkWidget       *dialog;
        GtkFileChooser  *chooser;
        gint            result;
        dialog  =   gtk_file_chooser_dialog_new
                                    ("Save File", GTK_WINDOW(window),
                                     GTK_FILE_CHOOSER_ACTION_SAVE,
                                     "Cancel", GTK_RESPONSE_CANCEL,
                                     "Save", GTK_RESPONSE_ACCEPT,
                                     NULL);
        chooser =   GTK_FILE_CHOOSER(dialog);
        gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE );
        gtk_file_chooser_set_current_name(chooser, "Untitled"        );
           
        result  =   gtk_dialog_run(GTK_DIALOG(dialog));
        if (result == GTK_RESPONSE_ACCEPT)
        {
            GtkFileChooser  *chooser;
            chooser     =   GTK_FILE_CHOOSER(dialog);
            filename    =   gtk_file_chooser_get_filename(chooser);
            fp          =   fopen(filename, "w");
            if (fp != NULL)
            {
                gtk_text_buffer_get_start_iter  (buffer, &startiter );
                gtk_text_buffer_get_end_iter    (buffer, &enditer   );
                text    =   gtk_text_buffer_get_text
                                                (buffer, &startiter,
                                                 &enditer, FALSE    );
                fprintf(fp, "%s", text);
                edited  =   FALSE;
                gtk_window_set_title    (GTK_WINDOW(window), filename);
            } else {
                gtk_text_buffer_set_text        (buffer, "error", -1);
            }
            fclose(fp);
            g_free(text);
        }
        gtk_widget_destroy(dialog);
    }
}

    /*  Change buffer   */
void change_buffer(GtkTextBuffer *buffer)
{
    if (!edited)
    {
        if (!(strcmp(filename, "")))
        {
            filename    =   "Untitled";
        }
        char   title[256];
        sprintf(title, "%s - edited", filename);
        gtk_window_set_title    (GTK_WINDOW(window), title);
        edited  =   TRUE;
    }
}

    /*  Closing buffer  */
void closin_buffer(GtkWidget *widget, gpointer buffer)
{
    if (edited) comfirm_save(buffer);
    gtk_main_quit();
}

void comfirm_save(gpointer buffer)
{
    gint    result;
    GtkWidget   *dialog;
    dialog  =   gtk_message_dialog_new
                                    (GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_QUESTION,
                                     GTK_BUTTONS_YES_NO,
                        "This file has changed. Do you want to save?"
                                    );
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     filename);
    result  =   gtk_dialog_run      (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
    if (result == GTK_RESPONSE_YES) save_file(window, buffer);
}
    

