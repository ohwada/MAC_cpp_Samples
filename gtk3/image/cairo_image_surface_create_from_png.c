/**
 * cairo_image_surface_create_from_png.c
 * 2022-06-01 K.OHWADA
 */

// load image from file using
// cairo_image_surface_create_from_png
// reference : https://zetcode.com/gfx/cairo/cairoimages/
// https://tgws.plus/prog/vccairo/02.html

#include <stdio.h>
#include <gtk/gtk.h>


// global
cairo_surface_t *image; 


// prototype
static void do_drawing(cairo_t *);


/**
 *  on_draw_event
 */
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing(cr);

  return FALSE;
}


/**
 *  do_drawing
 */
static void do_drawing(cairo_t *cr)
{
  cairo_set_source_surface(cr, image, 0, 0);
  cairo_paint(cr);    
}


/**
 * main
 */
int main(int argc, char *argv[])
{
const char* WIN_TITLE = "GTK3: cairo";

    char* file = (char *)"images/uparrow.png";

    if (argc == 2) {
        file = argv[1];
    } else {
       printf("Usage: %s <imageFile> \n", argv[0]);
    }

    printf("%s \n", file);
 
  GtkWidget *window;
  GtkWidget *darea;
  
  image = cairo_image_surface_create_from_png(file);

  int width = (int)cairo_image_surface_get_width(image);

  int height = (int)cairo_image_surface_get_height(image);

printf("w=%d, h=%d \n", width, height);

if ((width == 0)||(height == 0))
	{
		printf("cannot load: %s\n", file);
        cairo_status_t status = cairo_surface_status(image);
        printf("status: %s\n", cairo_status_to_string(status) );
		return EXIT_FAILURE;
	}

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

g_signal_connect(G_OBJECT(darea), "draw", 
       G_CALLBACK(on_draw_event), NULL); 

  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height); 
  
  gtk_widget_show_all(window);

  gtk_main();

  cairo_surface_destroy(image);

  return 0;
}
