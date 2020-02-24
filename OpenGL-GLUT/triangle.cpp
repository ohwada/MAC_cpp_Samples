/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 */

// origina : http://math.hws.edu/graphicsbook/source/glut/first-triangle.c


/*
 *  As a first example of using OpenGL in C, this program draws the
 *  classic red/green/blue triangle.  It uses the default OpenGL
 *  coordinate system, in which x, y, and z are limited to the range
 *  -1 to 1, and the positive z-axis points into the screen.  Note
 *  that this coordinate system is hardly ever used in practice.
 *
 *  When compiling this program, you must link it to the OpenGL library
 *  and to the glut library. For example, in Linux using the gcc compiler, 
 *  it can be compiled with the command:
 *
 *          gcc -o first-triangle first-triangle.c -lGL -lglut
 */
 
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
void display() {  // Display function will draw the image.
 
    //glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)

 // Gray
    glClearColor(0.5, 0.5, 0.5, 1.0);

    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
 
// draw Triangle
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd(); 

    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


/**
 * main
 */
int main( int argc, char** argv ) {  // Initialize GLUT and 

    cout << "OpenGL/GLUT Triangle" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.

 // Run the event loop!  This function does not return.
    glutMainLoop();

// Program ends when user closes the window.
    return EXIT_SUCCESS;
}

