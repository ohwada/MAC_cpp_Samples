/**
 *  messagedialog.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://vivacocoa.jp/cpp/gtk/gtk_dialog.php

#include <gtk/gtk.h>

// prototype
void show_info();
void show_warn();
void show_ques();
void show_erro();


/**
 *  main
 */
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *grid;
    
    GtkWidget *info;
    GtkWidget *warn;
    GtkWidget *ques;
    GtkWidget *erro;
    
    gtk_init(&argc, &argv);
    window  = gtk_window_new        (GTK_WINDOW_TOPLEVEL);  // 0
    gtk_window_set_title            (GTK_WINDOW(window),
                                     "Message dialogs");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window),
                                     GTK_WIN_POS_CENTER);   // 1
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    grid    = gtk_grid_new          ();
    gtk_grid_set_row_spacing        (GTK_GRID(grid), 15);
    gtk_grid_set_column_spacing     (GTK_GRID(grid), 15);
    gtk_grid_set_row_homogeneous    (GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous (GTK_GRID(grid), TRUE);
    gtk_container_add               (GTK_CONTAINER(window), grid);
    
    info    = gtk_button_new_with_label
                                    ("Info");
    warn    = gtk_button_new_with_label
                                    ("Warning");
    ques    = gtk_button_new_with_label
                                    ("Question");
    erro    = gtk_button_new_with_label
                                    ("Error");
    gtk_grid_attach                 (GTK_GRID(grid), info, 0, 0, 1, 1);
    gtk_grid_attach                 (GTK_GRID(grid), warn, 1, 0, 1, 1);
    gtk_grid_attach                 (GTK_GRID(grid), ques, 0, 1, 1, 1);
    gtk_grid_attach                 (GTK_GRID(grid), erro, 1, 1, 1, 1);
    
    g_signal_connect                (info,      "clicked",
                                     G_CALLBACK(show_info), window);
    g_signal_connect                (warn,      "clicked",
                                     G_CALLBACK(show_warn), window);
    g_signal_connect                (ques,      "clicked",
                                     G_CALLBACK(show_ques), window);
    g_signal_connect                (erro,      "clicked",
                                     G_CALLBACK(show_erro), window);
    g_signal_connect                (window,    "destroy",
                                     G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
    gtk_main                        ();

    return 0;
}


/**
 *  show_info
 */
void show_info(GtkWidget *widget, gpointer window)
{
    GtkWidget *dialog;
    dialog  = gtk_message_dialog_new(GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "Download Completed");
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     "Information");
    gtk_dialog_run                  (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
}


/**
 *   show_warn
 */
void show_warn(GtkWidget *widget, gpointer window)
{
    GtkWidget *dialog;
    dialog  = gtk_message_dialog_new(GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_WARNING,
                                     GTK_BUTTONS_OK,
                                     "Unallowed operation");
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     "Warning");
    gtk_dialog_run                  (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
}


/**
 *  show_ques
 */
void show_ques(GtkWidget *widget, gpointer window)
{
    GtkWidget *dialog;
    dialog  = gtk_message_dialog_new(GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_QUESTION,
                                     GTK_BUTTONS_YES_NO,
                                     "Are you sure to quit?");
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     "Question");
    gtk_dialog_run                  (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
}


/**
 *  show_erro
 */
void show_erro(GtkWidget *widget, gpointer window)
{
    GtkWidget *dialog;
    dialog  = gtk_message_dialog_new(GTK_WINDOW(window),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Error loading file");
    gtk_window_set_title            (GTK_WINDOW(dialog),
                                     "Error");
    gtk_dialog_run                  (GTK_DIALOG(dialog));
    gtk_widget_destroy              (dialog);
}
    