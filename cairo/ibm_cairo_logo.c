/**
 * cairo sample
 * 2020-03-01 K.OHWADA
 */

// draw IBM logo in GTK window , 
// and draw to png file, pdf file, svg file, ps file
// reference : https://www.ibm.com/developerworks/jp/linux/library/l-cairo/index.html

#include <gtk/gtk.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <cairo-svg.h>
#include <math.h>
#include <string.h>

// #include <gdk/gdkkeysyms.h>

#define WIDTH  800
#define HEIGHT 600

// #define STRIDE WIDTH*4
// #define MAX_COORDS 1024



/* This path desribes what will be drawn later 
   The bulk of it is doing the IBM letters by connect the dots
   at the very end, we will get fancy and add a (R) Registered logo.
*/
static void
travel_path (cairo_t *cr)
{
   gint     pen_radius         = 10;

   cairo_set_source_rgb (cr, 1,1,1);
   cairo_paint (cr);

   cairo_set_line_width (cr, pen_radius*2);

   /* Use IBM Blue Pen Color with no ALPHA */
   cairo_set_source_rgba (cr, .3, .42, .69, 1);


   /* This Draws the IBM 8 Lines "I" Logo */
   cairo_move_to (cr, 10, 10);
   cairo_line_to (cr, 160, 10); 

   cairo_move_to (cr, 10, 40);
   cairo_line_to (cr, 160, 40);

   /* NOTE: Narrower Middle: 1/3 width */
   cairo_move_to (cr, 60, 70);
   cairo_line_to (cr, 110, 70);

   cairo_move_to (cr, 60, 100);
   cairo_line_to (cr, 110, 100);

   cairo_move_to (cr, 60, 130);
   cairo_line_to (cr, 110, 130);

   cairo_move_to (cr, 60, 160);
   cairo_line_to (cr, 110, 160);
   /* END Narrower Middle */

   cairo_move_to (cr, 10, 190);
   cairo_line_to (cr, 160, 190);

   cairo_move_to (cr, 10, 220);
   cairo_line_to (cr, 160, 220);
   /* END "I" DRAWING */




   /* This Draws the IBM 8 Lines "B" Logo */
   cairo_move_to (cr, 170, 10);
   cairo_line_to (cr, 340, 10); 

   cairo_move_to (cr, 170, 40);
   cairo_line_to (cr, 360, 40); 

   cairo_move_to (cr, 200, 70);
   cairo_line_to (cr, 250, 70);
   /*B's have holes in them! */
   cairo_move_to (cr, 300, 70); 
   cairo_line_to (cr, 360, 70); 


   cairo_move_to (cr, 210, 100);
   cairo_line_to (cr, 350, 100); 


   cairo_move_to (cr, 210, 130);
   cairo_line_to (cr, 350, 130); 


   cairo_move_to (cr, 200, 160);
   cairo_line_to (cr, 250, 160);
   /*B's have holes in them! */
   cairo_move_to (cr, 300, 160); 
   cairo_line_to (cr, 360, 160); 


   cairo_move_to (cr, 170, 190);
   cairo_line_to (cr, 360, 190); 


   cairo_move_to (cr, 170, 220);
   cairo_line_to (cr, 340, 220); 
   /* END "B" DRAWING */
	



   /* THE EVER POINTY "M"  */
   cairo_move_to (cr, 370, 10);
   cairo_line_to (cr, 470, 10); 
   cairo_move_to (cr, 560, 10);
   cairo_line_to (cr, 660, 10); 


   cairo_move_to (cr, 370, 40);
   cairo_line_to (cr, 490, 40); 
   cairo_move_to (cr, 540, 40);
   cairo_line_to (cr, 660, 40); 


   cairo_move_to (cr, 400, 70);
   cairo_line_to (cr, 510, 70); 
   cairo_move_to (cr, 520, 70);
   cairo_line_to (cr, 630, 70); 


   cairo_move_to (cr, 400, 100);
   cairo_line_to (cr, 630, 100); 


   cairo_move_to (cr, 400, 130);
   cairo_line_to (cr, 470, 130);
   cairo_move_to (cr, 480, 130);
   cairo_line_to (cr, 550, 130);
   cairo_move_to (cr, 560, 130);
   cairo_line_to (cr, 630, 130); 


   cairo_move_to (cr, 400, 160);
   cairo_line_to (cr, 470, 160);
   cairo_move_to (cr, 490, 160);
   cairo_line_to (cr, 540, 160);
   cairo_move_to (cr, 560, 160);
   cairo_line_to (cr, 630, 160); 


   cairo_move_to (cr, 370, 190);
   cairo_line_to (cr, 470, 190);
   cairo_move_to (cr, 500, 190);
   cairo_line_to (cr, 530, 190);
   cairo_move_to (cr, 560, 190);
   cairo_line_to (cr, 660, 190); 


   cairo_move_to (cr, 370, 220);
   cairo_line_to (cr, 470, 220);
   cairo_move_to (cr, 510, 220);
   cairo_line_to (cr, 520, 220);
   cairo_move_to (cr, 560, 220);
   cairo_line_to (cr, 660, 220); 
 
   /* END POINTY LETTERS */
   
   /* We stroke the path so we see everything we just specified
      by connecting the dots
   */
   cairo_stroke(cr);
 



   /* Let us add a disclaimer and show some fancy cairo: */
   /* We are going to want a nice fine lined circle around the R 
   you need to make sure you have stroked existing things
   that you wanted drawn with the larger pen before continuing. 
   */
   cairo_set_line_width (cr, pen_radius*.5);

   /* Now we will draw the fancy circle around the "R" */
   /* NOTE: The angles are in radians */
   cairo_move_to (cr, 710, 200);
   double angle1 = 0 * (M_PI/180.0);  
   double angle2 = 360 * (M_PI/180.0);

   /* We draw a large black circle */
   cairo_set_source_rgba (cr, 0, 0, 0, 1);
   cairo_arc (cr, 710, 200, 20, angle1, angle2);
   cairo_stroke (cr);

   /* We draw a smaller white circle centered on it */
   cairo_set_source_rgba (cr, 1, 1, 1, 1);
   cairo_arc (cr, 710, 200, 20, angle1, angle2);
   /* We use the fill operator to fill in the circle! */
   cairo_fill (cr);

   /* We are going to draw the letter "R" with black pen*/

   cairo_move_to (cr, 695,212); /* Bottom left of text at point */
   cairo_set_source_rgba (cr, 0, 0, 0, 1);
   cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                       CAIRO_FONT_WEIGHT_BOLD);
   cairo_set_font_size (cr, 40);
   cairo_show_text (cr, "R");

    /* We stroke everything we have just done 
       to actually draw it...
    */ 
    cairo_stroke (cr);	 

}




