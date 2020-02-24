/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 */

// reference : https://tokoik.github.io/opengl/libglut.html#2.4

#include <stdio.h>
#include <stdlib.h>
#include <string>  
#include <iostream>

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

using namespace std;


/**
 * display
 */
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}


/**
 * dumpGLInfo
 */
void dumpGLInfo() {
    string vendor = (char *)glGetString(GL_VENDOR);
    string renderer = (char *)glGetString(GL_RENDERER);
    string version = (char *)glGetString(GL_VERSION);




    cout << "OpenGL Vender: " << vendor << endl;
    cout << "OpenGL Renderer: " << renderer << endl;
    cout << "OpenGL Version: " << version << endl;
}


/**
 * main
 */
int main( int argc, char** argv)
{

    cout << "OpenGL/GLUT hello window" << endl;
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("OpenGL/GLUT Hello");
    glutDisplayFunc(display);

// Red
    glClearColor(1.0, 0.0, 0.0, 1.0);

    dumpGLInfo();

    cout << "GLUT Version: " <<  GLUT_API_VERSION << endl;

// Run the event loop!  This function does not return.
    glutMainLoop();

    return EXIT_SUCCESS;
}
