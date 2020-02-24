/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 */

// reference : https://qiita.com/totepo18/items/b2a6bdb8054f8c9a1cbe


#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include <iostream>

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

using namespace std;


const GLfloat lightPosition1[4] = {0.0f,3.0f, 5.0f, 1.0f};
const GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat lightPosition2[4] = {5.0f,3.0f, 0.0f, 1.0f};
const GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };

const GLfloat teapotAmbient[4] = {0.3f,0.5f, 0.0f, 1.0f};
const GLfloat teapotDiffuse[4] = {1.0f,1.0f, 0.3f, 1.0f};
const GLfloat teapotSpecular[4] = {1.0f,1.0f, 1.0f, 1.0f};
const GLfloat teapotShininess[4] = {20.0f};

void setup(void) {

// Gray
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_SPECULAR, red);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);
}


/**
 * draw
 */
void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);
    glFlush();
}


/**
 * resize
 */
void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,
                   (double)width/height,
                   0.1,
                   100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.5, 2.1, 2.0,
              0.0, 0.0, 0.0,
              0.0, 4.0, 0.0);
}


/**
 * display
 */
void display(void){
// Black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutWireTeapot(0.5);
    glFlush();
}


/**
 * main
 */
int main( int argc, char** argv)
{

    cout << "OpenGL/GLUT WireTeapot" << endl;

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("OpenGL/GLUT WireTeapot");
    glutReshapeFunc(resize);
    glutDisplayFunc(draw);
    setup();
    glutMainLoop();

    return EXIT_SUCCESS;
}



