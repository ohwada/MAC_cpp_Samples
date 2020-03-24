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


bool loadTexture(std::string filename, bool isReverse = false);

void stupTextureReverse(char *data, int width, int height);

void displayTexPolygon();

void setupFunc();

void display_quads(void);

void idle_quads(void);

void reshape_quads(int w, int h);

void keyboard_quads(unsigned char key, int x, int y);

void setTwice(bool flag);

char* reverseUpsideDown(char *src, int width, int height);

