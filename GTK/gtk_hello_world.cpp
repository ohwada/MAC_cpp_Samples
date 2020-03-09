/**
 * GTK Sample
 * 2020-01-01 K.OHWADA
 * reference : https://developer.gnome.org/gtk-tutorial/stable/c39.html#SEC-HELLOWORLD
 */


#include <string> 
#include<iostream>
#include <gtk/gtk.h>

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH =   100;
    const int WIN_HEIGHT = 100;

    char*  WIN_TITLE = "GTK: Hello World";

    cout << WIN_TITLE << endl;

    // version
    const string DOT = ".";
    string version = to_string(GTK_MAJOR_VERSION) + DOT
        + to_string(GTK_MINOR_VERSION) + DOT
        + to_string(GTK_MICRO_VERSION);

    cout << "GTK Version: " << version << endl;


    gtk_init(&argc, &argv);
    
    GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), 
        WIN_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), 
        WIN_WIDTH, WIN_HEIGHT);
    gtk_widget_show(window);
    
    gtk_main();
    
	return EXIT_SUCCESS;
}
