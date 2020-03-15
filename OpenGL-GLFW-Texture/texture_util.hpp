/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>  
#include <iostream>

// macOS
#include <OpenGL/OpenGL.h>

#include <GLFW/glfw3.h>


GLuint crateShader();

GLuint setupTexture(char *image, int width, int height);

void display(GLuint  programId, GLuint texID);

void dumpGLInfo();