/* Apply our path to the surface specified */
static void
draw (cairo_surface_t *surface)
{
    cairo_t *cr;
    cr = cairo_create (surface);

    /* Try applying the scale and rotate factors here to examine their effects on the output!*/
    /* cairo_rotate (cr, -M_PI / 4); */
    /* cairo_scale (cr, 2, 1.0);  */

    travel_path (cr);
    cairo_destroy (cr);
}


/* Function needed to draw to gtk window */
static void
draw_gtk (GtkWidget      *widget,
          GdkEventExpose *eev,
          gpointer        data)
{
  cairo_t *cr;
  cr = gdk_cairo_create (widget->window);
  travel_path (cr);
  cairo_destroy (cr);
}


/* We will draw our path on multiple surfaces to demonstrate 
   some of the various cairo backend
*/
int main(int argc, char** argv)
{

    char*  WIN_TITLE = "cairo IBM logo";

    cairo_surface_t *surface;


    /* PDF Backend */
    surface = cairo_pdf_surface_create ("IBM.pdf",
					WIDTH, HEIGHT);
    draw (surface);
    cairo_surface_destroy (surface);


    /* Postscript Backend */
    surface = cairo_ps_surface_create ("IBM.ps",
					WIDTH, HEIGHT);
    draw (surface);
    cairo_surface_destroy (surface);


    /* Image backend */
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
					  WIDTH, HEIGHT);
    draw (surface);
    cairo_surface_write_to_png (surface, "IBM.png");
    cairo_surface_destroy (surface);


    /* Scalable Vector Graphics Backend */
    surface = cairo_svg_surface_create ("IBM.svg",
					WIDTH, HEIGHT);
    draw (surface);
    cairo_surface_destroy (surface);


    /* GTK Window using Cairo */
    gtk_init (NULL, NULL);        /* Fire up GTK!       */
    GtkWidget *mainwin;           /* Make a new windows */
    GtkWidget *canvas = NULL;     /* Make a new canvas  */
  
    mainwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mainwin), 
        WIN_TITLE);

    canvas = gtk_drawing_area_new ();
    gtk_widget_set_size_request (canvas, WIDTH, HEIGHT);     
    gtk_container_add (GTK_CONTAINER (mainwin), canvas); /* Place the canvas in the window */
 
    g_signal_connect (mainwin, "destroy", G_CALLBACK (gtk_main_quit), NULL); /* Quit graphically */

    /* Instead of drawing like usual, we connect the expose event to do the drawing! */
    g_signal_connect (G_OBJECT (canvas), "expose-event",
                      G_CALLBACK (draw_gtk), NULL);

    gtk_widget_show_all (mainwin); /* Show the window on the screen */
    gtk_main ();
    return 0;
}



