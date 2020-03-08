/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string>  
#include <iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

void setupWindow(std::string title, int width, int height, int x, int y);

void setupTexture(GLubyte* image, int width, int height, GLint internalformat, GLenum format); 

void displayTexPolygon();

void display(void);

void reshape(int w, int h);

void keyboard(unsigned char key, int x, int y);

void dumpGLInfo();

