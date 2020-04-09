/**
 * FreeType Sample
 * 2020-03-01 K.OHWADA
 * original : https://github.com/benhj/glfreetype
 */
 
// read font file <br/>
// show text in OpenGL window <br/>


// g++  test_TextRenderer.cpp  TextRenderer.cpp -std=c++11  -framework OpenGL   -framework GLUT `pkg-config --cflags --libs freetype2`

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "TextRenderer.hpp"

// global 
    const char* SAMPLE_TEXT = "The quick brown fox jumps over the lazy dog";

glfreetype::font_data our_font;


/**
 *  init
 */
void init (char* font_file)
{
    our_font.init(font_file, 25 /* size */);
}


/**
 * display
 */
void display(void)
{

        glClearColor(255.0, 255.0, 255.0, 255.0); // White
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glLoadIdentity();

        glColor3f(0.0, 0.0, 1.0); //  Blue

        glfreetype::print(our_font, 20 /* xpos */, 20 /* ypos */, 
                          SAMPLE_TEXT);

        glPopMatrix();

   glFlush();
}


/**
 * reshape
 */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}


/**
 * keyboard
 */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:  // Escape key
         exit(0);
   }
}


/**
 * main
 */
int main(int argc, char** argv)
{

    const int WIN_WIDTH = 680;
    const int WIN_HEIGHT = 120;

    const char* WIN_TITLE = "test TextRenderer";

    if (argc != 2) {
        std::cerr << "usage: " << argv[0] <<  " <fontfile> " << std::endl;
        return 1;
  }

    char *font_file = argv[1];

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (WIN_WIDTH, WIN_HEIGHT);
   glutCreateWindow (WIN_TITLE);
    init (font_file);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}
