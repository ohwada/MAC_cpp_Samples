/**
 * OpenGL Sample
 * 2010-02-01 K.OHWADA
 */

// reference : https://www.glfw.org/documentation.html

#include <stdio.h>
#include <stdlib.h>
#include <string>  
#include <iostream>

#include <OpenGL/OpenGL.h>
#include <GLFW/glfw3.h>

using namespace std;


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

    cout << "OpenGL/glfw3 Hello" << endl;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        cerr << "can not initialize glfw" << endl;
        return EXIT_FAILURE;
    }


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(320, 240, "OpenGL/glfw3 Hello", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        cerr << "can not open window" << endl;
        return EXIT_FAILURE;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    dumpGLInfo();

    string glfw_version = glfwGetVersionString();	
    cout << "glfw Version: " << glfw_version << endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

// Red
        glClearColor(1.0, 0.0, 0.0, 1.0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
